/*
 * simplePID.h
 *
 * Created: 16/10/2014 19:13:06
 *  Author: felipe.neves
 */ 


#ifndef SIMPLEPID_H_
#define SIMPLEPID_H_

#include <stdint.h>

/*
 *	Number of pid controllers
 */
#define NUMBER_OF_PID_CONTROLLLERS 2

/*
 *	custom pid types:
 */
typedef int8_t    iq8_t;	 //convenient type for IQ8 fractional representation

/*
 *	float to IQ macro
 */
#define FLOAT_TO_Q8(x)  (iq8_t)(x * (float)(1 << 7))


/*
 *	PID control structure
 */
struct pid_
{
	iq8_t inputState[4];	//Estados de entrada
	iq8_t coefSet[3];		//Set de coeficientes bn
	iq8_t outputState[4];	//Estados de saida 

	uint8_t inputPtr;
	uint8_t outputPtr;

	iq8_t kp;				//ganho proporcional
	iq8_t ki;				//ganho integral
	iq8_t kd;				//ganho derivativo
		
};

typedef struct pid_	 PidCtl_t;
typedef struct pid_	*PidCtlPtr_t;
typedef uint16_t Handler_t;


/*
 *	Prototipos
 */

/*!
 * PidCreate()
 * \brief inicializa uma estrutura pid e retorna seu handler	
 * \param
 * \return
 */
Handler_t PidCreate(iq8_t kp, iq8_t ki, iq8_t kd);

/*!
 * PidTune()
 * \brief Ajusta coeficientes de kp, ki e kd	
 * \param
 * \return
 */
void PidTune(Handler_t h, iq8_t kp, iq8_t ki, iq8_t kd);

/*!
 * PidCompute()
 * \brief Computa um valor de saida para o PID	
 * \param
 * \return
 */
extern iq8_t PidCompute(Handler_t h, iq8_t ref, iq8_t smp );



#endif /* SIMPLEPID_H_ */