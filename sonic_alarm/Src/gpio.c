#include "gpio.h"

uint16_t i_exti;
void GPIO_Init(void){
	RCC->APB2ENR=(0x1fd<<0*4);//A_ABCDEFG
	GPIOB->CRL&=~(0xf0000f);
	GPIOB->CRL|= (0x100001<<0*4);//PB0PB5
	GPIOB->ODR|=(1<<0);
}

void EXIT_Init(){
	
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.Mode =GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pin=GPIO_PIN_4;
	GPIO_InitStruct.Pull=GPIO_PULLUP;
	
	HAL_GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI4_IRQn,0,0);
	//HAL_NVIC_GetPriorityGrouping();
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

/*
  void EXTI4_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
	i_exti++;printf("i_exti=%2d\r\n",i_exti);
}
*/


