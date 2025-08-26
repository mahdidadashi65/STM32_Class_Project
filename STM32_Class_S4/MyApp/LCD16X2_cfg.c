/*
 * File: LCD16X2_cfg.c
 * Driver Name: [[ LCD16x2 Display (GPIO 4-Bit Mode) ]]
 * SW Layer:   ECUAL
 * Created on: Jun 28, 2020
 * Author:     Khaled Magdy
 * -------------------------------------------
 * For More Information, Tutorials, etc.
 * Visit Website: www.DeepBlueMbedded.com
 *
 */

#include "LCD16X2_cfg.h"
#include "LCD16X2.h"

const LCD16X2_CfgType LCD16X2_CfgParam[LCD16X2_MAX] =
{
	{   /*  Configuration Parameter For LCD Instance #1   */
		LCD16X2_1,			/* Index of LCD Instance #1   */
		LCD_D4_GPIO_Port,	LCD_D4_Pin, /* LCD D4 Pin GPIO Port & Pin */
		LCD_D5_GPIO_Port,	LCD_D5_Pin, /* LCD D5 Pin GPIO Port & Pin */
		LCD_D6_GPIO_Port,	LCD_D6_Pin, /* LCD D6 Pin GPIO Port & Pin */
		LCD_D7_GPIO_Port,	LCD_D7_Pin, /* LCD D7 Pin GPIO Port & Pin */
		LCD_E_GPIO_Port,	LCD_E_Pin, /* LCD EN Pin GPIO Port & Pin */
		LCD_RS_GPIO_Port,	LCD_RS_Pin  /* LCD RS Pin GPIO Port & Pin */
	}
};
