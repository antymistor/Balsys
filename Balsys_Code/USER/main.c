#include "IOI2C.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "REG.h"
#include "gyro.h"
#include "MCTR.h"
 int main(void)
 {	
	
	SysTick_init(72,10);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(115200);	
	uart3_init(115200);
	IIC_Init();
  BLMOTOR_init();
	while (1)
	{
		delay_ms(100);
		read_gyro();
		printf("%.2f\r\n",Yangel);

	}


}
 
