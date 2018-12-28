#
# TODO: Develop a better build system :P
#
MCU?=atmega32 
CC=avr-gcc
AR=avr-ar
INC = ../build/include
LIB  = ../build/lib
CFLAGS= -Wall -g2 -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -Iinclude/
SRC = pi_controller.c

all:
	@echo "[CC] Building AvrSimplePID!"
	@$(CC) $(CFLAGS) -mmcu=$(MCU) -c $(SRC) 
	@echo "[AR] Packing lib and cleaning up!"
	@mkdir build 
	@mv LibSimplePID.a build/lib/ 
	@cp include/simplePID.h  build/include/
	@rm -f $(OBJS) LibSimplePID.a   
	@echo "[CC] AvrSimplePID was built succesfully!"

clean:
	@echo "[CLEAN]: Cleaning !"
	@rm -rf build/
	@echo "[CLEAN]: Done !"

