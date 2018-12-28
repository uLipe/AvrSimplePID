#ifndef F_CPU
#define F_CPU 16000000UL 
#endif
 
#include <avr/io.h>
#include <util/delay.h>                
#include <simplePID.h>

static PidController pi_controller;
static PidNewCoefficients pi_coeff;

iq8_t StateEstimator(void) {
    //TODO: fill here your sensors readings:
    return FLOAT_TO_Q8(0.5f);
}

void Command(iq8_t command) {
    //TODO: actuate on plant, eg.: PWM:
    (void) command;
}

void main(void) {
    //Make a PI controller:
    pi_coeff.new_ki = FLOAT_TO_Q8(0.1f);
    pi_coeff.new_kp = FLOAT_TO_Q8(1.0f);

    //FIRST: initialize your PID controller:
    PidControllerInit(&pi_controller,
                      &pi_coeff);

    while(1) {
        delay_ms(2); //Simulate a plant running at 500Hz:
        //SECOND: Read sensor and compute next command:
        iq8_t command = PidControllerUpdate(&pi_controller, FLOAT_TO_Q8(1.0), StateEstimator());
        //THIRD: update actuator:
        Command(command);
    }                  
} 