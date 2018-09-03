#include <asf.h>
#include <sam3x8e.h>
#include <fastmath.h>


#include "DelayFunctions.h"
#include "converter_functions.h"
#include "USART_functions.h"

#include "LCDFunctions.h"
#include "lcdApplication.h"

float getVeff(int16_t d[]) 
{
	double s = 0;
	uint16_t i;
	for(i = 0; i < 100; i++) s = s + (d[i]*d[i]);
	s = s / 100;
	s = sqrt(s)/1000;
	
	return s;
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	delayInit();
	ioport_init();
	USARTInit();
	
	lcdInit();
	adcSetup();
	timerSetup();
	while(1){
		// take the filtered signal and calc the effect value and send it trough uart to MEGA.
		
		if(getSampleIndex() >= 100)
		{
			tc_stop(TC0, 0);
			int16_t * stemp;
			stemp = getSamples();
			double veff = 0;
			// typ veff = sqr(1/T Sum s^2dt)
			
			uint8_t i = 0;
			
			/*for(i = 0; i < 100; i++) {
				veff = veff + (stemp[i]*stemp[i]);
// 						lcdClearDisplay();
// 		lcdWrite4DigitNumber(stemp[i]);
// 		delayMicroseconds(400000);
			}
			veff = veff / 100;
			
			veff = sqrt(veff)/1000;
						lcdClearDisplay();
						lcdWrite4DigitNumber(veff);
						delayMicroseconds(400000);
			*/

			veff = getVeff(stemp);

//  			lcdClearDisplay();
//  			lcdWrite4DigitNumber(veff*10);
//  			delayMicroseconds(400000);
			float pw = 1000* ((veff*veff)/10);
			pw = (pw <= 10) ? 11 : pw;
			pw = (pw >= 100) ? 99 : pw;

			char str[3];
			itoa(pw, str, 10);
			uart0_transmit('*');
			uart_putString(str);
			uart0_transmit('!');	
			uart0_transmit('!');   
			lcdClearDisplay();
			lcdWrite4DigitNumber(pw);
			delayMicroseconds(400000);
						
			
			
			//reset();
			tc_start(TC0, 0);
			reset();
		}
	}
}
