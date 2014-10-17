
/*
 * simplePID_a.s
 *
 * Created: 16/10/2014 20:12:12
 *  Author: felipe.neves
 */ 
 #define MASK		0x03
 #define FILTER_LEN 0x03

				.global  PidCompute

				.section .text
;
;/*
; *	PID control structure
;*/
;struct pid_
;{
;	iq8_t inputState[4];	+0
;	iq8_t coefSet[3];		+4 
;	iq8_t outputState[4];	+7 
;
;	uint8_t inputPtr;		+11
;	uint8_t outputPtr;		+12
;
;	iq8_t kp;				//ganho proporcional
;	iq8_t ki;				//ganho integral
;	iq8_t kd;				//ganho derivativo
;		
;};



;
;extern iq8_t PidCompute(Handler_t h, iq8_t ref, iq8_t smp )
;
PidCompute:
			push r0			;prodl
			push r1			;prodh
			push r2			;_zero_reg_
			push r16		;inPtr
			push r17		;outPtr
			push r18		;inSmp
			push r19		;coefsmp (r20:21 -> accu)

			clr	  r2
			movw  r30, r24	;acessa o endereco apontado por h
			movw  r28, r24	;
			adiw  r28, +11	;
			ldd   r16, Y+0	;r16->inPtr
			ldd   r17, Y+1	;r17->outPtr

			add	  r30, r16	;aponta a posição livre da FIFO de entrada
			adc	  r31, r2	;
			sub	  r22, r20	;
			std	  Z+0, r22	;x[0] = ref - smp

			dec	  r16		;
			andi  r16, MASK ;atualiza ponto de insercao da FIFO
			std	  Y+0, r16	;nao sera mais usado por enquando

			inc	  r16		;ajusta ponto de leitura a posicao corrente
			andi  r16, MASK ;atualiza ponto de insercao da FIFO
			
			movw  r26,r24	;
			adiw  r26,+4	;aponta ao set de coeficientes:
			
			;nesse momento tempos:
			; Z--->x(0)
			; X--->b(0) 
			;Computa equação de diferencia IIR 
			clr	 r20		;
			ldd  r18, Z+0	;
			ld	 r19, X+	;
			fmuls r19, r18	;
			movw  r18,r0	;
			add	  r20, r19	; acumula primeiro MAC
			
			inc	  r16
			andi  r16, MASK	;
			movw  r30, r24  ;
			add	  r30, r16	;
			adc	  r31, r2	;realiza incremento circular na posicao da fifo

			ldd  r18, Z+0	;
			ld	 r19, X+	;
			fmuls r19, r18	;
			movw  r18,r0	;
			add	  r20, r19	; acumula segundo MAC

			inc	  r16
			andi  r16, MASK	;
			movw  r30, r24  ;
			add	  r30, r16	;
			adc	  r31, r2	;realiza incremento circular na posicao da fifo
			 
			ldd  r18, Z+0	;
			ld	 r19, X+	;
			fmuls r19, r18	;
			movw  r18,r0	;
			add	  r20, r19	; acumula terceiro MAC

			movw  r30, r24	;
			adiw  r30, +7	;aponta ao output
			add	  r30, r17	;
			adc	  r31, r2	;aponta a posicao corrente do output:

			ldd	  r18, Z+0	;
			sub   r20, r18	;acuu -= y[n - 1]
			inc	  r17		;
			andi  r17, MASK	;incremento circular

			movw  r30, r24	;
			adiw  r30, +7	;
			add	  r30, r17	;
			adc   r31, r2	;
			std   Z+0, r20	; guarda output value
	
			std	  Y+1, r17	; guarda output corrente
			mov   r24, r18	; finaliza pid

			pop	r19			;
			pop r18	
			pop r17
			pop r16
			pop r2
			pop r1
			pop r0
			
			ret

.end