// Starting pin number for 8-bit LCD data lines (P0.16 to P0.23)
#define LCD_DATA 16
#define LCD_RS 3// LCD Registre Select pin connected to P0.3
#define LCD_RW 5// LCD Read/Write control pin connected to P0.5
#define LCD_EN 4// LCD Enable pin connected to P0.4

#define CLEAR_LCD 0x01// Command to clear the LCD display
#define SHIFT_CUR_RIGHT 0x06// Command to shift cursor to the right after each character
#define DSP_OFF 0x08// Command to turn off the display
#define DSP_ON_CUR_OFF 0x0C// Command to turn on display, cursor off
#define MODE_8BIT_2LINE 0x38// Command to set LCD to 8-bit mode with 2 lines
#define GOTO_LINE1_POS0 0x80// Command to move cursor to Line 1, Position 0
#define GOTO_LINE2_POS0 0xC0// Command to move cursor to Line 2, Position 0
