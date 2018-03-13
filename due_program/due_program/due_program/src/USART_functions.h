/*
 * USART_functions.h
 *
 * Created: 2018-03-13 09:19:00
 *  Author: Spellabbet
 */ 

#include <inttypes.h>

#ifndef USART_FUNCTIONS_H_
#define USART_FUNCTIONS_H_

void USARTInit();
void USARTsend();

uint8_t USARTGet();

#endif /* USART_FUNCTIONS_H_ */