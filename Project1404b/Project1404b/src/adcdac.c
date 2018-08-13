/*
 * adcdac.c
 *
 * Created: 2013-12-10 08:30:13
 *  Author: Tommy
 */ 

#include <asf.h>
#include "adcdac.h"


void adc_setup()
{
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 20000000, 0);		//Configure for maximum frequency @ 84 MHz, CHECK THIS!!
	adc_configure_timing(ADC, 0, 0, 0);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_channel(ADC, ADC_CHANNEL_10);				//PB17 - AD8 for Arduino
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);			//trigg just by software
}




void dac_setup() {
	pmc_enable_periph_clk(ID_DACC);
	dacc_reset(DACC);
	dacc_set_transfer_mode(DACC, 0);
	dacc_set_timing(DACC,1,1,0);			//1 is shortest refresh period, 1 max. speed, 0 startup time
	
	dacc_set_channel_selection(DACC,0);		//Channel DAC0
	dacc_enable_channel(DACC, 0);			//enable DAC0
}

