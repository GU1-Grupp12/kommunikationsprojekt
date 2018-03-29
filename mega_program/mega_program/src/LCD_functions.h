/*
 * LCD_functions.h
 *
 * Created: 2018-03-29 07:19:51
 *  Author: Spellabbet
 */ 


#ifndef LCD_FUNCTIONS_H_
#define LCD_FUNCTIONS_H_

void LCDInit();
void LCDWriteByte(uint8_t d);
void LCDWriteChr(char d);

#endif /* LCD_FUNCTIONS_H_ */