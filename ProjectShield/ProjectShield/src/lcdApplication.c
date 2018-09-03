/*
 * lcdApplication.c
 *
 * Created: 2015-09-10 08:44:50
 *  Author: To Be Decided
 */ 

#include "lcdApplication.h"
#include "LCDFunctions.h"
#include "DelayFunctions.h"
#include <stdio.h>
#include <stdlib.h>

int lcdWrite4DigitNumber(int number)
/* Convert int into a string a put in buffer that is iterated through and written*/
{
	char chr[5];
	itoa(number, chr, 10);
	
	int i = 0;
	for(i = 0; i < 4; i++)
	{
		if(chr[i] == '\0') break;
		lcdWrite(chr[i], HIGH);
		delayMicroseconds(5000);
	}

	return 0;	/* Assuming everything went ok */
}

int lcdWriteAsciiString(const char *string)
/* writes an ascii string up to 40 characters on the LCD display */
{
	char *ptr;
	ptr = string;
	int i = 0;
	while(*ptr != '\0')
	{
		lcdWrite((*ptr++), HIGH);
		delayMicroseconds(5000);
	}
	
	return 0;	/* Assuming everything went ok */
}

