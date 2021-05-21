#include "i2c.h"

#define I2Cx                            I2C1
#define I2Cx_CLK_ENABLE()               __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE() 

#define I2Cx_FORCE_RESET()              __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()            __HAL_RCC_I2C1_RELEASE_RESET()

#define I2Cx_SCL_PIN                    GPIO_PIN_6
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SDA_PIN                    GPIO_PIN_7
#define I2Cx_SDA_GPIO_PORT              GPIOB
#define I2C_SPEEDCLOCK   400000
#define I2C_DUTYCYCLE    I2C_DUTYCYCLE_16_9


I2C_HandleTypeDef    I2cHandle;
void I2C_Init(void){

	I2Cx_CLK_ENABLE(); 
	//GPIOB->CRL &=~(0xff000000);//可以省略
	GPIOB->CRL |= (0xff000000);//50Mz AF_OD
	GPIOB->ODR |=(3<<6);       //开漏还能上拉？
	
	I2cHandle.Instance             = I2Cx;
  I2cHandle.Init.ClockSpeed      = I2C_SPEEDCLOCK;
  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE;
  I2cHandle.Init.OwnAddress1     = 0;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.OwnAddress2     = 0;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;  
  
  if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
 
	
	
	

}



//void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
//{

//  __HAL_RCC_I2C1_CLK_ENABLE();
//  //GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;

//	 __HAL_RCC_GPIOB_CLK_ENABLE() ;
//	GPIOB->CRL &=~(0xff000000);//可以省略
//	GPIOB->CRL |= (0xff000000);//50Mz AF_OD
//	GPIOB->ODR |=(3<<6);       //开漏还能上拉？
	
	
//}
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
//  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  I2Cx_SCL_GPIO_CLK_ENABLE();
  I2Cx_SDA_GPIO_CLK_ENABLE();
  /* Enable I2Cx clock */
  

  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* I2C TX GPIO pin configuration  */
//  GPIO_InitStruct.Pin       = I2Cx_SCL_PIN;
//  GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
//  GPIO_InitStruct.Pull      = GPIO_PULLUP;
//  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
//  HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);
//    
//  /* I2C RX GPIO pin configuration  */
//  GPIO_InitStruct.Pin       = I2Cx_SDA_PIN;
//  HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);
//	
 
}
