#include "myapp.h"
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "LCD16X2.h"
 
#define MyLCD LCD16X2_1



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

int8_t scan_keypad(void)
{
	int8_t key=-1;
	
	HAL_GPIO_WritePin(KP_R0_GPIO_Port,KP_R0_Pin|KP_R1_Pin|KP_R2_Pin|KP_R3_Pin,1);
	HAL_GPIO_WritePin(KP_R0_GPIO_Port,KP_R0_Pin,0);
	if     (HAL_GPIO_ReadPin(KP_C0_GPIO_Port,KP_C0_Pin) == 0)key=7;
	else if(HAL_GPIO_ReadPin(KP_C1_GPIO_Port,KP_C1_Pin) == 0)key=8;
	else if(HAL_GPIO_ReadPin(KP_C2_GPIO_Port,KP_C2_Pin) == 0)key=9;
	else if(HAL_GPIO_ReadPin(KP_C3_GPIO_Port,KP_C3_Pin) == 0)key=10;
	
	HAL_GPIO_WritePin(KP_R0_GPIO_Port,KP_R0_Pin|KP_R1_Pin|KP_R2_Pin|KP_R3_Pin,1);
	HAL_GPIO_WritePin(KP_R1_GPIO_Port,KP_R1_Pin,0);
	if     (HAL_GPIO_ReadPin(KP_C0_GPIO_Port,KP_C0_Pin) == 0)key=4;
	else if(HAL_GPIO_ReadPin(KP_C1_GPIO_Port,KP_C1_Pin) == 0)key=5;
	else if(HAL_GPIO_ReadPin(KP_C2_GPIO_Port,KP_C2_Pin) == 0)key=6;
	else if(HAL_GPIO_ReadPin(KP_C3_GPIO_Port,KP_C3_Pin) == 0)key=11;
	
	
	HAL_GPIO_WritePin(KP_R0_GPIO_Port,KP_R0_Pin|KP_R1_Pin|KP_R2_Pin|KP_R3_Pin,1);
	HAL_GPIO_WritePin(KP_R2_GPIO_Port,KP_R2_Pin,0);
	if     (HAL_GPIO_ReadPin(KP_C0_GPIO_Port,KP_C0_Pin) == 0)key=1;
	else if(HAL_GPIO_ReadPin(KP_C1_GPIO_Port,KP_C1_Pin) == 0)key=2;
	else if(HAL_GPIO_ReadPin(KP_C2_GPIO_Port,KP_C2_Pin) == 0)key=3;
	else if(HAL_GPIO_ReadPin(KP_C3_GPIO_Port,KP_C3_Pin) == 0)key=12;
	
	HAL_GPIO_WritePin(KP_R0_GPIO_Port,KP_R0_Pin|KP_R1_Pin|KP_R2_Pin|KP_R3_Pin,1);
	HAL_GPIO_WritePin(KP_R3_GPIO_Port,KP_R3_Pin,0);
	if     (HAL_GPIO_ReadPin(KP_C0_GPIO_Port,KP_C0_Pin) == 0)key=13;
	else if(HAL_GPIO_ReadPin(KP_C1_GPIO_Port,KP_C1_Pin) == 0)key=0;
	else if(HAL_GPIO_ReadPin(KP_C2_GPIO_Port,KP_C2_Pin) == 0)key=14;
	else if(HAL_GPIO_ReadPin(KP_C3_GPIO_Port,KP_C3_Pin) == 0)key=15;
	
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

void test_lcd_char(void)
{
	
	  LCD16X2_Init(MyLCD);
    LCD16X2_Clear(MyLCD);
    LCD16X2_Set_Cursor(MyLCD, 1, 1);
    LCD16X2_Write_String(MyLCD, "  Meco");
    LCD16X2_Set_Cursor(MyLCD, 2, 1);
    LCD16X2_Write_String(MyLCD, "STM32 Course");
	
	while(1)
	{		

		    LCD16X2_SR(MyLCD);  HAL_Delay(450);
        LCD16X2_SR(MyLCD);  HAL_Delay(450);
        LCD16X2_SR(MyLCD);  HAL_Delay(450);
        LCD16X2_SR(MyLCD);  HAL_Delay(450);
 
        LCD16X2_SL(MyLCD);  HAL_Delay(450);
        LCD16X2_SL(MyLCD);  HAL_Delay(450);
        LCD16X2_SL(MyLCD);  HAL_Delay(450);
        LCD16X2_SL(MyLCD);  HAL_Delay(450);
	}
}


void test_uart_send(void)
{
	
	while(1)
	{		
		HAL_UART_Transmit(&huart2,(uint8_t*)"Hello\r\n",7,1000);
		//HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		HAL_Delay(1000);
	}
}


void myapp(void)
{
	//test_keypad();
	//test_count_7seg();
	//test_lcd_char();
	
	test_uart_send();
}
