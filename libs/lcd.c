#include "lcd.h"

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
			LCD_WriteText("ON ");
			break;
		case 2:
			LCD_WriteText("OFF");
			break;		
		}

			
		last_air = air_mode;
	}
	
	if(last_heat != (PORTD & (1<<PD3)))
	{
		LCD_GoTo(5,1);
		if(heat_off == 1)
			LCD_WriteText("FOF");
		else if((PORTD & (1<<PD3)))			
			LCD_WriteText("ON ");
		else
			LCD_WriteText("OFF ");
		last_heat = (PORTD & (1<<PD3));
	}
}