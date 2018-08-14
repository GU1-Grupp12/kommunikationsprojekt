/*
 * LCD.h
 *
 * Created: 2018-08-14 14:12:58
 *  Author: Spellabbet
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>

void LCDInit(void);
void LCDWriteCommand(uint8_t);
void LCDWriteChr(uint8_t);
void LCDWriteStr(char *);
void LCDClear(void);

#endif /* LCD_H_ */