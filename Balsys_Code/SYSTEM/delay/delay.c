#include "delay.h"
#include "misc.h"	 
#include "stm32f10x_tim.h"
static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数

u16 t_us=0;
u16 t_ms=0;
u16 t_sec=0;
u16 t_min=0;
u16 t_hour=0;

void SysTick_init(u8 SYSCLK,u16 nms)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	SysTick->VAL =0x00;           //清空计数器
	SysTick->LOAD = nms*SYSCLK*125;//72MHz,最大1864ms
	SysTick->CTRL=3;//bit2清空,选择外部时钟  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
unsigned char ucTimeFlag=0,ucDelayFlag=0;
void SysTick_Handler(void) 
{      
	ucTimeFlag=1;	if (ucDelayFlag) ucDelayFlag--;
}			
unsigned char CheckSystemTick(void)
{	
	if (ucTimeFlag) 
	{
		ucTimeFlag = 0;
		return(1);
	}
	else 
		return(0);
}				    
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
/**************************实现函数********************************************
*函数原型:		void delay_ms(u16 nms)
*功　　能:		毫秒级延时  延时nms  nms<=1864 
*******************************************************************************/

void delay_ms(u16 nms)
{	 		  	  
  u32 Start = 	SysTick->VAL;
	u32 Span =(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	u32 End = 0;
		ucDelayFlag=Span/SysTick->LOAD;
		End = Span%SysTick->LOAD;
	if (Start>End)
	{
			End = Start-End;
		  while(ucDelayFlag);
			if (End<10)
				while(SysTick->VAL>10);
			else			
				while(SysTick->VAL>End); 
	}
	else
	{
			ucDelayFlag++;
			End = (Start+SysTick->LOAD)-End;
		  while(ucDelayFlag);			
			if (End<10)
				while(SysTick->VAL>10);
			else			
				while(SysTick->VAL>End); 
	}		  	    
}   

//延时nus
//nus为要延时的us数.
/**************************实现函数********************************************
*函数原型:		void delay_us(u32 nus)
*功　　能:		微秒级延时  延时nus  nms<=1864 
*******************************************************************************/		    								   
void delay_us(u32 nus)
{		
	u32 Start = 	SysTick->VAL;
	u32 Span =(u32)nus*fac_us;//时间加载(SysTick->LOAD为24bit)
	u32 End = 0;
		ucDelayFlag=Span/SysTick->LOAD;
		End = Span%SysTick->LOAD;
	if (Start>End)
	{
			End = Start-End;
		  while(ucDelayFlag);
			if (End<10)
				while(SysTick->VAL>10);
			else			
				while(SysTick->VAL>End); 
	}
	else
	{
			ucDelayFlag++;
			End = (Start+SysTick->LOAD)-End;
		  while(ucDelayFlag);			
			if (End<10)
				while(SysTick->VAL>10);
			else			
				while(SysTick->VAL>End); 
	}		  	    
}

//------------------End of File----------------------------
