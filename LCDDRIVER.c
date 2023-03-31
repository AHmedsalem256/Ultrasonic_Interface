

/*

LCD driver based on DIO driver


RS -> 1 for data 0-> command (PORTD pin 0)
RW -> zero PORTD PIN 1

VO for POT
VSS -> GND
VDD -> POWER
D0-D7 -> PORT
E - > PORTD pin 2


*/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"

#include<util/delay.h>


#define FUNCTION_SET    0b00111000
#define ON_OFF          0b00001111 
#define DISPLAY_CLEAR   0b00000001
#define DATAPORT 2
#define CONTROLPORT 3

#define PINRS  2
#define PINRW  3
#define PINE   4

/*

LCD driver based on DIO driver


RS -> 1 for data 0-> command (PORTD pin 0)
RW -> zero PORTD PIN 1

VO for POT
VSS -> GND
VDD -> POWER
D0-D7 -> PORT
E - > PORTD pin 2


*/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"LCDINTERFACE.h"

#include<util/delay.h>


#define FUNCTION_SET    0b00111000
#define ON_OFF          0b00001111
#define DISPLAY_CLEAR   0b00000001
#define DATA_PORT 2
#define CONTROL_PIN 3
#define RW_PIN 3
#define RS_PIN 2
#define E_PIN  4


void LCD_VidIntialize()
{
	/* SETTING ALL RS,RW PIN DIRECTION_HIGH >> INTIALIZE */

	DIO_VidSetPinDirection(CONTROL_PIN,RW_PIN,1);
	DIO_VidSetPinDirection(CONTROL_PIN,RS_PIN,1);
	DIO_VidSetPinDirection(CONTROL_PIN,E_PIN,1);

	
	/* SETTING PORT_DATA HIGH */
	
	DIO_VidSetPortDirection(DATA_PORT,255);
	
	/* SENDING SOME INSTRUCTIONS FROM DATA_SHEET */
	
	_delay_ms(40);

	LCD_VidSendCommand(FUNCTION_SET);
	
	_delay_ms(1);
	
	LCD_VidSendCommand(ON_OFF);

	_delay_ms(1);

	LCD_VidSendCommand(DISPLAY_CLEAR);

	_delay_ms(2);


}

void LCD_VidSendData(u8 value)
{
	/* SETTING UP PINS CHECK FOR IT DATA SHEET___ */
	
	/* RS - >> HIGH >> Writting_DATA */
	
	DIO_VidSetPinValue(CONTROL_PIN,RS_PIN,1);
	
	/* RW - >> LOW >> WRITTING_DATA  */
	DIO_VidSetPinValue(CONTROL_PIN,RW_PIN,0);
	
	/* SENDING DATA VALUE */
	
	DIO_VidSetPortValue(DATA_PORT,value);
	
	/* SETTING UP ENABLE SEQUENCE*/
	
	/* sequence >> open_pin >> __delay__ms(1) >> close_pin */
	
	DIO_VidSetPinValue(CONTROL_PIN,E_PIN,1);
	
	_delay_ms(1);
	
	DIO_VidSetPinValue(CONTROL_PIN,E_PIN,0);
	
	_delay_ms(1);

}

void LCD_VidSendCommand(u8 value)
{
	
	/* SETTTING UP PINS >> DATASHEET */

	/* SETTING RS_PIN >> LOW >> READ */
	
	DIO_VidSetPinValue(DATA_PORT,RS_PIN,0);
	
	/* SENDING THE COMMAND */

	DIO_VidSetPortValue(DATAPORT,value);

	/* SETTING RW_PIN >> HIGH >> COMMAND */
	
	DIO_VidSetPinValue(CONTROL_PIN,RW_PIN,0);
	
	/* ENABLE_SEQUENCE */
	
	DIO_VidSetPinValue(CONTROL_PIN,E_PIN,1);
	
	_delay_ms(1);
	
	DIO_VidSetPinValue(CONTROL_PIN,E_PIN,0);
	
}

void LCD_VidSendString(u8 *ptr)
{
	u8 i;

	for(i=0 ; ptr[i] != '\0' ;i++)
	{
		LCD_VidSendData(ptr[i]);

	}
}

void LCD_VidSendNum(u32 num)
{
	u8 x = 0;
	u32 rev = 0;

	if(num == 0)
	{
		LCD_VidSendData(48);
		return ;

	}

	while(num)
	{
		rev = (rev *10) + (num %10);

		num/=10;
		x++;

	}
	while(x)
	{
		u8 p = rev%10+48;

		LCD_VidSendData(p);

		rev/=10;

		x--;

	}


}
void LCD_VidGOTOPOS(u8 row,u8 col)
{
	if( 0 == row)
	{
		LCD_VidSendCommand(128 + col);
	}

	if(1 == row)
	{
		LCD_VidSendCommand(128 + 64 + col);
	}
}


void LCD_VidDraw()
{
	LCD_VidSendCommand(64);

	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);

	/* got to DDRAM  */
	LCD_VidGOTOPOS(0,0);

	LCD_VidSendData(0);


}
