#include "myapp.h"
#include "main.h"
#include "gpio.h"





void show_seg(uint8_t num)
{
	HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGB_Pin|SEGC_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin,0);
	
	if(num == 0)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGB_Pin|SEGC_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin,1);
	}
	else 	if(num == 1)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGB_Pin|SEGC_Pin,1);
	}
	else 	if(num == 2)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGB_Pin|SEGD_Pin|SEGE_Pin|SEGG_Pin,1);
	}
	else 	if(num == 3)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGB_Pin|SEGC_Pin|SEGD_Pin|SEGG_Pin,1);
	}
	else 	if(num == 4)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGB_Pin|SEGC_Pin|SEGF_Pin|SEGG_Pin,1);
	}
	else 	if(num == 5)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGC_Pin|SEGD_Pin|SEGF_Pin|SEGG_Pin,1);
	}
	else 	if(num == 6)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGC_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin,1);
	}
	else 	if(num == 7)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGB_Pin|SEGC_Pin,1);
	}
	else 	if(num == 8)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGB_Pin|SEGC_Pin|SEGD_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin,1);
	}
	else 	if(num == 9)
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGB_Pin|SEGC_Pin|SEGD_Pin|SEGF_Pin|SEGG_Pin,1);
	}
	else
	{
			HAL_GPIO_WritePin(SEGA_GPIO_Port,SEGA_Pin|SEGE_Pin|SEGF_Pin|SEGG_Pin,1);
	}
	
	
}

int8_t scan_keypad()
{
	int8_t key=-1;
	
	return key;
}

void test_keypad(void)
{
	int8_t key=-1;
	show_seg(0xf);
	
	while(1)
	{		
		key=scan_keypad();
		
		if(key>=0)
		{
			show_seg(key);
		}
	}
}

void test_count_7seg(void)
{
	int8_t num=0;
	
	
	while(1)
	{		
		show_seg(num++);
		if(num>10)num=0;
		HAL_Delay(500);
	}
}


void myapp(void)
{
	//test_keypad();
	test_count_7seg();
}
