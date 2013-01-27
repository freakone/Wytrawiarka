#include "sens.h"

void adc_init()
{
	DDRC &= ~(1 << PC4);
	DDRC &= ~(1 << PC5);	
	ADCSRA = (1 << ADEN) | (1 << ADIE)  | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADATE);
	ADMUX = (1 << REFS0) | (1 << MUX2);
	ADCSRA |= (1 << ADSC);
	
}

