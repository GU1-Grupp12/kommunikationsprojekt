/*
 * USART_functions.c
 *
 * Created: 2018-03-11 08:14:23
 *  Author: Spellabbet
 */ 

#include "USART_functions.h"

void USARInit() {
	UBRRH = (unsigned char)(BAUD>>8);
	UBRRL = (unsigned char)BAUD;
	
	UCSRC |= (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
	UCSRB |= (1<<RXEN)|(1<<TXEN);
}

void USARTSend(unsigned char d) {
	while(!((UCSRA) & (1<<UDRE))) {}
	UDR = d;
}

unsigned char USARTGet() {
	while(!((UCSRA) & (1<<RXC))) {}
	return UDR;
}