#include <simplePID.h>

int PidControllerInit(PidController *pid, PidNewCoefficients *coeff) {
	if(!pid)
		return -1;

	if(!coeff) 
		return -1;
	
	//Make a IIR Z-trans filter from PID parameters:
	pid->bn[0] = (coeff->new_kp + coeff->new_ki + coeff->new_kd); 
	pid->bn[1] = (coeff->new_kp + coeff->new_ki) - (coeff->new_kd + coeff->new_kd);
	pid->bn[2] = coeff->new_kd;

	pid->next_xn = 0;
	pid->next_yn = 0;

	pid->xn[0] = 0; 
	pid->xn[1] = 0; 
	pid->xn[2] = 0; 
	pid->xn[3] = 0; 

	pid->yn[0] = 0; 
	pid->yn[1] = 0; 
	pid->yn[2] = 0; 

	return 0;
}

int PidControllerTune(PidController *pid, PidNewCoefficients *coeff) {
	if(!pid)
		return -1;

	if(!coeff) 
		return -1;

	pid->bn[0] = (coeff->new_kp + coeff->new_ki + coeff->new_kd); 
	pid->bn[1] = (coeff->new_kp + coeff->new_ki) - (coeff->new_kd + coeff->new_kd);
	pid->bn[2] = coeff->new_kd;

	pid->xn[0] = 0; 
	pid->xn[1] = 0; 
	pid->xn[2] = 0; 
	pid->xn[3] = 0; 

	pid->yn[0] = 0; 
	pid->yn[1] = 0; 
	pid->yn[2] = 0; 

	return 0;
}
