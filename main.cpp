#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "libs/HD44780.h"
#include <stdlib.h>

unsigned volatile char temperature = 0;
unsigned volatile char destination = 50;
unsigned volatile char air_mode = 0;
unsigned volatile char heat_off = 0;

void lcd_init()
{
	LCD_Initalize();
	LCD_Clear();
	LCD_GoTo(2, 0);
	LCD_WriteText("Synergia PWR");
	LCD_GoTo(0, 1);
	LCD_WriteText("Wytrawiarka v0.1");
}

void lcd_print_main_screen()
{
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteText("A:xx*C D:xx*C");
	LCD_GoTo(4,0);
	LCD_WriteData(0xDF);
	LCD_GoTo(11,0);
	LCD_WriteData(0xDF);
	LCD_GoTo(0,1);
	LCD_WriteText("HEAT:OFF AIR:OFF");
}

void led_init()
{
	DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);
	
	PORTB |= (1 << PB1);
	_delay_ms(200);
	PORTB |= (1 << PB2);
	_delay_ms(200);
	PORTB |= (1 << PB3);
	
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

void adc_init()
{
	DDRC &= ~(1 << PC4);
	DDRC &= ~(1 << PC5);	
	ADCSRA = (1 << ADEN) | (1 << ADIE)  | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADATE);
	ADMUX = (1 << REFS0) | (1 << MUX2);
	ADCSRA |= (1 << ADSC);
	
}

SIGNAL (SIG_ADC)
{
	int temp = (ADCL | (ADCH << 8))*500;
	temp /= 1024;
	temperature = temp;
}

unsigned volatile char last_temp = 0;
unsigned volatile char last_dest = 0;
unsigned volatile char last_heat = 5;
unsigned volatile char last_air = 5;

void lcd_update()
{
	char str[10];
	if(last_temp != temperature)	
	{
		itoa(temperature, str, 10);
		LCD_GoTo(2,0);
		LCD_WriteText(str);
		last_temp = temperature;
	}
	
	if(last_dest != destination)
	{
		itoa(destination, str, 10);
		LCD_GoTo(9,0);
		LCD_WriteText(str);	
		last_dest = destination;
	}
	
	if(last_air != air_mode)
	{
		LCD_GoTo(13,1);
		switch(air_mode)
		{
		case 0:
			LCD_WriteText("AUT");
			break;
		case 1:
			LCD_WriteText("ON");
			break;
		case 2:
			LCD_WriteText("OFF ");
			break;		
		}

			
		last_air = air_mode;
	}
	
	if(last_heat != (PORTD & (1<<PD3)))
	{
		LCD_GoTo(5,1);
		if((PORTD & (1<<PD3)))			
			LCD_WriteText("ON ");
		else
			LCD_WriteText("OFF ");
		last_heat = (PORTD & (1<<PD3));
	}
}

void rest_init()
{
	DDRD = 0;
	DDRD |= (1 << PD4) | (1 << PD3);
	PORTD |= (1 << PD5) | (1 << PD6);
	DDRB &= ~(1 << PB6);
	DDRB &= ~(1 << PB7);
	PORTB |= (1 << PB6) | (1 << PB7);
}

void temp_check()
{
	if(temperature > destination || heat_off == 1)
	{
		PORTD &= ~(1 << PD3);
		TIMSK0 = 0;
		OCR1A = 0;
		OCR1B = 0;
		OCR2A = 255;
	}
	else if(temperature < (destination - 3))
	{
		TIMSK0 = (1 << TOIE0);
		PORTD |= (1 << PD3);			
	}
}

void button_check()
{
	int counter = 0;

		while((PIND & (1<<PD5)))
		{
			if(destination >= 90)
				break;
				
			counter++;
			if(counter > 5000)
			{
				destination++;
				counter = 0;
			}
		}
		
		counter = 0;
	
		while((PIND & (1<<PD6)))
		{
			if(destination <= 40)
				break;
				
			counter++;
			if(counter > 5000)
			{
				destination--;
				counter = 0;
			}
			
			
		}
		
		counter = 0;
}
int main(void) 
 {  
	lcd_init();
	led_init();
	sei();
	adc_init();
	lcd_print_main_screen();
	
	while(1)
	{     		
		lcd_update();
		temp_check();
		button_check();		
	}  
 }