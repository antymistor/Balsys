#ifndef __MCTR_H
#define __MCTR_H
#include "stm32f10x.h"

typedef enum
{
	forward,
	backward,
	still
}DIRECTION;
void BLMOTOR_init(void);
void motor_ctr(u8 num,DIRECTION dir,u16 power);
#endif

//------------------End of File----------------------------
