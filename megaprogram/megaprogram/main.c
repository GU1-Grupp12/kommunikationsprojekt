/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include "LCD_functions.h"
#include "USART_functions.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	LCDInit();
	
	UARTInit();
	
	char toPrint[3];
	uint8_t delay = 0;
	
	char avgBuffer[64];
	uint8_t avgIndex;
	char avgChar;
	
	while (1)
	{
		LCDWriteCommand(0x80);
		LCDWriteCommand(0x40);
		
		LCDWriteStr("WHAT I GET:");
		
		uint8_t i = 0;
		delay = delay + 1;
		if(delay >= 128/4)
		{
			for(i = 0; i < 3; i++) 
			{
				toPrint[i] = UARTGet();
				if(avgIndex < 64) avgBuffer[avgIndex++] = toPrint[i]; 
			}
			delay = 0;
		}
		
		for(i = 0; i < 3; i++) LCDWriteChr(toPrint[i]);//UARTGet());
		
		LCDWriteStr("AVG:");
		if(avgIndex >= 64-1) 
		{
			uint16_t sum;
			for(i = 0; i < 64; i++)
			{
				sum = sum + avgBuffer[i];
			}
			avgChar = sum/64;
			avgIndex = 0;
		}
		LCDWriteChr(avgChar);
		LCDWriteCommand(0x80);
		LCDWriteCommand(0x40);
		LCDClear();
		LCDWriteStr("                                             ");
	}
}
