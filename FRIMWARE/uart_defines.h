#define FOSC 12000000// Frequency of the oscillator in Hz (12 MHz)
#define CCLK (FOSC*5)// CPU Clock = 5 × FOSC (used by PLL)
#define PCLK (CCLK/4)// Peripheral Clock = CPU Clock / 4
#define BAUD 9600 // Desired UART baud rate
#define DIVISOR (PCLK/(16*BAUD))// UART divisor for baud rate generation
#define _8BIT 3// 8-bit word length selection (value for 8-bit mode in UART)
#define WORD_LEN_SEL_BITS _8BIT// Macro to define word length selection bits for UART
#define DLAB_BIT 7// Bit position of DLAB (Divisor Latch Access Bit) in LCR register
#define DR_BIT 0// Bit position of DR (Data Ready) in LSR register
#define TEMT_BIT 6// Bit position of TEMT (Transmitter Empty) in LSR register

