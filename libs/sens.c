#include "sens.h"

void adc_init()
{
	DDRC &= ~(1 << PC4);
	DDRC &= ~(1 << PC5);	
	ADCSRA = (1 << ADEN) | (1 << ADIE)  | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	ADMUX = (1 << REFS0) | (1 << MUX2);
	ADCSRA |= (1 << ADSC);	
}

unsigned volatile char count = 0;
unsigned volatile int srednia = 0;
SIGNAL (SIG_ADC)
{
	int temp = (ADCL | (ADCH << 8)) * 50;
	temp /= 102;	
	
	srednia += temp;
	count++;
	if(count == 100)
	{
		temperature=(srednia / 100);
		count = 0;
		srednia = 0;
	}
	
	ADCSRA |= (1 << ADSC);	
}
