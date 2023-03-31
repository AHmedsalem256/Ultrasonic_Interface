
#ifndef ICU_INTERFACE_H
#define ICU_INTERFACE__H

#include"BIT_MATH.h"
#include"STD_TYPES.h"

typedef enum
{
	FALLING,RISING
}edge_type;


typedef enum{
	F_CPU_NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_Clock;

typedef struct{
	edge_type A_EDGE;

	ICU_Clock clock;

}Icu_config;



void Icu_init(const Icu_config *Config );

void IcuSETT_CALL_BACK( void (*Icu_Ptr)(void));

void Icu_Set_edge(const edge_type e_edge);

u16 Icu_Get_value();

void Icu_clearTimer();



void Icu_Deinit();



















#endif
