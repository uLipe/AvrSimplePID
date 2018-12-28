				.global  PidControllerUpdate
				.section .text

;
;extern iq8_t PidControllerUpdate(PidController *pid, iq8_t reference, iq8_t feedback);
;
PidControllerUpdate:
			push r0			;prodl
			push r1			;prodh
			push r2			;_zero_reg_
			push r16		;inPtr
			push r17		;outPtr
			push r18		;inSmp
			push r19		;coefsmp (r20:21 -> accu)

			clr	  r2
			movw  r30, r24	;
			movw  r28, r24	;
			adiw  r28, +11	;
			ldd   r16, Y+0	;
			ldd   r17, Y+1	;

			add	  r30, r16	;finds next free xn from fifo
			adc	  r31, r2	; 
			sub	  r22, r20	;x[0] = ref - smp
			std	  Z+0, r22	;
			dec	  r16		;
			andi  r16, 0x03 ;
			std	  Y+0, r16	;
			inc	  r16		;
			andi  r16, 0x03 ;
			movw  r26,r24	;
			adiw  r26,+4	;find the IIR filter coefficients
			
			;at this point we have:
			; Z--->x(0)
			; X--->b(0) 
			; Compute IIR Z-tF:
			clr	 r20		;
			ldd  r18, Z+0	;
			ld	 r19, X+	;
			fmuls r19, r18	;
			movw  r18,r0	;
			add	  r20, r19	; 
			
			inc	  r16
			andi  r16, 0x03	;
			movw  r30, r24  ;
			add	  r30, r16	;
			adc	  r31, r2	;

			ldd  r18, Z+0	;
			ld	 r19, X+	;
			fmuls r19, r18	;
			movw  r18,r0	;
			add	  r20, r19	;

			inc	  r16
			andi  r16, 0x03	;
			movw  r30, r24  ;
			add	  r30, r16	;
			adc	  r31, r2	;
			 
			ldd  r18, Z+0	; Puts the new output value 
			ld	 r19, X+	; on next yn entry:
			fmuls r19, r18	;
			movw  r18,r0	;
			add	  r20, r19	; 
			movw  r30, r24	;
			adiw  r30, +7	;
			add	  r30, r17	;
			adc	  r31, r2	;
			ldd	  r18, Z+0	;
			sub   r20, r18	;
			inc	  r17		;
			andi  r17, 0x03	; Update pid TF history.
			movw  r30, r24	;
			adiw  r30, +7	;
			add	  r30, r17	;
			adc   r31, r2	;
			std   Z+0, r20	; 
	
			std	  Y+1, r17	;
			mov   r24, r18	; 
			pop	r19			;
			pop r18	
			pop r17
			pop r16
			pop r2
			pop r1
			pop r0			
			ret

.end
