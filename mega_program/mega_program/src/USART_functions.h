/*
 * USART_functions.h
 *
 * Created: 2018-03-11 08:18:23
 *  Author: Spellabbet
 */ 


#ifndef USART_FUNCTIONS_H_
#define USART_FUNCTIONS_H_

#define BAUD 9600
#define F_CPU 10000
#define B ((F_CPU / 4 / BAUD - 1) / 2)

void USARTInit();
void USARTSend(unsigned char d);

unsigned char USARTGet();

#endif /* USART_FUNCTIONS_H_ */