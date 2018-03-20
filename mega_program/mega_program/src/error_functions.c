/*
 * error_functions.c
 *
 * Created: 2018-03-20 08:11:15
 *  Author: Spellabbet
 */ 

#include "error_functions.h"
#include "USART_functions.h"

uint8_t errorChecking()
{
	buffer[offset] = lastGet;
	if(offset >= 2)
	{
		offset = 0;
		return (buffer[0] != buffer[1]) ? ERROR_FOUND : NO_ERROR;
	}
	
	return NOT_DONE;
}