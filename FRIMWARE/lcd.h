#include "types.h"
void WriteLCD(u8 );// Writes raw data/command to LCD port
void CmdLCD(u8 );// Sends a command byte to the LCD
void CharLCD(u8 );// Displays a single character on the LCD
void InitLCD(void);// Initializes the LCD with configuration commands
void StrLCD(s8 *);// Displays a null-terminated string on the LCD
void U32LCD(u32);// Displays an unsigned 32-bit integer on the LCD
void S32LCD(s32);// Displays a signed 32-bit integer on the LCD
void F32LCD(f32,u32);// Displays a floating-point number with given precision
void HexLCD(u32);// Displays a 32-bit number in hexadecimal format
void OctLCD(u32);// Displays a 32-bit number in octal format
void BinLCD(u32,u32);// Displays a binary representation of a number up to given bits
void BuildCGRAM(u8*,u8);// Builds custom characters into CGRAM at given location
