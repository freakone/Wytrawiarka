#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HD44780.h"
#include <stdlib.h>
#include "globals.h"

void lcd_init();
void lcd_print_main_screen();
void lcd_update();