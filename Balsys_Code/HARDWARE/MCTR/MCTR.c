#include "MCTR.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
void BLMOTOR_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	TIM_OCInitTypeDef              TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//PWM_out related Pins
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//Direction ctr related Pins
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_DeInit(TIM2);
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period=999;                
  TIM_TimeBaseStructure.TIM_Prescaler=71;     
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                              
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;    
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    
  TIM_OCInitStructure.TIM_Pulse=0;
  
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM2,&TIM_OCInitStructure);   
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_OC3Init(TIM2,&TIM_OCInitStructure);  
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_OC4Init(TIM2,&TIM_OCInitStructure);   
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

  TIM_OC1Init(TIM3,&TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2Init(TIM3,&TIM_OCInitStructure);   
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_Cmd(TIM2,ENABLE);
	TIM_CtrlPWMOutputs(TIM2,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
}

void motor_ctr(u8 num,DIRECTION dir,u16 power)
{
switch (num)
	{
		case 1:
			if(dir==forward){GPIO_ResetBits(GPIOA,GPIO_Pin_4);TIM_SetCompare1(TIM2,power);}
			else if(dir==backward){GPIO_SetBits(GPIOA,GPIO_Pin_4);TIM_SetCompare1(TIM2,power);}
			else{TIM_SetCompare1(TIM2,0);}
			break;
		case 2:
			if(dir==forward){GPIO_SetBits(GPIOA,GPIO_Pin_5);TIM_SetCompare2(TIM2,power);}
			else if(dir==backward){GPIO_ResetBits(GPIOA,GPIO_Pin_5);TIM_SetCompare2(TIM2,power);}
			else{TIM_SetCompare2(TIM2,0);}
			break;
		case 3:
			if(dir==forward){GPIO_SetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM3,power);}
			else if(dir==backward){GPIO_ResetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM3,power);}
			else{TIM_SetCompare1(TIM3,0);}
			break;
		case 4:
			if(dir==forward){GPIO_ResetBits(GPIOB,GPIO_Pin_1);TIM_SetCompare3(TIM2,power);}
			else if(dir==backward){GPIO_SetBits(GPIOB,GPIO_Pin_1);TIM_SetCompare3(TIM2,power);}
			else{TIM_SetCompare3(TIM2,0);}
			break;
		case 5:
			if(dir==forward){GPIO_SetBits(GPIOB,GPIO_Pin_12);TIM_SetCompare4(TIM2,power);}
			else if(dir==backward){GPIO_ResetBits(GPIOB,GPIO_Pin_12);TIM_SetCompare4(TIM2,power);}
			else{TIM_SetCompare4(TIM2,0);}
			break;
		case 6:
			if(dir==forward){GPIO_SetBits(GPIOB,GPIO_Pin_13);TIM_SetCompare2(TIM3,power);}
			else if(dir==backward){GPIO_ResetBits(GPIOB,GPIO_Pin_13);TIM_SetCompare2(TIM3,power);}
			else{TIM_SetCompare2(TIM3,0);}
			break;
			
		default:break;
	}
}

