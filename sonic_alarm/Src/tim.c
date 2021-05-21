#include "tim.h"
#include "array.h"


TIM_HandleTypeDef    htim2;
void TIM_Init(void){

  /* Set TIMx instance */
  htim2.Instance = TIM2;
  /* Initialize TIMx peripheral as follows:
       + Period = 10000 - 1
       + Prescaler = (SystemCoreClock/10000) - 1
       + ClockDivision = 0
       + Counter direction = Up
  */
  htim2.Init.Period            = 10-1;   //10ms
  htim2.Init.Prescaler         = 72000-1;//1ms
  htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim2.Init.RepetitionCounter = 0;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  
	//HAL_TIM_Base_MspInit
	__HAL_RCC_TIM2_CLK_ENABLE();
	HAL_NVIC_SetPriority(TIM2_IRQn,1,1);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-2- Start the TIM Base generation in interrupt mode ####################*/
  /* Start Channel1 */
  if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
	
	
	
	

}

	void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	Key_Scan();
	//printf("tim_ok");
}

