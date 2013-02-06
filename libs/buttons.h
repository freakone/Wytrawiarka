#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "globals.h"
#include <avr/eeprom.h>
#include "lcd.h"

void button_check();
void button_init();