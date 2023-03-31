#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"ICU_interface.h"
#include<avr/io.h>

/*

ICU Driver based on atmega32 avr

Author : AHmed salem 

DATE 1/3/2023


*/

/* ADDRESS TO CALL CALL_BACK */

void (* ICU_SET_CALLBACK)(void) = 0;


void __vector_6(void)  __attribute__((signal));

void __vector_6 (void)
{
	ICU_SET_CALLBACK();

}


void Icu_init(const Icu_config *Config )
{

	/* setting ICP1 pin as input */

	DIO_VidSetPinDirection(3,6,0);


	/* TCCR1A >> normal */

	TCCR1A |= 1 << 3 | 1 << 2;

	ICR1 = 0;

		TCNT1 = 0;

	/* TCCR1B */

	//TCCR1B=(TCCR1B & 0)|((Config->A_EDGE)<<ICES1)|(Config->clock);

		TCCR1B = 1 << 6 | 1 << 1 ;


	TIMSK |= 1 << 5;

}


void IcuSETT_CALL_BACK( void (*Icu_Ptr)(void))
{
	ICU_SET_CALLBACK = Icu_Ptr;
}


void Icu_Set_edge(const edge_type e_edge)
{
	TCCR1B = (TCCR1B&0xBF) |(e_edge<<ICES1);
}


u16 Icu_Get_value()
{
	return ICR1;
}


void Icu_clearTimer()
{
	TCNT1 = 0;
}


void Icu_Deinit()
{
 	    ICR1=0;
		TCNT1=0;
		TCCR1A=0;
		TCCR1B=0;
		TIMSK &= ~(1<<TICIE1);
}

