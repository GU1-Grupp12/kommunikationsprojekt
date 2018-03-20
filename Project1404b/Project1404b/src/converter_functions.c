/*
 * converter_functions.c
 *
 * Created: 2018-03-13 09:14:48
 *  Author: Spellabbet
 */ 
#include <asf.h>
#include "converter_functions.h"

#define M 11
#define N 4

void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;
	uint32_t invalue, outvalue;


	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);			//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
		//put test pin HIGH 
	
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);  //Wait until DRDY get high

	invalue=adc_get_latest_value(ADC);			//get input value
	
	//************
	// Here should signal processing code be placed
	
	static float xbuff[M+1];  
	static float b[M+1] = {0.03317656454166, -0.05161718187399,  0.03317656454166};
//{0.01488697472657, -0.02695899404537,  0.03705935223574, -0.02695899404537, 0.01488697472657};

  
	static int hasSet = 0;  
	int i = 0;  
	if(hasSet == 0)  {    
		for(i = 0; i < M+1; i++)   
		{    
			xbuff[i] = 0;    
			//b[0] = 0.1f;   
		}   
		hasSet = 1;  
	}    
	int k = 0;  
	for(k = M-1; k > -1; k--)  
	{   
		xbuff[k+1] = xbuff[k];  
	}
	
	static float y[N+1];
	static float a[N+1] = {-1,   1.857007392162,    -0.873541396873};
	static int hasSet1 = 0;
	if(hasSet1 == 0)
	{
		for(i = 0; i < N+1; i++)
		{
			y[i] = 0;
		}
		hasSet1 = 1;
	}
	
	xbuff[0] = (float)invalue;    
	static float r = 0;  
	r = 0;  
	for(i = 0; i < M+1; i++)   
	{  
		 r = r + (b[i] * xbuff[i]);  
	}  
	
	static float r1 = 0;
	r1 = 0;
	for(i = 1; i < N+1; i++)
	{
		r1 = r1 + (a[i] * y[i]);
	}
	//r1 = r1 + r;
	for(k = N-1; k > -1; k--)
	{
		y[k+1] = y[k];
	}
	y[1] = (r + r1);
	outvalue= y[1];
	
	//***********
		
	dacc_write_conversion_data(DACC,outvalue);	//send output value to DAC
	
}

void adcSetup()
{
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 20000000, 0);		
	adc_configure_timing(ADC, 0, 0, 0);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_channel(ADC, ADC_CHANNEL_10);				
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);			
}

void dacSetup()
{
	pmc_enable_periph_clk(ID_DACC);
	dacc_reset(DACC);
	dacc_set_transfer_mode(DACC, 0);
	dacc_set_timing(DACC,1,1,0);			
	
	dacc_set_channel_selection(DACC,1);		
	dacc_enable_channel(DACC, 1);			
}

void timerSetup()
{
	pmc_enable_periph_clk(ID_TC0);

	/** Configure TC for a 10 kHz frequency and trigger on RC compare. */
	tc_init(TC0, 0, 0 | TC_CMR_CPCTRG);			//Timer_clock_1 - MCK/2 - 42 MHz
	tc_write_rc(TC0, 0, 4200);					//4200 corresponds to fs = 10 kHz

	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);

	tc_start(TC0, 0);
}