#include "headers.h"// Include necessary header file
// Function to initialize UART0
void Init_UART0(void)
{
	PINSEL0=((PINSEL0&~(3<<(2*0)))|(1<<(2*0)));// Configure UART0 TXD pin
	PINSEL0=((PINSEL0&~(3<<(2*1)))|(1<<(2*1)));// Configure UART0 RXD pin
	U0LCR=((1<<DLAB_BIT)|(WORD_LEN_SEL_BITS));// Enable DLAB to set baud rate
	U0DLL=(DIVISOR);// Load divisor for baud rate
	U0DLM=(DIVISOR>>8);
	U0LCR&=~(1<<DLAB_BIT);// Disable DLAB to configure UART operations
	U0IER = 0x01;// Enable UART0 interrupts
  VICIntSelect = 0x00000000;  // Set VIC interrupt selection
  VICIntEnable |= (1 << 6);// Enable UART0 interrupt
  VICVectAddr0 = (unsigned int)UART0_ISR;// Set interrupt handler
  VICVectCntl0 = 0x20 | 6;// Configure priority
}
// Function to transmit a single byte via UART0
void U0_TxByte(u8 sByte)
{
	U0THR=sByte;// Load byte into transmit register
	while(((U0LSR>>TEMT_BIT)&1)==0);// Wait until transmission is complete
}
// Function to receive a single byte via UART0
u8  U0_RxByte(void)
{
	while(((U0LSR>>DR_BIT)&1)==0);// Wait for data
	return U0RBR;// Read received byte
}

// Function to transmit a string via UART0
void U0_TxStr(s8 *str)
{
	while(*str)// Send characters until null terminator
		U0_TxByte(*str++);
}
// Function to receive a string via UART0
s8* U0_RxStr(void)
{
	static s8 buffer[100];// Buffer to store received string
	u32 i=0;
	while(1)
	{
		buffer[i]=U0_RxByte();
		if(buffer[i]=='$')// End of transmission
		{
			break;
		}
		i++;
	}
	buffer[i+1]='\0';// Null-terminate string
	return buffer;
}

void Init_UART1(void)
{
	 // Configure P0.8 as TXD1 (01), and P0.9 as RXD1 (01)
	 // Clear existing bits, then set appropriate function bits for UART1
	PINSEL0=((PINSEL0&~(3<<(2*8)))|(1<<(2*8)));
	PINSEL0=((PINSEL0&~(3<<(2*9)))|(1<<(2*9)));
	U1LCR=((1<<DLAB_BIT)|(WORD_LEN_SEL_BITS));// Enable access to divisor latches (DLAB = 1) and set word length = 8 bits
	// Set baud rate using divisor latch (DLL and DLM)
	// U1DLL holds lower 8 bits, U1DLM holds upper 8 bits of divisor
	U1DLL=(DIVISOR);
	U1DLM=(DIVISOR>>8);
	// Disable DLAB after setting divisor to access THR, RBR, etc.
	U1LCR&=~(1<<DLAB_BIT);
	U1IER = 0x01;// Enable RBR (Receive Data Available) interrupt
	VICIntSelect =0x00000000; // Configure interrupt controller: UART1 is IRQ (not FIQ)
	VICIntEnable |= (1 << 7);// Set the address of the UART1 ISR (interrupt service routine)
	VICVectAddr1 = (unsigned int)UART1_ISR;
	VICVectCntl1 = 0x20 | 7;// Enable slot 1 for UART1 interrupt and assign interrupt source #7
}
//function to Transmitt byte
void U1_TxByte(u8 sByte)
{
	U1THR=sByte;// Load the byte into the UART1 Transmit Holding Register
	while(((U1LSR>>TEMT_BIT)&1)==0);// Wait until Transmit Holding Register is empty (TEMT bit = 1)
}
// Receive a single byte from UART1
u8  U1_RxByte(void)
{
	while(((U1LSR>>DR_BIT)&1)==0);// Wait until data is available in the Receive Buffer (DR bit = 1)
	return U1RBR;// Return the received byte from Receive Buffer Register
}
// Transmit a null-terminated string over UART1
void U1_TxStr(s8 *str)
{
	while(*str)// Send characters one by one until null terminator is reached
		U1_TxByte(*str++);
}
// Function to receive a string from UART1 until the '$' termination character is encountered
s8* U1_RxStr(void)
{
	static s8 buffer[100];// Declare a static buffer to retain data after the function returns
	u32 i=0;// Index to track buffer position
	while(1)// Continuously receive characters from UART1
	{
		buffer[i]=U1_RxByte();// Read a byte from UART1 and store in buffer
		if(buffer[i]=='$')// Check for termination character '$'
		{
			break;// End of string received
		}
		i++;// Move to next buffer index
	}
	buffer[i+1]='\0';// Null-terminate the string properly
	return buffer;// Return pointer to the received string
}
// UART1 Interrupt Service Routine
void UART1_ISR(void)__irq
{
	u8 ch;// Variable to store received character
	u32 iirval=U1IIR;// Read the Interrupt Identification Register
	// Check if the interrupt is due to "Receive Data Available"
    	if((iirval&0x0F)==0x04)
    	{
       		 ch=U1RBR;// Read received character from UART1 Receiver Buffer Registe
		if(!uart1_rx_complete)// If reception is not yet complete
		{
			if(!uart1_rx_started)// Check if start of frame not detected yet
			{
				if(ch==0x02)// Check for STX (Start of Text) character: 0x02
				{
					uart1_rx_index=0;// Reset buffer index
					uart1_rx_started=1;// Start receiving data
				}
			}
			else
			{
				if(ch==0x03)// Check for ETX (End of Text) character: 0x03
				{
					uart1_rx_buf[uart1_rx_index]='\0';// Null-terminate the received string
					uart1_rx_complete=1; // Mark reception as complete
					uart1_rx_started=0;// Reset start flag
					uart1_rx_index=0;// Reset index for future receptions
				}
				// Accept only numeric characters (ASCII 48–57) and ensure buffer does not overflow
				else if((uart1_rx_index<MAX_BUF_LEN1-1)&&((ch>=48)&&(ch<=57)))
				{
				    uart1_rx_buf[uart1_rx_index++]=ch;// Store valid character into buffer
				}
			}
		}
	}
    	VICVectAddr=0x00;// Signal end of interrupt to the VIC
}

