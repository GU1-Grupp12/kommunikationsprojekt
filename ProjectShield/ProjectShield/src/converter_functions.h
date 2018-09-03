/*
 * converter_functions.h
 *
 * Created: 2018-03-13 09:15:07
 *  Author: Spellabbet
 */ 

#include <inttypes.h>
#include <asf.h>
#include <stdio.h>
#ifndef CONVERTER_FUNCTIONS_H_
#define CONVERTER_FUNCTIONS_H_

uint8_t samp_index;
int16_t samples[100];

void adcSetup();
void dacSetup();

void timerSetup();
void TC1_Handler(void);

void reset(void);
uint8_t getSampleIndex(void);
int * getSamples(void);
uint32_t getInvalue(void);

#endif /* CONVERTER_FUNCTIONS_H_ */