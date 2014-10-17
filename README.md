AvrSimplePID
============

Simple digital and fast PID controller for AVR processors by Felipe Neves

- Fast, execute the complete PID loop plus history updtade in 6.5us @ 16MHz
- Light, only 350 bytes of code, with -O0 optmization so if possible to achieve less code size
- Simple, create a pid, tune on the fly, and use it, only 3 apis
- Flexible, in header file the user can configure more than onde PID controller accessing it with the handle
- Clean, source code is clear, the assembly part uses intuitive instructions to processe PID loop,
- Reliable, pid alghoritm is based on 2p2z approximation method, giving better response and granularity
- No saturation, use fractional IQ7 type numbers.


Enjoy it! :)

Felipe.
