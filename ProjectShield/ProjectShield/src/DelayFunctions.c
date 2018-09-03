//
//  DelayFunctions.c
//  Code to be used in task 1401c
//
//	Ulrik Eklund 2014
//
//

#include "asf.h"
#include "DelayFunctions.h"

void delayInit(void)		/* Initializes the timer used for delays */
{
	pmc_enable_periph_clk(ID_TC3);
	tc_init(TC1,0,0);		 /* TC0, channel 0, TCLK1 och capturemode */
	tc_set_block_mode(TC1,0);
	tc_stop(TC1,0);			/* making sure the timer does not run  */
}

void delayMicroseconds(uint32_t us)		/* A simple implementation for a delay in us (not calibrated) */
{
	tc_start(TC1,0);
	while (tc_read_cv(TC1,0) < us*42); /* Only works in newere version of ASF */
	tc_stop(TC1,0);
}