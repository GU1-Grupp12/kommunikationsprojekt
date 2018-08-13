#include <asf.h>

#include "DelayFunctions.h"
#include "sysclk.h"
#include "converter_functions.h"
#include "USART_functions.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	ioport_init();
	delayInit();
	USARTInit();
	adcSetup();
	timerSetup();
	
	while(1){
		uart0_transmit('R');
	}
	
}
