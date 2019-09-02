#include "IOI2C.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "gyro.h"
#include "REG.h"

float Yangel=0;
float Xangel=0;
float Zangel=0;
float Xspeed=0;
float Zspeed=0;
float Yspeed=0;
u32   Tms=0;

void ShortToChar(short sData,unsigned char cData[])
{
	cData[0]=sData&0xff;
	cData[1]=sData>>8;
}

short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}


void read_gyro(void)
{
	u8 chrTemp[6];
	
	 IICreadBytes(0x50, MMSS, 4,&chrTemp[0]);
	Tms=(u32)(chrTemp[3]<<8|chrTemp[2])+(u32)chrTemp[0]*60*1000+chrTemp[1]*1000;
  IICreadBytes(0x50, GX, 6,&chrTemp[0]);
	Xspeed=(float)CharToShort(&chrTemp[0])/32768*2000;
	Yspeed=(float)CharToShort(&chrTemp[2])/32768*2000;
	Zspeed=(float)CharToShort(&chrTemp[4])/32768*2000;
	
	
	IICreadBytes(0x50,Roll, 6,&chrTemp[0]);
	Xangel=(float)CharToShort(&chrTemp[0])/32768*180;
	if(Xangel>0){Xangel=180.f-Xangel;}
	else{Xangel=-Xangel-180.f;}
	Yangel=(float)CharToShort(&chrTemp[2])/32768*180;;
	Zangel=(float)CharToShort(&chrTemp[4])/32768*180;;
}


