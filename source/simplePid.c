/*
 * simplePid.c
 *
 * Created: 16/10/2014 19:54:38
 *  Author: felipe.neves
 */ 

#include "simplePID.h"

/*
 *	Variaveis desse modulo:
 */

PidCtl_t PidTbl[NUMBER_OF_PID_CONTROLLLERS]; //Tabela de blocos de controle PID
uint8_t  freePid = 0;						 //Numero de pids usados

/*
 * PidCreate()
 */
Handler_t PidCreate(iq8_t kp, iq8_t ki, iq8_t kd)
{	
	//checa se tem estrutura disponivel:
	if(freePid >= NUMBER_OF_PID_CONTROLLLERS)
	{
		return(0);		
	}
	
	//Inicializa bloco de controle livre:
	PidTbl[freePid].kd = kd;
	PidTbl[freePid].ki = ki;
	PidTbl[freePid].kp = kp;
	
	//Seta os coeficientes:
	PidTbl[freePid].coefSet[0] = kp+ki+kd;
	PidTbl[freePid].coefSet[1] = kp+ki-(kd + kd);
	PidTbl[freePid].coefSet[2] = kd;
	
	//Limpa todos os states:
	PidTbl[freePid].inputState[0] = 0;
	PidTbl[freePid].inputState[1] = 0;
	PidTbl[freePid].inputState[2] = 0;
	PidTbl[freePid].inputState[3] = 0;

	PidTbl[freePid].outputState[0] = 0;
	PidTbl[freePid].outputState[1] = 0;
	PidTbl[freePid].outputState[2] = 0;
	PidTbl[freePid].outputState[3] = 0;
	
	PidTbl[freePid].inputPtr  = 0;
	PidTbl[freePid].outputPtr = 0;
	
	freePid++;
	
	//Retorna em forma de handler:
	return((Handler_t) &PidTbl[freePid-1]);
	
}

/*
 * PidTune()
 */
void PidTune(Handler_t h, iq8_t kp, iq8_t ki, iq8_t kd)
{
	PidCtlPtr_t ptr = (PidCtlPtr_t)h;
	
	//checa se é valido:
	if(h == 0x0000) return;
	
	//ajusta coeficientes:
	ptr->kd = kd;
	ptr->ki = ki;
	ptr->kp = kp;
	
	ptr->coefSet[0] = kp+ki+kd;
	ptr->coefSet[1] = kp+ki-(kd + kd);
	ptr->coefSet[2] = kd;	
}
