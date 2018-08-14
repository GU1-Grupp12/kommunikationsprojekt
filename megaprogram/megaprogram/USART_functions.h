/*
 * USART_functions.h
 *
 * Created: 2018-03-11 08:18:23
 *  Author: Spellabbet
 */ 

#include <stdint.h>

#ifndef USART_FUNCTIONS_H_
#define USART_FUNCTIONS_H_

#define BAUD 1200
#define F_CPU 16000000
#define B ((F_CPU / 4 / BAUD - 1) / 2)

#include <util/setbaud.h>

void UARTInit(void);

unsigned char UARTGet(void);
uint8_t lastGet;

#endif /* USART_FUNCTIONS_H_ */