#include "buttons.h"

void button_init()
{
	DDRD |= (1 << PD4) | (1 << PD3);
	PORTD |= (1 << PD5) | (1 << PD6);
	DDRB &= ~(1 << PB6);
	DDRB &= ~(1 << PB7);
	PORTB |= (1 << PB6) | (1 << PB7);
}

int counter = 0;
int counter2 = 0;
void button_check()
{
	if(!(PIND & (1<<PD5)) && destination < 90)
	{
		counter++;
		
		if(counter > 3000)
		{
			destination++;
			counter = 0;
		}
	}
	if(!(PIND & (1<<PD6)) && destination  > 40)
	{
		counter++;
		
		if(counter > 3000)
		{
			destination--;
			counter = 0;
		}
	}
	
	if(!(PINB & (1<<PB6)))
	{
		heat_off = heat_off == 1 ? 0 : 1;
		
		while(!(PINB & (1<<PB6)));
	}
	
	if(!(PINB & (1<<PB7)))
	{
		if(air_mode < 2)
			air_mode++;
		else
			air_mode = 0;
		
		while(!(PINB & (1<<PB7)));
	}

	
}