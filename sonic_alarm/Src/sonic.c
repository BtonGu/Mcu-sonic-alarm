/*
Echo=PE4 in_EXTI
Trig=PE6 pushpull
使用方法：
Sonic_Init();
TRIG_pulse();
while(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4))
{
   if(TIM3->CNT>1000){
	 printf("超声波_TimeOut!");
	 break ;
 }
}TIM3->CNT=0;
*/
#include "sonic.h"
void Sonic_Init(void){
	TIM_HandleTypeDef    htim3;
	
	GPIOE->CRL &=~(0x0f000000);
  GPIOE->CRL |= (0x01<<6*4);
	//PE4配置EXTI,见GPIO.c
	
	__HAL_RCC_TIM3_CLK_ENABLE();
  htim3.Instance = TIM3;
  /* Initialize TIMx peripheral as follows:
       + Period = 10000 - 1
       + Prescaler = (SystemCoreClock/10000) - 1
       + ClockDivision = 0
       720* 1000 000/72000 000
  */
  htim3.Init.Period            = 65535;
  htim3.Init.Prescaler         = 72*10-1;  
  htim3.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim3.Init.RepetitionCounter = 0;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;	
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK){Error_Handler();}
	HAL_TIM_Base_Start(&htim3);
	
}
      
void TRIG_pulse()
{

	 GPIOE->ODR |= (1<<6);
	 delay_us(50);
	 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_RESET);
}
 

/*
  void EXTI4_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
	printf("CNT=%2d\r\n",(volatile uint32_t)TIM3->CNT/6-85);
}
*/





