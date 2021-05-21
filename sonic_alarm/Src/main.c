#include "main.h"
#include "gpio.h"//contain EXTI
#include "tim.h"
#include "dht11.h"
#include "lcd.h"
#include "adc.h"
#include "i2c.h"
#include "sonic.h"
#include "syn6288.h"
#include "array.h"
/*把这些全部放入main.h中会带来负担吗 */
int tonic;
void SystemClock_Config(void);
void Error_Handler(void);


int main(void)
{
	uint8_t th,dh;
	uint8_t eeprom,ee=0;
	uint16_t adc;
  uint8_t Kmode=0;
	uint8_t Kflag10=0;
	uint8_t Kflag11=0;
	
  HAL_Init();

  /* Configure the system clock to 72 MHz */
  SystemClock_Config();
	GPIO_Init();
	EXIT_Init();
	Usart_Init();
	LCD_Init();
	TIM_Init();
	ADC1_Init();
	I2C_Init();
  Sonic_Init();
	ArrayKey_Init();
	
  GPIOB->ODR|=(1<<0);
  /* Output a message on Hyperterminal using printf function */
  printf("\n\r UART Printf Example: retarget the C library printf function to the UART\n\r");
  printf("** Test finished successfully. ** \n\r");
	//LCD_ShowString( 30, 40, 200,16,16, "GGG");		//显示一个字符串,12/16字体

  
  /* Infinite loop */
  while (1)
  { printf("\r\n");GPIOB->ODR^=(1<<5);
		printf("keyvalue=%2d\r\n",keyvalue);
		if((keyvalue>=10)&&(keyvalue<=15)) Kmode=keyvalue;
		if(keyvalue==10)Kflag10=~Kflag10;
		if(keyvalue==11)Kflag11=~Kflag11;
		keyvalue=99;
		printf("Kflag10=%2d\r\n",Kflag10);
		
		
		DHT11_Read_Data(&th,&dh);
		printf("temp=%2d,dh=%2d",th,dh);
		printf("温度湿度\r\n");
		
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,100);
		adc=HAL_ADC_GetValue(&hadc1);
		printf("ADC=%2d\r\n",HAL_ADC_GetValue(&hadc1));
		
		LCD_ShowString(30,30,200,16,16,"Sonic:");
		LCD_ShowNum		(100,30,tonic,3,16);
		LCD_ShowString(30,50,200,16,16,"Adc:");
		LCD_ShowNum   (100,50,adc,4,16);
		LCD_ShowString(30,70,200,16,16,"Distan:");
		if(Kflag10)LCD_ShowNum   (100,70,tonic,3,16);
		else			 LCD_ShowNum   (100,70,adc*100/4096,3,16);
		LCD_ShowString(130,70,200,16,16,"cm");
		LCD_ShowString(30,90,200,16,16,"keyvalue:");
    LCD_ShowNum   (100,90,keyvalue,3,16);
		LCD_ShowNum   (30, 110,th,3,16);
    LCD_ShowNum   (100,110,dh,3,16);
		
		if(Kflag11){ ee++;
			LCD_ShowString(30,130,200,16,16,"Alarm_on");
			if(ee>4){  ee=4;
				if(tonic<50)      {SYN_FrameInfo();ee=0;}
				else if(tonic<100){SYN_FrameInfo2();ee=0;}
				else ;
			}		
		}else LCD_ShowString(30,130,200,16,16,"        ");
//	  if(ee%4==0)SYN_FrameInfo();//语音1
//    if(ee%7==0)SYN_FrameInfo2();//语音2
		
    TRIG_pulse();TIM3->CNT=0;
		while(!HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4))
		{
			 if(TIM3->CNT>1000){
			 printf("超声波_TimeOut!");
			 break ;
		 }
		}TIM3->CNT=0;//后面不能有printf的重定向，重写向优先级？？
		//超声波会干扰dht11??
		
    
		
		/*
		HAL_Delay(10);
		if(HAL_I2C_Mem_Read(&I2cHandle,0xA1,ee++,I2C_MEMADD_SIZE_8BIT,&eeprom,1,100)==HAL_ERROR)printf("I2C_Error\r\n");
		HAL_Delay(10);printf("%02d:24c02=%2d\r\n",ee,eeprom);
		if(ee>10)ee=0;
		*/
		
		
		
		HAL_Delay(1000);
  }
}


void EXTI4_IRQHandler(void)
{
	tonic=TIM3->CNT;
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
	tonic=tonic/6;
	printf("CNT=%2dcm\r\n",tonic);
	//printf("EXTI\r\n");
	//printf("CNT=%2dcm\r\n",(volatile uint32_t)TIM3->CNT/6-135);
  //printf("CNT=%2d\r\n",(volatile uint32_t)TIM3->CNT);
		
}





/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 1
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef clkinitstruct = {0};
  RCC_OscInitTypeDef oscinitstruct = {0};
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  oscinitstruct.HSEState        = RCC_HSE_ON;
  oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV1;
  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    while(1);
  }
}

  void Error_Handler(void)
{
	printf("error");
}

void delay_us(uint16_t us)
{
  uint32_t startval,tickn,delays,wait;
 
  startval = SysTick->VAL;
  tickn = HAL_GetTick();//sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
  delays =us * 72; //sysc / 1000 * udelay;
  if(delays > startval)
    {
      while(HAL_GetTick() == tickn);
      wait = 72000 + startval - delays;
      while(wait < SysTick->VAL);
    }
  else
    {
      wait = startval - delays;
      while(wait < SysTick->VAL && HAL_GetTick() == tickn);
    }
}
	




/******************END OF FILE****/
