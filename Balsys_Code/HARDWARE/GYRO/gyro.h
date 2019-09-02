#ifndef __GYRO_H
#define __GYRO_H
#include "stm32f10x.h"

extern float Yangel;
extern float Yspeed;
extern float Xangel;
extern float Xspeed;
extern float Zangel;
extern float Zspeed;
extern u32   Tms;

void read_gyro(void);

#endif

//------------------End of File----------------------------
