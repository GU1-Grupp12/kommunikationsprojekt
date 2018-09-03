//
//  LCDFunctions.c
//  Code to be used in task 1401c
//
//	Ulrik Eklund 2014
//
//

#include <inttypes.h>
#include <asf.h>
#include "lcdFunctions.h"
#include "delayFunctions.h"	/* The sam3x8e microcontroller can write faster than the LCD controller can handle its inputs */

int lcdInit(void)		/* Initializes the display on the LCD shield, returns 1 if everything is ok */
{
	int all_ok=1;		/* at the beginning assume nothing works */
	
	/* At power on */
	ioport_set_pin_dir(LCD_RS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LCD_Enable, IOPORT_DIR_OUTPUT);
	ioport_set_port_dir(IOPORT_PIOC, LCD_mask_D4_D7, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_Enable, LOW);
	delayMicroseconds(30000);		/* wait > 15 ms */
	ioport_set_pin_level(LCD_RS, LOW);
	
	/* Function set (interface is 8 bit long) */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delayMicroseconds(1);		/* wait 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);
	delayMicroseconds(4100);	/* wait for more than 4,1 ms */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delayMicroseconds(1);	/* delay 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);
	delayMicroseconds(100);	/* wait 100 us */
	ioport_set_pin_level(LCD_D4, HIGH);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delayMicroseconds(1);	/* wait 1 us */
	ioport_set_pin_level(LCD_Enable, LOW);		
	delayMicroseconds(100);	/* wait 100 us */
		
	/* Set display to 4-bit input */
	ioport_set_pin_level(LCD_D4, LOW);
	ioport_set_pin_level(LCD_D5, HIGH);
	ioport_set_pin_level(LCD_D6, LOW);
	ioport_set_pin_level(LCD_D7, LOW);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delayMicroseconds(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	delayMicroseconds(100);
	lcdWrite(0b00101000, LOW);		/* Two rows, small font */
	lcdWrite(0b00001000, LOW);		/* Display off */
	lcdWrite(0b00000001, LOW);		/* Display clear */
	delayMicroseconds(3000);
	lcdWrite(0b00000110, LOW);		/* Entry mode set: move cursor right, no display shift */
	lcdWrite(0b00001111 ,LOW);		/* Display on, cursor on, blinking on */

	all_ok = 0;					/* simple return statement showing that the initialization of the LCD has completed */
	return all_ok;
}


int lcdWrite(uint8_t byte, bool type)		/* writes a byte to the LCD display */
/*
 *	writes the byte (8 bits) to the LCD display as two consecutive 4 bits 
 *	type = 0 controls the display
 *	type = 1 writes the content of the byte (usually interpreted as ASCII-code) to the display
 */
{
	/* In it's infinite wisdom the shield has the data pins in mirrored order compared to the Due board */
	uint8_t mirror_pin[16]={0b0000,0b1000,0b0100,0b1100,0b0010,0b1010,0b0110,0b1110,0b0001,0b1001,0b0101,0b1101,0b0011,0b1011,0b0111,0b1111};
	uint32_t byte32;
	uint8_t byte_orig;
	uint8_t mirrored_output = 0;

	byte_orig = byte;

	/* write the first 4 bits to the shield. */
	byte = byte>>4;
	byte = mirror_pin[byte];
	byte32 = (uint32_t)byte << 23;
	mirrored_output = byte<<4;
	
	ioport_set_pin_level(LCD_RS, type); 
	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delayMicroseconds(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	
	delayMicroseconds(100);
	
	/* write the second 4 bits to the shield. */
	byte = byte_orig;
	byte = byte & 0x0f;
	byte = mirror_pin[byte];
	byte32 = (uint32_t)byte<<23;
	mirrored_output = mirrored_output + byte;

	ioport_set_port_level(IOPORT_PIOC, LCD_mask_D4_D7, byte32);
	ioport_set_pin_level(LCD_Enable, HIGH);
	delayMicroseconds(1);
	ioport_set_pin_level(LCD_Enable, LOW);
	delayMicroseconds(100);
	
	return 0;
}

int lcdClearDisplay(void)
{
	lcdWrite(0b00000001, LOW);
	delayMicroseconds(5000);
	return 0;
}
