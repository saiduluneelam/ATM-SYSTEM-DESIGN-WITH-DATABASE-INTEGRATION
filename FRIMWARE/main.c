#include "headers.h"// Include necessary header file

// Menu options for ATM operations
s8 MENU[][16]={"1:BALANCE","2:DEPOSIT","3:WITHDRAW","4:PIN CHANGE","5:MINI STATEMENT","6:EXIT"};

// Keypad lookup table mapping keys to their corresponding values
s8 KPMLUT[][4]={'1','2','3','*','4','5','6','/','7','8','9','-','c','0','=','+'};

// PIN storage and user-entered PIN pointer
s8 pin[5],*givenpin;

// Flags for validation and attempts tracking
u32 flag1=0,chances,attempts=0,pinchange=0;

// UART0 receive buffer and control variables
volatile s8 uart0_rx_buf[MAX_BUF_LEN2]={0};
volatile u32 uart0_rx_index = 0;
volatile u32 uart0_rx_complete = 0;

// UART1 receive buffer and control variables
volatile s8 uart1_rx_buf[MAX_BUF_LEN1]={0};
volatile u32 uart1_rx_index = 0;
volatile u32 uart1_rx_complete = 0;
volatile u32 uart1_rx_started = 0;
u32 uart0_rx_valid=0;

// Variable for tracking UART checksum
volatile unsigned int uart_checksum = 0;

// Main function to execute the ATM program
int main()
{
	s8 buffer[30];
	IODIR0|=1<<LED;// Configure LED as output
	InitKPM();// Initialize keypad matrix
	InitLCD();// Initialize LCD display
	Init_UART0();// Initialize UART0 communication
	Init_UART1();// Initialize UART1 communication
	while(1)// Main program loop
	{
		CmdLCD(CLEAR_LCD);// Clear LCD screen
		// Display welcome message
		rotate_string("WELCOME TO ABC ATM ",strlen("WELCOME TO ABC ATM "),0);
		attempts=0;
		pinchange=0;
		// Check RFID validity
		if(validate_RFID())
		{
				U1IER = 0x00;  // Disable UART1 interrupts
				VICIntEnClr = (1 << 7);  // Clear VIC interrupt enable bit for UART1
				if(validate_PIN())// Validate user PIN
				{
					main_MENU();// Display main ATM menu
				}
				U1IER = 0x01;  // Enable UART1 Receive Data Available interrupt
				VICIntEnable |= (1 << 7);  // Re-enable VIC interrupt for UART1
		}
	}
}
