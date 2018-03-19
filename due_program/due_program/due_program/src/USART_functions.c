/*
 * USART_functions.c
 *
 * Created: 2018-03-13 09:19:15
 *  Author: Spellabbet
 */ 

#include "USART_functions.h"

void USARTInit()
{
	*ptr_UART_CR |= (1u<<4);					//Set RXEN.
	*ptr_UART_BRGR |= (0b1000100011<<0);	//Set baudrate(9600). CD==0b1000100011==546
}

uint8_t USARTGet()
{
	while(!(*ptr_UART_SR & (1u<<0))) { } // se om det tagits emot något nytt, vänta annars.
	
	return 0;
}
