#ifndef HEADER// If HEADER is not already defined,
#define HEADER  // Define HEADER to prevent future re-inclusion

#include <LPC21xx.h>// Include device-specific header for LPC21xx microcontrollers
#include <string.h>// Include standard C library for string handling
#include <stdlib.h>// Include standard C library for memory allocation, conversions, etc.
#include <stdio.h>// Include standard C library for input/output functions

// Include custom headers
#include "types.h"// Include custom type definitions (e.g., s8, u8, s16
#include "lcd.h"// Include LCD function prototypes
#include "lcd_defines.h"// Include LCD pin and command macros
#include "kpm.h"// Include keypad module function prototypes
#include "kpm_defines.h"// Include keypad-related macros
#include "delay.h"// Include delay functions
#include "uart.h"// Include UART communication function prototypes
#include "uart_defines.h" // Include UART configuration and macros
#include "others_functions.h"// Include other utility functions
#include "bank_functions.h"// Include banking application functions

#define LED 15// Define LED as pin number 15 (used for status indication)
//#define DEBUG// Uncomment to enable DEBUG mode (used for testing/diagnostics)
#define MAX_BUF_LEN1 9// Maximum buffer length for UART1
#define MAX_BUF_LEN2 100// Maximum buffer length for UART0 or general use
#define TIMEOUT_FLAG 255  // Special value to indicate timeout
#define MAX_AMOUNT 30000// Maximum transaction amount limit (banking limit)
// 'pin' holds the current PIN (max 4 digits + '\0'); 'givenpin' is a pointer to the entered PIN
extern s8 pin[5], *givenpin;
extern u32 flag1, chances,attempts,pinchange;
// 'flag1' indicates login success
// 'chances' stores remaining PIN entry attempts
// 'attempts' may track number of login attempts
// 'pinchange' flag to indicate whether PIN was changed
extern s8 KPMLUT[][4];// Keypad lookup table mapping rows and columns to key values
extern s8 MENU[][16];// Menu options displayed on the LCD, each up to 16 characters wide

// UART0 receive buffer and control flag
extern volatile s8 uart0_rx_buf[MAX_BUF_LEN2];// Buffer to hold received data from UART0
extern volatile u32 uart0_rx_index;// Current index into UART0 buffer
extern volatile u32 uart0_rx_complete;// Flag indicating UART0 message is fully received

// UART1 receive buffer and control flags
extern volatile s8 uart1_rx_buf[MAX_BUF_LEN1];// Buffer to hold received data from UART1
extern volatile u32 uart1_rx_index;// Current index into UART1 buffer
extern volatile u32 uart1_rx_complete;// Flag indicating UART1 message is fully received
extern volatile u32 uart1_rx_started;// Flag indicating UART1 reception has started
extern volatile u32 uart_checksum ;// Variable used to verify checksum of received UART1 data
 // Flag indicating if the UART0 received message is valid (e.g., passed checksum or format checks)
extern u32 uart0_rx_valid;

// End of header file protection
#endif  // HEADER

