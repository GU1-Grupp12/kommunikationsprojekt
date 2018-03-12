#include <stdint.h>

#ifndef ADC_FUNCTIONS_H_
#define ADC_FUNCTIONS_H_

#define USBCON _SFR_MEM8(0xD8)

uint16_t adcValue;

void init();

uint16_t read();

#endif /* ADC_FUNCTIONS_H_ */