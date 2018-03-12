/*
 * LCD_functions.h
 *
 * Created: 2018-03-12 14:21:10
 *  Author: Spellabbet
 */ 

#include <inttypes.h>

#ifndef LCD_FUNCTIONS_H_
#define LCD_FUNCTIONS_H_

 extern void lcd_write_char(char c);
 extern void lcd_init();
 extern lcd_write_string(char[] c);
 extern lcd_write_byte(uint8_t d);
 extern clear_screen();

#endif /* LCD_FUNCTIONS_H_ */