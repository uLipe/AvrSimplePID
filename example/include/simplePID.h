#ifndef SIMPLEPID_H_
#define SIMPLEPID_H_

#include <stdint.h>

typedef int8_t  iq8_t;	 //convenient type for IQ8 fractional representation
#define FLOAT_TO_Q8(x)  (iq8_t)(x * (float)(1 << 7))

typedef struct {
	iq8_t xn[4];
	iq8_t bn[3];		
	iq8_t yn[4];	 
	uint8_t next_xn;
	uint8_t next_yn;
}PidController;

typedef struct {
	iq8_t new_kp;
	iq8_t new_ki;
	iq8_t new_kd;
}PidNewCoefficients;

/**
 *	@brief initializes a pid controller block
 *  @param pid - target pid controller to be initialized
 * 	@param coeff - initial coefficients set of pid controller
 *  @return 0 on success, otherwise -1
 */  
int PidControllerInit(PidController *pid, PidNewCoefficients *coeff);

/**
 *  @brief tune pid coefficients
 *  @param pid - target pid controller to be initialized
 * 	@param coeff - initial coefficients set of pid controller
 *  @return 0 on success, otherwise -1
 */ 
int PidControllerTune(PidController *pid, PidNewCoefficients *coeff);

/**
 * @brief update pid controller and compute new command value
 * @param pid - pid to be updated
 * @param reference - desired value
 * @param feedback - measured value
 * @return - new command value otherwise 0
 * @note this function MUST be called periodically at sample rate 
 *       desired by the controller 
 */ 
extern iq8_t PidControllerUpdate(PidController *pid, iq8_t reference, iq8_t feedback);

#endif /* SIMPLEPID_H_ */