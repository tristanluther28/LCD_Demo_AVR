//-----------------------------------------------------------------------------
//
//  LCD_1602A_attiny.h
//
//  Swallowtail 1602A LCD Firmware
//  AVR (ATtiny26) 1602A LCD Firmware
//
//  Copyright (c) 2021 Swallowtail Electronics
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sub-license,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//  Web:    http://tristanluther.com
//  Email:  tristanluther28@gmail.com
//
//-----------------------------------------------------------------------------

/******************** Macros *****************************/
#define DDR_LCD DDRA
#define PORT_LCD PORTA
#define RS PA2
#define E PA3
#define D4 PA4
#define D5 PA5
#define D6 PA6
#define D7 PA7

/******************** Includes ***************************/
#include <avr/io.h>
#include <util/delay.h>

/******************* Globals *****************************/


/******************** Functions **************************/
//Write a single command to the display
void LCD_1602A_Write_Cmd(char cmd){
	char cmd_high;
	char cmd_low;
	cmd_high = cmd & 0xF0; //Mask lower nibble and send the high nibble over the port
	PORT_LCD = cmd_high;
	PORT_LCD &= ~(1<<RS);	//When RS is 0 the command register is accessed
	PORT_LCD |= (1<<E); //Enable the data nibble to be read
	_delay_us(1);
	PORT_LCD &= ~(1<<E); //Disable the read
	_delay_ms(3);
	cmd_low = ((cmd<<4) & 0xF0); //Shift 4-bit and mask to send the high nibble
	PORT_LCD = cmd_low;
	PORT_LCD &= ~(1<<RS);	//When RS is 0 the command register is accessed
	PORT_LCD |= (1<<E); //Enable the data nibble to be read
	_delay_us(1);
	PORT_LCD &= ~(1<<E); //Disable the read
	_delay_ms(3);
}

//Clear the LCD screen
void LCD_1602A_Clear(){
	LCD_1602A_Write_Cmd(0x01);
	LCD_1602A_Write_Cmd(0x80);
}

//Initialize the outputs for this LCD display
void LCD_1602A_init(){
	/* Initialize the I/O Registers */
	/*				-I/O Map-
	 *	RS (Selects either data or instruction register): PA2 (1: Output)
	 *  E (Enable): PA3 (1: Output)
	 *	D4: PA4 (1: Output)
	 *	D5: PA5 (1: Output)
	 *	D6: PA6 (1: Output)
	 *	D7: PA7 (1: Output)
	 */
	DDR_LCD = (1<<D4) | (1<<D5) | (1<<D6) | (1<<D7) | (1<<RS) | (1<<E);
	//Set the default values for outputs to zero and inputs to have pull-up resistors
	PORT_LCD = (0<<D4) | (0<<D5) | (0<<D6) | (0<<D7) | (0<<RS) | (0<<E);
	//Wait a brief second
	_delay_ms(20);
	//Set-up the LCD for 4-bit operation with 2-line operation
	LCD_1602A_Write_Cmd(0x02);
	LCD_1602A_Write_Cmd(0x28);
	//Turn off the display cursor
	LCD_1602A_Write_Cmd(0x0C);
	//Allow the cursor to auto-increment
	LCD_1602A_Write_Cmd(0x06);
	//Clear the display and return the cursor to the home position
	LCD_1602A_Clear();
	return; //Return to call point
}

//Write a single byte (char) to the display at the given location
void LCD_1602A_Write_Char(char c){
	uint8_t c_high;
	uint8_t c_low;
	c_high = c & 0xF0; //Mask lower nibble and send the high nibble over the port
	PORT_LCD = c_high;
	PORT_LCD |= (1<<RS);	//When RS is 1 the data register is accessed
	PORT_LCD |= (1<<E); //Enable the data nibble to be read
	_delay_us(1);
	PORT_LCD &= ~(1<<E); //Disable the read
	_delay_ms(3);
	c_low = ((c<<4) & 0xF0); //Shift 4-bits and mask to send the high nibble
	PORT_LCD = c_low;
	PORT_LCD |= (1<<RS);	//When RS is 1 the data register is accessed
	PORT_LCD |= (1<<E); //Enable the data nibble to be read
	_delay_us(1);
	PORT_LCD &= ~(1<<E); //Disable the read
	_delay_ms(3);
}

//Write a string to the LCD
void LCD_1602A_Write_String(char *str){
	int i; //Iterator variable
	for(i=0;str[i]!=0;i++) //Write each character until we reach null
	{
		LCD_1602A_Write_Char(str[i]); //Write the char
	}
}

//Moves the LCD cursor to a specified location on the screen
void LCD_1602A_Set_Cursor(uint8_t x, uint8_t y){
	if (y == 0 && x<16){
		LCD_1602A_Write_Cmd((x & 0x0F)|0x80);	/* Command of first row and required position<16 */
	}
	else if (y == 1 && x<16){
		LCD_1602A_Write_Cmd((x & 0x0F)|0xC0);	/* Command of first row and required position<16 */	
	}
}


/********** Interrupt Service Routines *******************/
