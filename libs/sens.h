#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "globals.h"

void adc_init();
SIGNAL (SIG_ADC);