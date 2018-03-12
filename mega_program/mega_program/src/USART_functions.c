/*
 * USART_functions.c
 *
 * Created: 2018-03-11 08:14:23
 *  Author: Spellabbet
 */ 

#include "USART_functions.h"

#include <avr/io.h>
#include <asf.h>

void USARTInit() {
	UBRR0H = (unsigned char)(B>>8);
	UBRR0L = (unsigned char)B;
	
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}

void USARTSend(unsigned char d) {
	while(!((UCSR0A) & (1<<UDRE0))) {}
	UDR0 = d;
}

unsigned char USARTGet() {
	while(!((UCSR0A) & (1<<RXC0))) {}
	return UDR0;
}