/*void UART0_ISR(void)__irq
{
    char ch;
	u32 iirval=U0IIR;
    if((iirval&0x0F)==0x04) 
    {
        ch=U0RBR;
        if(uart0_rx_index<MAX_BUF_LEN2-1)
        {
            uart0_rx_buf[uart0_rx_index++]=ch;
            if(ch=='$')
            {
                uart0_rx_buf[uart0_rx_index]='\0';
                uart0_rx_complete=1;
                uart0_rx_index=0;
            }
        }
    }
    VICVectAddr = 0x00;
}*/

void UART0_ISR(void) __irq
{
    char ch;// Variable to store received character
    static int receiving = 0;// Static flag to track if a message is currently being received
    u32 iirval = U0IIR;// Read UART0 Interrupt Identification Register
	// Check if interrupt was caused by "Receive Data Available"
    if ((iirval & 0x0F) == 0x04) 
    {
        ch = U0RBR; // Read received character from UART0 Receiver Buffer Register
	// If '@' (start symbol) is received, begin receiving a new message
        if (ch == '@') 
        {
            receiving = 1;// Set receiving flag
            uart0_rx_index = 0;// Reset buffer index
            uart_checksum = 0;// Reset checksum
        }
	// If currently receiving a message and buffer has space
        if (receiving && uart0_rx_index < MAX_BUF_LEN2 - 1) 
        {
		// Accept only valid characters for the protocol (alphanumeric and symbols)
            if (ch == '@' || ch == '#' || ch == '$' || ch == ':' || ch == '_' || ch=='.'||ch=='|'||ch=='-'||
                (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) 
            {
                uart0_rx_buf[uart0_rx_index++] = ch;// Store valid character in buffer
                uart_checksum += ch;// Update checksum
            }

            // Check if `$` is received
            if (ch == '$') 
            {
                uart0_rx_buf[uart0_rx_index] = '\0';  // Null-terminate the received string
                receiving = 0;// Stop receiving
		// Validate that the message is non-empty and has meaningful content
                if (uart_checksum > 0 && uart0_rx_index > 1)   
                {
                    uart0_rx_complete = 1;// Mark reception as complete
                    uart0_rx_valid = 1;  // Mark data as valid
                }
                else 
                {
                    uart0_rx_complete = 0;  // Mark reception as incomplete
                    uart0_rx_valid = 0;// Mark data as invalid
                }
                uart0_rx_index = 0;// Reset buffer index for next message
            }
        }
    }

    // **If `$` was never received, force retransmission**
    if (receiving && uart0_rx_index > 0 && uart0_rx_buf[uart0_rx_index - 1] != '$') 
    {
        uart0_rx_valid = 0; // Mark as invalid
        uart0_rx_complete = 0; // Ensure retry happens
    }
    VICVectAddr = 0x00;// Signal end of ISR to the VIC (interrupt controller)
}
