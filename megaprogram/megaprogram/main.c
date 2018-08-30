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
	
	char avgBuffer[16];
	uint8_t avgIndex;
	char avgChar;
	
	uint8_t error;
	
	while (1)
	{
		uint8_t i = 0;
		error = 0;
		if(UARTGet() == '*')
			for(i = 0; i < 4; i++)
			{
				if(i == 0 || i == 1) 
				{
					toPrint[i] = UARTGet();
					if(avgIndex < 16) avgBuffer[avgIndex++] = toPrint[i];
					if(toPrint[i] < 48 || toPrint[i] > 57) toPrint[i] = ' ';
				} 
				else
				{
					if(UARTGet() != '!')
					{
						error = 1;
						break;
					}
				}
			}
		
		
		delay = delay + 1;
		if(delay >= 2)
		{
			LCDWriteStr("                                           ");
			LCDWriteCommand(0x80);
			LCDWriteCommand(0x40);
			
			LCDWriteStr("P:");
			
			for(i = 0; i < 2; i++) LCDWriteChr(toPrint[i]);//UARTGet());
			if(error == 1) LCDWriteStr(" : ERROR");
			/*LCDWriteStr("AVG:");
			if(avgIndex >= 16-1) 
			{
				uint16_t sum;
				for(i = 0; i < 16; i++)
				{
					sum = sum + avgBuffer[i];
				}
				avgChar = sum/16;
				avgIndex = 0;
			}
			LCDWriteChr(avgChar);*/
							
			delay = 0;
		}
	}
}
