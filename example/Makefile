#
# TODO: Develop a better build system :P
#
MCU?=atmega32 
CC=avr-gcc
HEX=avr-objcopy
HEXFLAGS= -j .text -j .data -O ihex
INC = include
LIB  = lib
CFLAGS= -Wall -g2 -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields 
SRC = pi_controller.c
CFLAGS += -I$(INC) 

all:
	@echo "[CC] Building pi controller example!"
	@$(CC) $(CFLAGS) -mmcu=$(MCU) $(SRC) -o pi_controller.elf -L$(LIB) -lSimplePID
	@echo "[HEX] Generating hex file!"
	@$(HEX) $(HEXFLAGS) pi_controller.elf pi_controller.hex
	@echo "[CC] cleaning up and making output folder"
	@mkdir build
	@mv    pi_controller.hex build/
	@rm -f pi_controller.hex pi_controller.elf 
	@echo "[CC] pi controller example was built succesfully!"

clean:
	@echo "[CLEAN]: Cleaning !"
	@rm -rf build/
	@rm -f pi_controller.hex
	@rm -f pi_controller.elf
	@echo "[CLEAN]: Done !"