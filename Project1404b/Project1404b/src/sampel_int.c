/*
 * sampel_int.c
 *
 * Created: 2013-12-10 12:32:30
 *  Author: Tommy
 */ 

#include <asf.h>
#include "sampel_int.h"

//void TCO_Handler(void);

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;
	uint32_t invalue, outvalue;


	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);			//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	ioport_set_pin_level(CHECK_PIN,HIGH);		//put test pin HIGH 
	
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);  //Wait until DRDY get high

	invalue=adc_get_latest_value(ADC);			//get input value
	
	//************
	// Here should signal processing code be placed
	
	outvalue=invalue;
	
	
	
	//***********
		

		
	dacc_write_conversion_data(DACC,outvalue);	//send output value to DAC
	
	ioport_set_pin_level(CHECK_PIN,LOW);		//put test pin LOW
	
}
