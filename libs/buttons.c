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
void button_check()
{
	if(!(PIND & (1<<PD6)) && !(PIND & (1<<PD5)))
	{
		counter++;
		
		if(counter > 20000)
		{
			eeprom_write_word((uint16_t*)1, (uint16_t)destination);
			eeprom_write_word((uint16_t*)10, (uint16_t)air_mode); 	
			lcd_print_save_screen();
			_delay_ms(2000);
			lcd_print_main_screen();
			lcd_last_reset();
			counter = 0;
		}
	}
	else
	if(!(PIND & (1<<PD6)) && destination < 90)
	{
		counter++;
		
		if(counter > 4000)
		{
			destination++;
			counter = 0;
		}
	}
	else
	if(!(PIND & (1<<PD5)) && destination  > 40)
	{
		counter++;
		
		if(counter > 4000)
		{
			destination--;
			counter = 0;
		}
	}
	
	if(!(PINB & (1<<PB6)))
	{
		heat_off = heat_off == 1 ? 0 : 1;
		_delay_ms(30);		
		while(!(PINB & (1<<PB6)));
	}
	
	if(!(PINB & (1<<PB7)))
	{
		if(air_mode < 2)
			air_mode++;
		else
			air_mode = 0;
		
		_delay_ms(30);	
		while(!(PINB & (1<<PB7)));
	}

	
}