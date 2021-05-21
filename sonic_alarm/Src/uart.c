#include "main.h"

UART_HandleTypeDef UartHandle;
void Usart_Init(void)
{

  UartHandle.Instance        = USART1;
  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;//8B=7+1(7不能中文)
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;

  if (HAL_UART_Init(&UartHandle) != HAL_OK){Error_Handler();}}

int fputc(int ch, FILE *f)	
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

