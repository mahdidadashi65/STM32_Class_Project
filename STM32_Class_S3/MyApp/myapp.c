#include "myapp.h"
#include "main.h"
#include "gpio.h"


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

void test_led_7seg_1x(void)
{
		while(1)
	{
		
		// LED ON
		HAL_GPIO_WritePin(SEGA_GPIO_Port, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGG_Pin,GPIO_PIN_RESET);

		HAL_Delay(100);
		// LED OFF
		HAL_GPIO_WritePin(SEGA_GPIO_Port, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGG_Pin,GPIO_PIN_SET);

		HAL_Delay(100);
		
	}
}

void test_led_7seg_4x(void)
{
	
	

		while(1)
	{
		
						HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin,GPIO_PIN_RESET);
		// LED ON
		HAL_GPIO_WritePin(SEGA_GPIO_Port, SEGB_Pin|SEGC_Pin,GPIO_PIN_RESET);

		HAL_Delay(10);
		// LED OFF
		HAL_GPIO_WritePin(SEGA_GPIO_Port, SEGB_Pin|SEGC_Pin,GPIO_PIN_SET);

		HAL_Delay(10);
		
		
				HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin,GPIO_PIN_SET);
		// LED ON
		HAL_GPIO_WritePin(SEGA_GPIO_Port, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGG_Pin,GPIO_PIN_RESET);

		HAL_Delay(10);
		// LED OFF
		HAL_GPIO_WritePin(SEGA_GPIO_Port, SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGG_Pin,GPIO_PIN_SET);

		HAL_Delay(10);
		
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
		
			
		HAL_Delay(2000);
	}
}

void test_read_key_int(void)
{
	
	while(1)
	{
		//HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(2000);
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == SW2_Pin)
    {
		 if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin)==0)
		 {
					HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_RESET);
		 }
		 else
		 {
					HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,GPIO_PIN_SET);
		 }
	 }
		
	     if(GPIO_Pin == SW3_Pin)
    {
		 if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin)==0)
		 {
					HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_RESET);
		 }
		 else
		 {
					HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,GPIO_PIN_SET);
		 }
	 }
		
}


void myapp(void)
{
	//test_led_blink();
  //test_led_7seg_1x();
	//test_led_7seg_4x();
	//test_read_key();
	test_read_key_int();
}
