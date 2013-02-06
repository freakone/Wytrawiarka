#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "libs/lcd.h"
#include "libs/led.h"
#include "libs/buttons.h"
#include "libs/globals.h"
#include "libs/sens.h"

unsigned volatile char temperature = 0;
unsigned volatile char destination = 50;
unsigned volatile char air_mode = 0;
unsigned volatile char heat_off = 0;
unsigned volatile int air_counter = 0;
unsigned volatile char blinker_off = 0;

void temp_check()
{
	if(temperature > destination)
	{
		PORTD &= ~(1 << PD3);
		blinker_off = 1;
		OCR1A = 0;
		OCR1B = 0;
		OCR2A = 255;
	}
	else
	if(heat_off == 1)
	{
		PORTD &= ~(1 << PD3);
		blinker_off = 1;
		OCR1A = 0;
		OCR1B = 255;
		OCR2A = 0;
	}
	else if(temperature < (destination - 1))
	{
		blinker_off = 0;
		PORTD |= (1 << PD3);			
	}
}

void air_check()
{
	switch(air_mode)
	{
	case 0:
	
		if(air_counter > 3000)
		{
			air_counter = 0;
			PORTD &= ~(1 << PD4);
		} 
		else if(air_counter > 2000)
		{			
			PORTD |= (1 << PD4);			
		}
		
		break;
	case 1:
		PORTD |= (1 << PD4);
		break;
	case 2:
		PORTD &= ~(1 << PD4);
		break;	
	}

}


int main(void) 
 {  	
	destination = eeprom_read_word(( uint16_t *)1) ;
	air_mode = eeprom_read_word(( uint16_t *)10) ;
		
	if(destination > 90)
	{
		destination = 50;
		air_mode = 0;
	}
	lcd_init();
	led_init();
	adc_init();
	sei();	
	button_init();
	lcd_print_main_screen();
	
	while(1)
	{     		
		lcd_update();
		temp_check();
		air_check();
		button_check();		
	}  
 }