#include "headers.h"//includuing the necessary header files
//function for Read input from the user string
s8* Read_String(void);
//function for Read the input from the user KEY
u8 Read_key(void);
//function to Read the user input PIN
s8* Read_PIN(u32);
//function to Display Welcome message
void Display_Wel(void);
//function to Validate the RFID Card
u32  validate_RFID(void);
//function to Validate the PIN
u32  validate_PIN(void);
//function to Recv buffer from UART1
void recv_str_from_uart1(s8 *,u32 );
//function to Recv buffer from UART0
void recv_buf_from_uart0(s8 *,u32);
//function to send buffer to UART0
void send_buf_to_uart0(s8 *);
//function to Rotate String
void rotate_string(const char *,int ,u32 );
//function to User Menu
void main_MENU(void);
//function to validate the user input to Selecting the option
s8 Validate(u32 ,s8 (*)[]);
//user defined string comparing
u32 str_cmp(s8 *,s8 *);
//user defined string n compare
u32 str_ncmp(s8 *,s8 *,u32 );
//function to calculate string length
u32 str_len(s8 *);
//user defined ASCII to integer
int atoi_arm(s8*);

