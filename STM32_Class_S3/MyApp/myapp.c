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

void test_led_7seg(void)
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


void myapp(void)
{
	//test_led_blink();
  test_led_7seg();
}
