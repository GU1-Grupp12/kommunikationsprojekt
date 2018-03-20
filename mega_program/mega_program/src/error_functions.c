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
	if(offset >= SIZE)
	{
		offset = 0;
		uint8_t i;
		uint8_t j;
		for(i = 0; i < SIZE; i++)
		{
			for(j = 0; j < SIZE; j++)
			{
				if(buffer[i] != buffer[j])
					return ERROR_FOUND;
			}	
		}
		
		return NO_ERROR;
		
		return (buffer[0] != buffer[1]) ? ERROR_FOUND : NO_ERROR;
	}
	
	return NOT_DONE;
}