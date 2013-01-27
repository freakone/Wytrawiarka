#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "globals.h"

void led_init();
SIGNAL(TIMER0_OVF_vect);