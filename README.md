AvrSimplePID
============

Simple digital and fast PID controller for AVR processors using fixed point and 
AVR specialized math instructions.

# Features:
- Fast, execute the complete PID loop plus history updtade in 6.5us @ 16MHz
- Light, only 350 bytes of code, with -O0 optmization so if possible to achieve less code size
- Simple, create a pid, tune on the fly, and use it, only 3 apis
- Core implementation uses 2p2z alghoritm written in assembly

# Usage:
 - Just clone this repository to your local machine;
 - You need the avr-gcc + make to build this library, if you dont't have install it;
 - Navigate to this dir until find a Makefile;
 - in your terminal type:

 ```
 $ make all MCU=<mmcu> 
 ```
- where mmcu is the ISA you want to compile supported by avr-gcc;  
- on the build folder you'll find a .a file pĺus .h file, include it on your project and enjoy;

# Example
 Inside of example folder you will find a code which can be used as starting point of your 
 PID control project, it also serves as tutorial on how to use a built library.
 You can also build this file into a flashable hex file by typing inside a terminal:

 ```
 $ make all MCU=<mmcu> 
 ```
- where mmcu is the ISA you want to compile supported by avr-gcc;  
- on the build folder you'll find a .hex file ready to be flashed;

# Support:
 - If you want some help with this work contact me: ryukokki.felipe@gmail.com
