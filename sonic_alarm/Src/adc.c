#include "adc.h"



ADC_HandleTypeDef    hadc1;
void ADC1_Init(void){
	ADC_ChannelConfTypeDef   sConfig;
	
	hadc1.Instance = ADC1;
  hadc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode          = ADC_SCAN_DISABLE;               /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
  hadc1.Init.ContinuousConvMode    = DISABLE;                       /* Continuous mode disabled to have only 1 rank converted at each conversion trig, and because discontinuous mode is enabled */
  hadc1.Init.NbrOfConversion       = 1;                             /* Sequencer of regular group will convert the 3 first ranks: rank1, rank2, rank3 */
  //hadc1.Init.DiscontinuousConvMode = ENABLE;                        /* Sequencer of regular group will convert the sequence in several sub-divided sequences */
  //hadc1.Init.NbrOfDiscConversion   = 1;                             /* Sequencer of regular group will convert ranks one by one, at each conversion trig */
  hadc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;            /* Trig of conversion start done manually by software, without external event */

  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    /* ADC initialization error */
    Error_Handler();
  }
                                               
  sConfig.Channel      = ADC_CHANNEL_14;
  sConfig.Rank         = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
  
  HAL_ADC_ConfigChannel(&hadc1, &sConfig) ;
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc){
	RCC->APB2ENR|=(1<<9);
	GPIOC->CRL&=~(0xf0000); //PC4-CRL 0000B
}

