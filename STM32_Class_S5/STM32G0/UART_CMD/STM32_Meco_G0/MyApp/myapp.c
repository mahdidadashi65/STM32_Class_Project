#include "myapp.h"
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include <stdio.h>


#define RXBUFFERSIZE 10
/* Buffer used for reception */
uint8_t aRxBuffer_it[RXBUFFERSIZE];
__IO ITStatus UartReady = RESET;





#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}


void test_led_blink(void)
{
	while(1)
	{	
		// LED ON
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_RESET);
		HAL_Delay(100);
		// LED OFF
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_SET);
		HAL_Delay(100);
		
	}
}



void test_read_key(void)
{
	
	while(1)
	{
   if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin)==0)
	 {
		 		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_RESET);
	 }
	 else
	 {
		 		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_SET);
	 }
		
			
		HAL_Delay(10);
	}
}


void test_read_send_uart(void)
{
	
	while(1)
	{
       
    HAL_UART_Transmit(&huart1,"UART1\r\n",7,100);
    HAL_UART_Transmit(&huart3,"UART3\r\n",7,100);
    HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
    printf("Log\r\n");


		HAL_Delay(1000);
	}
}

void test_read_read_uart_polling(void)
{	
  uint8_t aRxBuffer[10];
  HAL_StatusTypeDef status;
	while(1)
	{
    status = HAL_UART_Receive(&huart1, (uint8_t *)&aRxBuffer, 10, 2000);
    if(status == HAL_OK)
    {
        printf("St:%d %x\r\n",status,aRxBuffer[0]); 
    }
    HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);  
		HAL_Delay(100);
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  Error_Handler();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set transmission flag: transfer complete */
  UartReady = SET;
}

void test_read_read_uart_interrupt(void)
{	 
  HAL_StatusTypeDef status;
  
  if (HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer_it, RXBUFFERSIZE) != HAL_OK)
  {
    Error_Handler();
  }
  
	while(1)
	{
    if(UartReady == SET)
    {
      UartReady = RESET;
      printf("Data:%x\r\n",aRxBuffer_it[0]);
      if (HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer_it, RXBUFFERSIZE) != HAL_OK)
      {
        Error_Handler();
      }      
    }
    HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);  
		HAL_Delay(100);
	}
}

void myapp(void)
{
	//test_led_blink();
	//test_read_key();
  //test_read_send_uart();
  //test_read_read_uart_polling();
  test_read_read_uart_interrupt();

}
