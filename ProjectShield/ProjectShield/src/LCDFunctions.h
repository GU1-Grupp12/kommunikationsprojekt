//
//  LCDFunctions.h
//
//  Ulrik Eklund 2015
//
//


#ifndef LCDFunctions_h
#define LCDFunctions_h

#include "asf.h" /* Ugly to include an h-file in another h-file, but necessary */
#define LCD_RS PIO_PC22_IDX
#define LCD_Enable PIO_PC21_IDX

#define LCD_D4 PIO_PC26_IDX
#define LCD_D5 PIO_PC25_IDX
#define LCD_D6 PIO_PC24_IDX
#define LCD_D7 PIO_PC23_IDX

#define PIOC_BASE_ADDRESS 0x400E1200U

#define LCD_mask_D4_D7 (0b1111<<23)

int lcdInit(void);
int lcdWrite(uint8_t byte, bool type);
int lcdClearDisplay(void);

#endif
