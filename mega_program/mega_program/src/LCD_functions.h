/*
 * LCD_functions.h
 *
 * Created: 2018-03-29 07:19:51
 *  Author: Spellabbet
 */ 


#ifndef LCD_FUNCTIONS_H_
#define LCD_FUNCTIONS_H_

#define CHR_WIDTH 1
#define OFFSET 0

void LCDInit(void);
void LCDWriteByte(uint8_t d);
void LCDWriteChr(uint8_t d);
void LCDWriteCommand(uint8_t d);
void LCDWriteStr(char * t);
void LCDClear(void);

#endif /* LCD_FUNCTIONS_H_ */