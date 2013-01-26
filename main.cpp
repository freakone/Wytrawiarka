#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "libs/HD44780.h"


void lcd_init()
{
	LCD_Initalize();
	LCD_Clear();
	LCD_GoTo(2, 0);
	LCD_WriteText("Synergia PWR");
	LCD_GoTo(0, 1);
	LCD_WriteText("Wytrawiarka v0.1");
}

void led_init()
{
	DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);
	
	PORTB |= (1 << PB1);
	_delay_ms(200);
	PORTB |= (1 << PB2);
	_delay_ms(200);
	PORTB |= (1 << PB3);
}

int main(void) 
 {  
	lcd_init();
	led_init();
   while(1)
   {     		
		
   }  
 }