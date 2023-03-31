


/*

AUTHOR : Ahmed Salem Mohammed 

Date 3/3/2023 

@brief : ULTRASONIC driver Based on Timer1 AVR

*/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"ICU_interface.h"
#include"TIMERinterface.h"
#include<avr/delay.h>

u16 g_Period = 0;
extern u8 g_counter;

static void UTRASONIC_edgeprocessing(void);
void ULTRASONIC_trigger();
u16 ULTRASONIC_ReadDisance();

void ULTRASONIC_Init()
{
	Icu_config ICU_conf;

	ICU_conf.A_EDGE = RISING  ;
	ICU_conf.clock  = F_CPU_8  ;

	Icu_init(&ICU_conf);

	/* Setting up CALL_BACK_FUNC */

	IcuSETT_CALL_BACK(UTRASONIC_edgeprocessing);

	/*setup the Pin Trigger as Ouput DIRECTION pin*/

	DIO_VidSetPinDirection(3,7,1);



}



void ULTRASONIC_trigger()
{
	/* Setting PIN 7 PORT D AS trigger pin  */

	DIO_VidSetPinValue(3,7,1);
	_delay_us(15);
	DIO_VidSetPinValue(3,7,0);

}

u16 ULTRASONIC_ReadDisance()
{
	u16 Distance;

	ULTRASONIC_trigger();

	Distance = g_Period / 58.5;

	return Distance;

}





static void UTRASONIC_edgeprocessing(void)
{
	++g_counter;

	if(g_counter == 1)
	{
		/* Set falling edge */

		Icu_Set_edge(FALLING);

		/* clear to count from there */

		Icu_clearTimer();

	}
	else if(g_counter == 2){

		/* saving time */
		g_Period = Icu_Get_value();
		/* setting rising edge */
		Icu_Set_edge(RISING);
		/* clear timer */

		Icu_clearTimer();

	}
	else
	{
		g_counter = 0;
	}

}



