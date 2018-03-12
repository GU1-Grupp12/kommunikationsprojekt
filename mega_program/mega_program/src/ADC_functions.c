#include "ADC_functions.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <asf.h>
#include <stdint.h>

void init()
{
	ADMUX |= (1<<REFS0);
	
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADCSRA |= (1<<ADATE);
	ADCSRA |= (1<<ADIE);
	ADCSRA |= (1<<ADEN);
	
	DIDR0 = 3;
	USBCON = 0;
	
	ADCSRA |= (1<<ADSC);
}

uint16_t read()
{
	return 0;
}

ISR(ADC_vect)
{
	unsigned char low,high;
	
	low = ADCL;
	high = ADCH;
	adcValue = (high<<8) + low;
}