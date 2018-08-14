#include "USART_functions.h"

#include <avr/io.h>

void UARTInit() {
	/*UBRR0H = (unsigned char)(B>>8);
	UBRR0L = (unsigned char)B;
	
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);*/	
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	#if USE_2X
	UCSR0A |= _BV(U2X0);
	#else
	UCSR0A &= ~(_BV(U2X0));
	#endif

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

unsigned char UARTGet() {
	while(!((UCSR0A) & (1<<RXC0))) {}
	lastGet = UDR0;
	//offset = offset + 1;
	return lastGet;
}