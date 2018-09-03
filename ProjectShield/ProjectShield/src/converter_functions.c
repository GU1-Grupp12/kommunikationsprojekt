
/*
 * converter_functions.c
 *
 * Created: 2018-03-13 09:14:48
 *  Author: Spellabbet
 */ 
#include "asf.h"
#include "converter_functions.h"
#include "lowpass_2.h"
#include "asf.h"
#include "USART_functions.h"
#include "lcdApplication.h"
#include "LCDFunctions.h"
#include "DelayFunctions.h"

#define M 50
#define N 4

const float b[51] = {
	-0.007576808865785,-0.001893899636357, 0.004936046569725,  0.01316726210615,
	0.01641503216402,  0.01070548634607,-0.001153955416096, -0.01042575932739,
	-0.009063956496661, 0.002770220478856,  0.01523460545822,  0.01606839982939,
	0.001701449537751, -0.01751650355909, -0.02406789681545, -0.00836734115522,
	0.02013720768656,  0.03695646392396,  0.02159184570406, -0.02203882729479,
	-0.06120289788675, -0.05323181046378,  0.02327851896588,   0.1474590233775,
	0.2627669934492,    0.309630834013,   0.2627669934492,   0.1474590233775,
	0.02327851896588, -0.05323181046378, -0.06120289788675, -0.02203882729479,
	0.02159184570406,  0.03695646392396,  0.02013720768656, -0.00836734115522,
	-0.02406789681545, -0.01751650355909, 0.001701449537751,  0.01606839982939,
	0.01523460545822, 0.002770220478856,-0.009063956496661, -0.01042575932739,
	-0.001153955416096,  0.01070548634607,  0.01641503216402,  0.01316726210615,
	0.004936046569725,-0.001893899636357,-0.007576808865785
};

uint16_t dcBiasBuffer[100] = {0};
uint16_t dcBias = 0;
uint16_t dcIndex = 0;
uint32_t invalue, outvalue;
static float xbuff[M+1] = {0};
void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;
	int32_t invalue, outvalue;
	float r = 0;

	ul_dummy = tc_get_status(TC0, 0);			
	UNUSED(ul_dummy);
	
	for (int k = M - 1; k >= 0; k--) {
		xbuff[k + 1] = xbuff[k];
	}
	
	adc_start(ADC);
	while((adc_get_status(ADC) & 0x1<<24)==0);

	invalue = adc_get_latest_value(ADC);
	xbuff[0] = (float)invalue;
	
	for (uint8_t k = 0; k < M + 1; ++k) {
		r = r + xbuff[k] * b[k];
	}
	
	outvalue = (uint32_t)r;
	
	static uint16_t sum;
	uint8_t dcS = 35;
	if(dcIndex < dcS) 
	{
		sum = sum + outvalue;
		dcIndex ++;
	}
	else 
	{
		
		dcBias = (sum/dcS);
// 		lcdClearDisplay();
// 		lcdWrite4DigitNumber(dcBias);
// 		delayMicroseconds(400000);		
		dcIndex = 0;
		sum = 0;
	}
	
	if(samp_index < 100)
	{
		samples[samp_index] = ((outvalue-dcBias)*1000)/1240;

		samp_index++;
	}  
		//lcdClearDisplay();
		//lcdWrite4DigitNumber(samp_index);
		//delayMicroseconds(400000);	
	//***********
}

uint8_t getSampleIndex() 
{
	return samp_index;
}
uint32_t getInvalue()
{
	return invalue;
}

int * getSamples()
{
	return samples;
}
void reset(void) 
{
	samp_index = 0;
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

void timerSetup()
{
	
/*	uint32_t f = ((971226 % 1999) + 991)*16;
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	
	pmc_enable_periph_clk(ID_TC3);

	tc_find_mck_divisor(f, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	tc_init(TC1, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC1, 0, 8400);

	NVIC_EnableIRQ( TC3_IRQn);
	uart0_transmit('s');
	tc_enable_interrupt(TC1, 0, TC_IER_CPCS);
	
	tc_start(TC1, 0);*/
	/* Configure PMC */
	pmc_enable_periph_clk(ID_TC0);

	/** Configure TC for a 10 kHz frequency and trigger on RC compare. */
	tc_init(TC0, 0, 0 | TC_CMR_CPCTRG);			//Timer_clock_1 - MCK/2 - 42 MHz
	tc_write_rc(TC0, 0, 6000);					//6000 corresponds to fs = 7kHz
	
	/* Configure and enable interrupt on RC compare */
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);

	tc_start(TC0, 0);
	
}