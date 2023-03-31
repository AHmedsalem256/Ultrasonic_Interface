/*
 * main.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Ahmed
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCDINTERFACE.h"
#include"TIMERinterface.h"
#include"ICU_interface.h"
#include<avr/io.h>
#include<avr/delay.h>

u8 g_counter  = 0 ;

void main()
{
	u16 REQ_DIST = 0; // initialize required distance

	DIO_VidSetPinDirection(1,3,1);

	LCD_VidIntialize(); // lcd init func

	SREG |= 1 << 7;  // enable GIE

	LCD_VidGOTOPOS(0,0);

	ULTRASONIC_Init();  //active ultrasonic

	REQ_DIST = ULTRASONIC_ReadDisance(); // to get distance


	while(1)
	{

		if(g_counter == 2) /* mesure time bet rise and fall */
		{
			g_counter = 0;

			LCD_VidGOTOPOS(0,0);

			LCD_VidSendNum(REQ_DIST);

			REQ_DIST = ULTRASONIC_ReadDisance();

			if(REQ_DIST < 10)
			{
				LCD_VidGOTOPOS(0,0);
			}

			if(REQ_DIST < 100)
			{
				LCD_VidGOTOPOS(0,0);
			}

			if(REQ_DIST == 50)
			{
				DIO_VidSetPinValue(1,3,1);
			}

			else if(REQ_DIST != 50)
			{
				DIO_VidSetPinValue(1,3,0);
			}

		}

		_delay_ms(500);
		LCD_VidSendCommand(0x01);
		_delay_ms(500);
		LCD_VidGOTOPOS(0,0);

	}
}

