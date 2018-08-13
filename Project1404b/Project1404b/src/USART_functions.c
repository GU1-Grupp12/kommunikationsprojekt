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
	//*ptr_UART_CR |= (1u<<6);					//Set TXEN.
	//*ptr_UART_BRGR |= (0b1000100011<<0);	//Set baudrate(9600). CD==0b1000100011==546
	
	pmc_enable_periph_clk(ID_USART0);
	USART0->US_CR |= (1 << 6);
	USART0->US_MR |= (1 << 7) | (1 << 6);
	USART0->US_MR &= ~((1 << 4) | (1 << 5));
	PIOA->PIO_PDR |= (PIO_PA10) | (PIO_PA11);
	USART0->US_BRGR = 4000;
}

void uart0_transmit(unsigned char data){
	while(!(USART0->US_CSR & (1u<<1)));
	
	USART0->US_THR = data;
}

void uart_putString(char* StringPtr){
	while (*StringPtr != 0x00){
		uart0_transmit(*StringPtr);
		delayMicroseconds(100000);
		StringPtr++;
	}
}
