/*
 * error_functions.h
 *
 * Created: 2018-03-20 08:11:24
 *  Author: Spellabbet
 */ 


#ifndef ERROR_FUNCTIONS_H_
#define ERROR_FUNCTIONS_H_

#include <stdint.h>

#define NOT_DONE 3
#define ERROR_FOUND 2 
#define NO_ERROR 1
#define SIZE 2

uint8_t buffer[SIZE];
uint8_t offset;

uint8_t errorChecking(void);

#endif /* ERROR_FUNCTIONS_H_ */