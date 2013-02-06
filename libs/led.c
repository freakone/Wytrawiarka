#include "led.h"

void led_init()
{
	DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);
	
	PORTB |= (1 << PB1);
	_delay_ms(600);
	PORTB |= (1 << PB2);
	_delay_ms(600);
	PORTB |= (1 << PB3);
	_delay_ms(600);
	
	TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B = (1<< CS11) | (1 << CS10);
	TCCR2A = (1 << COM2A1) | (1 << WGM20);
	TCCR2B = (1 << CS22);
	
	TCCR0B = (1 << CS02);
	TIMSK0 = (1 << TOIE0);
}




unsigned volatile char step = 0;
SIGNAL(TIMER0_OVF_vect)
{
	if(blinker_off != 1)
	{
		switch(step)
		{
		case 0:
			if(OCR1A < 255)
				OCR1A++;
			else if(OCR1B < 255)
				OCR1B++;
			else if(OCR2A < 255)
				OCR2A++;
			else
				step ++;
		break;
		
		case 1:
			if(OCR1A > 0)
				OCR1A--;
			else if(OCR1B > 0)
				OCR1B--;
			else if(OCR2A > 0)
				OCR2A--;
			else
				step = 0;
		}
	}
	
	air_counter++;
}
