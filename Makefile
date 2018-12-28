#
# TODO: Develop a better build system :P
#
MCU?=atmega32 
CC=avr-gcc
CFLAGS= -Wall -g2 -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -Iinclude/
SRC = source/simplePID.c source/simplePID_a.s


all:
	@echo "[CC] Building AvrSimplePID!"
	@$(CC) $(CFLAGS) -mmcu=$(MCU) -c $(SRC) 
	@$(AR) -rcs "libSimplePID.a" simplePID.o simplePID_a.o
	@echo "[AR] Packing lib and cleaning up!"
	@mkdir build 
	@mkdir build/include build/lib
	@mv libSimplePID.a build/lib/ 
	@cp include/simplePID.h  build/include/
	@rm -f simplePID.o simplePID_a.o libSimplePID.a   
	@echo "[CC] AvrSimplePID was built succesfully!"

clean:
	@echo "[CLEAN]: Cleaning !"
	@rm -rf build/
	@rm -f $(OBJS) libSimplePID.a   
	@echo "[CLEAN]: Done !"

