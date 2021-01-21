//-----------------------------------------------------------------------------
//
//  main.c
//
//  Swallowtail 1602A LCD Demo Firmware
//  AVR (ATtiny26) 1602A LCD Demo Firmware
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
#ifndef F_CPU
#define F_CPU 1000000UL //Set clock speed to 1MHz (Internal)
#endif

/******************** Includes ***************************/
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_1602A_attiny26.h"

/******************* Globals *****************************/


/******************** Functions **************************/


/********** Interrupt Service Routines *******************/


/******************** Main *******************************/
int main(void)
{
	//Initialize the LCD
	LCD_1602A_init();
	//Send the first message string
	LCD_1602A_Write_String("Swallowtail");
	//Set the cursor to the lower row/col #5
	LCD_1602A_Set_Cursor(5, 1);
	//Send the second message string
	LCD_1602A_Write_String("Electronics");
    /* State machine loop */
    while (1) 
    {
		
    }
}

