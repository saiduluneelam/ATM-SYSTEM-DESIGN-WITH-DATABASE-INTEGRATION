#include "headers.h"// Include necessary header file
// Function to send a byte of data to the LCD
void WriteLCD(u8 data)
{
	IOPIN1=((IOPIN1&~(0XFF<<LCD_DATA))|(data<<LCD_DATA));// Place data on LCD data bus
	IOCLR0=1<<LCD_RW;// Set write mode
	IOSET0=1<<LCD_EN;// Enable LCD to latch data
	delay_ms(1);// Short delay for data processing
	IOCLR0=1<<LCD_EN;// Disable LCD enable pin
	delay_ms(2);// Extra delay for LCD operation
}
// Function to send a command to the LCD
void CmdLCD(u8 cmd)
{
	IOCLR0=1<<LCD_RS; // Select command register
	WriteLCD(cmd);// Write command to LCD
}
// Function to send a character to the LCD for display
void CharLCD(u8 ascii)
{
	IOSET0=1<<LCD_RS;// Select data register
	WriteLCD(ascii);// Write ASCII character to LCD
}
// Function to initialize the LCD in 8-bit mode
void InitLCD(void)
{
	IODIR1|=((u32)0xFF<<LCD_DATA);// Set LCD data pins as output
	IODIR0|=(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);// Set control pins as output
	delay_ms(15);// Delay for LCD power-on stabilization
	CmdLCD(0x30);// Command to set 8-bit mode
	delay_ms(2);
	delay_us(100);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE);// Configure LCD for 8-bit mode and 2-line display
	CmdLCD(DSP_ON_CUR_OFF);// Turn on display, turn off cursor
	CmdLCD(CLEAR_LCD);// Clear LCD screen
	CmdLCD(SHIFT_CUR_RIGHT);// Set cursor shift direction
}
// Function to print a string to the LCD
void StrLCD(s8 *str)
{
	while(*str)// Iterate through the string characters
		CharLCD(*str++);// Display each character on LCD
}
