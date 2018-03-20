/*
 * USART_functions.h
 *
 * Created: 2018-03-13 09:19:00
 *  Author: Spellabbet
 */ 

#include <inttypes.h>

#ifndef USART_FUNCTIONS_H_
#define USART_FUNCTIONS_H_
#define UART_BASE_ADDRESS
uint32_t *const ptr_UART_CR = (uint32_t *) (UART_BASE_ADDRESS + 0x0000U);
uint32_t *const ptr_UART_MR = (uint32_t *) (UART_BASE_ADDRESS + 0x0004U);
uint32_t *const ptr_UART_SR = (uint32_t *) (UART_BASE_ADDRESS + 0x0014U);
uint32_t *const ptr_UART_THR = (uint32_t *) (UART_BASE_ADDRESS + 0x001CU);	
uint32_t *const ptr_UART_BRGR = (uint32_t *) (UART_BASE_ADDRESS + 0x0020U);
void USARTInit();
void uart0_transmit(unsigned char data);
void uart_putString(char* StringPtr);

#endif /* USART_FUNCTIONS_H_ */