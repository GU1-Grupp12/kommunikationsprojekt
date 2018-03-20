/*
 * USART_functions.c
 *
 * Created: 2018-03-13 09:19:15
 *  Author: Spellabbet
 */ 

#include "USART_functions.h"
#include "DelayFunctions.h"
#include "asf.h"
void USARTInit()
{
	*ptr_UART_CR |= (1u<<6);					//Set TXEN.
	*ptr_UART_BRGR |= (0b1000100011<<0);	//Set baudrate(9600). CD==0b1000100011==546
}

void uart0_transmit(unsigned char data){
	while(!(*ptr_UART_SR & (1u<<1)));
	
	*ptr_UART_THR = data;
}

void uart_putString(char* StringPtr){
	while (*StringPtr != 0x00){
		uart0_transmit(*StringPtr);
		delayMicroseconds(100000);
		StringPtr++;
	}
}
