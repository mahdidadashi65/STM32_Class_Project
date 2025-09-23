#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "adc.h"
#include "tim.h"
#include "stdio.h"
#include "stdbool.h"

#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF); 

  return ch;
}



void test_led(void)
{
  while (1)
  {
    
    HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
    HAL_Delay(100);
    
  }
}

void test_uart(void)
{
  while (1)
  {
    
    HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
    HAL_Delay(100);
    HAL_UART_Transmit(&huart3,"Hello\r\n",7,100);
    
  }
}


void test_printf(void)
{
  while (1)
  {
    
    HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
    HAL_Delay(100);
    printf("Hello %d\r\n",5);
    
  }
}

long map(long x, long in_min, long in_max, long out_min, long out_max) 
{ 
    return (x - in_min) * (out_max - out_min + 1) / (in_max - in_min + 1) + out_min;
}

void test_adc(void)
{
  int adc_voltage_mv = 0;
  int adc_val = 0;
  
  while (1)
  {
    
    HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
    HAL_Delay(100);
    
     /*##-3- Start the conversion process #######################################*/  
    if(HAL_ADC_Start(&hadc1) != HAL_OK)
    {
      /* Start Conversation Error */
      Error_Handler();
    }
    
    /*##-4- Wait for the end of conversion #####################################*/  
     /*  Before starting a new conversion, you need to check the current state of 
          the peripheral; if it’s busy you need to wait for the end of current
          conversion before starting a new one.
          For simplicity reasons, this example is just waiting till the end of the 
          conversion, but application may perform other tasks while conversion 
          operation is ongoing. */
    HAL_ADC_PollForConversion(&hadc1, 10);
    
    /* Check if the continuous conversion of regular channel is finished */
    if((HAL_ADC_GetState(&hadc1) & HAL_ADC_STATE_EOC_REG) == HAL_ADC_STATE_EOC_REG)
    {
      /*##-5- Get the converted value of regular channel  ######################*/
      adc_val = HAL_ADC_GetValue(&hadc1);
    }
  
    adc_voltage_mv = map(adc_val, 0, 4095, 0, 3300);
    printf("adc_voltage_mv:%d mV\r\n",adc_voltage_mv);
    
  }
}



//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
//{
//  int adc_voltage_mv = 0;
//  int adc_val = 0;
//  /* Get the converted value of regular channel */
//  adc_val = HAL_ADC_GetValue(AdcHandle);
//  adc_voltage_mv = map(adc_val, 0, 4095, 0, 3300);
//  printf("adc_voltage_mv:%d mV\r\n",adc_voltage_mv);
//}




void test_adc_int(void)
{

  
  while (1)
  {
    
    HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
    HAL_Delay(1000);
    
      /*##-3- Start the conversion process and enable interrupt ##################*/  
    if(HAL_ADC_Start_IT(&hadc1) != HAL_OK)
    {
      /* Start Conversation Error */
      Error_Handler();
    }
  

    
  }
}

uint16_t uhADCxConvertedValue[10000] = {0};

bool adc_convert_status=false;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
  HAL_GPIO_TogglePin(LOGIC_GPIO_Port,LOGIC_Pin);
  adc_convert_status =  true;
}

void test_adc_dma(void)
{
 int adc_voltage_mv = 0;
  

  
  while (1)
  {
    
    HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
    HAL_Delay(1000);
   
        /*##-3- Start the conversion process and enable interrupt ##################*/
  /* Note: Considering IT occurring after each number of ADC conversions      */
  /*       (IT by DMA end of transfer), select sampling time and ADC clock    */
  /*       with sufficient duration to not create an overhead situation in    */
  /*        IRQHandler. */ 
    adc_convert_status=false;
    HAL_GPIO_TogglePin(LOGIC_GPIO_Port,LOGIC_Pin);

  if(HAL_ADC_Start_DMA(&hadc1, (uint32_t*)uhADCxConvertedValue, 10000) != HAL_OK)
  {
    /* Start Conversation Error */
    Error_Handler(); 
  }
  
    adc_voltage_mv = map(uhADCxConvertedValue[0], 0, 4095, 0, 3300);
    printf("adc_voltage_mv:%d mV\r\n",adc_voltage_mv);

  }
}


void test_adc_pwm(void)
{
  int pwm_percent = 0;
  int adc_val = 0;
  
  
  __HAL_TIM_SetAutoreload(&htim1,100-1);
  __HAL_TIM_PRESCALER(&htim1,((84000000/1000)/100)+1);
  __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,40);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  
  while (1)
  {
    
    //HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);
    HAL_Delay(100);
    
     /*##-3- Start the conversion process #######################################*/  
    if(HAL_ADC_Start(&hadc1) != HAL_OK)
    {
      /* Start Conversation Error */
      Error_Handler();
    }
    
    /*##-4- Wait for the end of conversion #####################################*/  
     /*  Before starting a new conversion, you need to check the current state of 
          the peripheral; if it’s busy you need to wait for the end of current
          conversion before starting a new one.
          For simplicity reasons, this example is just waiting till the end of the 
          conversion, but application may perform other tasks while conversion 
          operation is ongoing. */
    HAL_ADC_PollForConversion(&hadc1, 10);
    
    /* Check if the continuous conversion of regular channel is finished */
    if((HAL_ADC_GetState(&hadc1) & HAL_ADC_STATE_EOC_REG) == HAL_ADC_STATE_EOC_REG)
    {
      /*##-5- Get the converted value of regular channel  ######################*/
      adc_val = HAL_ADC_GetValue(&hadc1);
    }
  
    pwm_percent = map(adc_val, 0, 4095, 0, 100);
    printf("pwm:%d %%\r\n",pwm_percent);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1,pwm_percent);
    
  }
}

void MyApp(void)
{
   
  //test_led();
  //test_uart();
  //test_printf();
  //test_adc();
  //test_adc_int();
  //test_adc_dma();
  test_adc_pwm();
  
}
