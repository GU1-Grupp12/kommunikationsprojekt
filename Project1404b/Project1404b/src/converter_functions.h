/*
 * converter_functions.h
 *
 * Created: 2018-03-13 09:15:07
 *  Author: Spellabbet
 */ 

#include <inttypes.h>
#include <asf.h>
#ifndef CONVERTER_FUNCTIONS_H_
#define CONVERTER_FUNCTIONS_H_

void adcSetup();
void dacSetup();

void timerSetup();
void TC0_Handler();

#endif /* CONVERTER_FUNCTIONS_H_ */