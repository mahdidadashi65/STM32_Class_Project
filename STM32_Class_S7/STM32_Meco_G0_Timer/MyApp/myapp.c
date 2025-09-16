#include "myapp.h"
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <i2c.h>
#include "tim.h"


#define RXBUFFERSIZE 10
/* Buffer used for reception */
uint8_t aRxBuffer_it[RXBUFFERSIZE];
__IO ITStatus UartReady = RESET;


#define uart_cmd huart1


#define MAX_RX3_SIZE 100
uint8_t data0=1;
uint8_t rx_buffer3[MAX_RX3_SIZE];
uint8_t rx_counter3=0;

void cmd_parser(uint8_t len,uint8_t* cmd);

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


// sample1
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
//{
//  /* Set transmission flag: transfer complete */
//  UartReady = SET;
//}


void test_read_read_uart_interrupt(void)
{	   
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

//sample2
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{ 
  rx_buffer3[rx_counter3]=data0;

  if(rx_buffer3[rx_counter3]==  '\n')
  {
    cmd_parser(rx_counter3,rx_buffer3);
    rx_counter3=0;
  }

  rx_counter3++;
  if(rx_counter3>MAX_RX3_SIZE)rx_counter3=0;

  if (HAL_UART_Receive_IT(&huart1, (uint8_t *)&data0, 1) != HAL_OK)
  {
    Error_Handler();
  }
  
}


int val=100;

void cmd_parser(uint8_t len,uint8_t* cmd)
{
  printf("New CMD: %d %x %x %s\r\n",len , cmd[0],cmd[len-1],cmd);
  
  uint8_t cmd2[100];
  
  for(int i=0; i<len;i++)
  {
    cmd2[i]=toupper(cmd[i]);
  }
  

    if (strstr((const char*)cmd2, "ON") != NULL) 
  {
      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_SET);
      printf("LED ON\r\n");
  }
  

  
   if (strstr((const char*)cmd2, "OFF") != NULL) 
  {
      HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_RESET);
      printf("LED OFF\r\n");
  }
  
  char* cmd_pwm="PWM";
  if (strstr((const char*)cmd2, cmd_pwm) != NULL) 
  {
    int pwm_val=0;
    char* pwm_loc=0;
    pwm_loc = strstr((const char*)cmd2, cmd_pwm);
    pwm_val = atoi(pwm_loc+strlen(cmd_pwm));
    printf("pwm: %d\r\n",pwm_val);
  }
  
    char* led_pwm="LED";
  if (strstr((const char*)cmd2, led_pwm) != NULL) 
  {
    int pwm_val=0;
    char* pwm_loc=0;
    pwm_loc = strstr((const char*)cmd2, led_pwm);
    pwm_val = atoi(pwm_loc+strlen(led_pwm));
    printf("led: %d\r\n",pwm_val);
  }
  
  
  char* led_flt="FLT";
  if (strstr((const char*)cmd2, led_flt) != NULL) 
  {
    float pwm_val=0;
    char* pwm_loc=0;
    pwm_loc = strstr((const char*)cmd2, led_flt);
    pwm_val = atoi(pwm_loc+strlen(led_flt));
    printf("flt: %.2f\r\n",pwm_val/100);
  }
  
  
  
  char* cmd_out="OUT";
  if (strstr((const char*)cmd2, cmd_out) != NULL) 
  {
    int pwm_val=0;
    char* pwm_loc=0;
    pwm_loc = strstr((const char*)cmd2, cmd_out);
    pwm_val = atoi(pwm_loc+strlen(cmd_out));
    printf("cmd_out: %d\r\n",pwm_val);
    // write out val to port
  }
  
  char* cmd_in="INP";
  if (strstr((const char*)cmd2, cmd_in) != NULL) 
  {
//    int pwm_val=0;
//    char* pwm_loc=0;
//    pwm_loc = strstr((const char*)cmd2, cmd_in);
//    pwm_val = atoi(pwm_loc+strlen(cmd_in));
//    printf("val_in: %d\r\n",pwm_val);
    
    //read in val from port
    uint8_t port_in_val=val++;
    char buffer[100];
    sprintf(buffer,"PORT IN:%d\r\n",port_in_val);
    HAL_UART_Transmit(&uart_cmd,(const uint8_t*)buffer,strlen(buffer),100);
  }
  
}

void test_read_read_uart_interrupt2(void)
{	   
  if (HAL_UART_Receive_IT(&huart1, (uint8_t *)&data0, 1) != HAL_OK)
  {
    Error_Handler();
  }
  
	while(1)
	{
    HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);  
		HAL_Delay(100);
	}
}

//***************
#define EEPROM_ADDRESS          0xA0   /* Address A0 == MB1020 A-01 - Address A6 == MB1020 A-02 */
#define EEPROM_PAGESIZE         4     /* RF EEPROM ANT7-M24LR used */

void test_read_eeprom(void)
{

  #define I2C_RXBUFFERSIZE 40
  /* Buffer used for transmission */
uint8_t aTxBuffer[] = "test data";

/* Buffer used for reception */
uint8_t aRxBuffer[I2C_RXBUFFERSIZE];

/* Useful variables during communication */
uint16_t Memory_Address=0;
  
//      /* Write EEPROM_PAGESIZE */
//  if(HAL_I2C_Mem_Write(&hi2c1 , (uint16_t)EEPROM_ADDRESS, Memory_Address, I2C_MEMADD_SIZE_16BIT, (uint8_t*)(aTxBuffer + Memory_Address), EEPROM_PAGESIZE,500)!= HAL_OK)
//  {
//    /* Writing process Error */
//    Error_Handler();
//  }


  /*##-3- Start reading process ##############################################*/
  if (HAL_I2C_Mem_Read(&hi2c1, (uint16_t)EEPROM_ADDRESS, 0, I2C_MEMADD_SIZE_16BIT, (uint8_t *)aRxBuffer, I2C_RXBUFFERSIZE,500) != HAL_OK)
  {
    /* Reading process Error */
    Error_Handler();
  }
  while(1)
	{
    HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);  
		HAL_Delay(100);
	}
  
}


extern void ModbusRTUTask(void const * argument);

__attribute__((weak,noreturn))
void __aeabi_assert (const char *expr, const char *file, int line) 
{
}

//void test_modbus_slave(void)
//{
//  
//  ModbusRTUTask(NULL);
//    while(1)
//	{
//    HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);  
//		HAL_Delay(100);
//	}
//  
//}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == &htim14)
  {
    HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
    HAL_GPIO_TogglePin(SSEL_GPIO_Port,SSEL_Pin);
  }
  else if (htim == &htim2)
  {
    HAL_GPIO_TogglePin(PA0_GPIO_Port,PA0_Pin);
  }

}


void timer_test1(void)
{
    
   HAL_TIM_Base_Start_IT(&htim14);
   __HAL_TIM_SetAutoreload(&htim14,500-1);
  
  HAL_TIM_Base_Start_IT(&htim2);
   __HAL_TIM_SetAutoreload(&htim2,1000-1);

  while(1)
  {
      HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		  HAL_Delay(1000);
  }
  
}

void myapp(void)
{
  printf("Start App\r\n");
	//test_led_blink();
	//test_read_key();
  //test_read_send_uart();
  //test_read_read_uart_polling();
  //test_read_read_uart_interrupt();
  //test_read_read_uart_interrupt2();
  
  
  //test_read_eeprom();
  //test_modbus_slave();
  timer_test1();
}
