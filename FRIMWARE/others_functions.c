#include "headers.h"// Include necessary header file
// Function to read a numeric string from user input
s8* Read_String() 
{
    static s8 arr[50];// Buffer to store user input
    u8 c;// Variable for key input
    s32 i = 0;// Index variable
    
    for (i = 49; i >= 0; i--) 
        arr[i] = '\0';// Initialize buffer

    i = 0;
    while (1) 
    {
        c = Read_key();// Read key input
    	// Timeout occurred    
        if (c == TIMEOUT_FLAG)
	{ 
	     // Timeout occurred
            return NULL; // Exit without returning partial input
        }
	// End of input
	if (c == '=')
	{
            arr[i] = '\0';
            break;
        } 
	// Backspace operation
	else if (c == 'c') 
	{
            i--;
            CmdLCD(GOTO_LINE2_POS0 + i);
            CharLCD(' ');
            arr[i] = '\0';
            if (i <= 0)
                i = 0;
        }
	// Valid numeric input
	else if ((c >= '0') && (c <= '9'))
	{
            arr[i] = c;
            CmdLCD(GOTO_LINE2_POS0 + i);
            CharLCD(c);
            delay_ms(50);
            CmdLCD(GOTO_LINE2_POS0 + i);
            CharLCD(c);
            i++;
        }

        while ((ColScan() & 1) == 0);
		delay_ms(100);
    }
    return arr;// Return the entered string
}
// Function to read a 4-digit PIN input
s8* Read_PIN(u32 flag) 
{
    static s8 arry[5];// Buffer for PIN storage
    u8 c;// Variable for key input
    s32 i = 0;// Index variable

    for (i = 4; i >= 0; i--) 
        arry[i] = '\0';// Initialize buffer

    i = 0;
    while (i < 4) 
    {
        c = Read_key();// Read key input
	// Timeout occurred
        if (c == TIMEOUT_FLAG) 
	{ 
	     // Timeout occurred
            return NULL; // Exit without returning partial input
        }
	// Backspace operation
        if (c == 'c') 
	{
            i--;
            CmdLCD(GOTO_LINE2_POS0 + i);
            CharLCD(' ');
            arry[i] = '\0';
            if (i <= 0)
                i = 0;
        } 
	// Valid numeric input
	else if ((c >= '0') && (c <= '9'))
	{
         	   arry[i] = c;
         	   CmdLCD(GOTO_LINE2_POS0 + i);
         	   CharLCD(c);
         	   delay_ms(100);
          	   CmdLCD(GOTO_LINE2_POS0 + i);
		   if(flag)
			   CharLCD('*');// Mask PIN for security  
		   else
			   CharLCD(c);
            i++;
        }

        while ((ColScan() & 1) == 0);
	
	delay_ms(100);
    }
    
    arry[i] = '\0';// Terminate PIN string
    return arry;// Return entered PIN
}
//function to Read PIN
u32 validate_PIN(void)
{
	s8 buffer[30],reference_pin[10];// Buffer to hold formatted message and reference PIN
	// Allow 3 attempts to enter the correct PIN
	for(chances=3;chances>0;chances--)
	{
		CmdLCD(CLEAR_LCD);// Clear LCD screen
		CmdLCD(GOTO_LINE1_POS0);// Move cursor to first line, first position
		StrLCD((s8 *)"ENTER PIN:");// Prompt user to enter PIN
		givenpin=Read_PIN(1);// Read PIN input (with masking)
		if(givenpin==NULL)// If user doesn't input PIN (e.g., times out)
		{ 
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8*)"SESSION TIMED OUT ! ");// Inform session timeout
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("PLEASE TRY AGAIN ");// Request retry
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			send_buf_to_uart0((s8*)"#TIMEOUT$");// Notify timeout over UART0
			return 0;// Exit with failure
		}
		// Copy entered PIN to reference_pin
		strcpy((char *)reference_pin,(char *)givenpin);
#ifdef DEBUG
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD(reference_pin);// (Debug) Display entered PIN on LCD
#endif
		sprintf((char*)buffer,"#p%s$",givenpin);// Format message to send over UART
#ifdef DEBUG
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD(buffer); // (Debug) Show formatted message on LCD
		delay_ms(30);
		send_buf_to_uart0(buffer); // Send formatted PIN message to UART0
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("ENTER UART0 BUFF");// (Debug) Prompt to enter UART0 buffer
#endif 
		send_buf_to_uart0(buffer);// Send the formatted PIN to the server via UART0
		recv_buf_from_uart0(buffer,sizeof(buffer));// Receive server response into buffer
		delay_s(1);// Wait for response stability (or simulate processing delay)
		// If server returns success message
		if(str_cmp(buffer,(s8*)"@OK$")==0)
		{	
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD((s8*)"LOGIN SUCESSFULL ");// Display login success
			delay_s(1);
			strcpy((char *)pin,(char *)reference_pin);// Store the successful PIN globally
			flag1=1;// Set successful login flag
			CmdLCD(CLEAR_LCD);
			return 1;// Return success
		}
		// If server says invalid PIN
		else if(str_cmp(buffer,(s8*)"@ERR#INVLD$")==0)
		{
			IOSET0=1<<LED;//|(1<<ADC);
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("INVALID PIN ");// Inform invalid PIN
			if(chances==3) // First wrong attempt
			{
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("YOU HAVE 2 MOVES ");// Warn user about remaining attempts
				delay_s(1);
			}
			else if(chances==2)// Second wrong attempt
			{
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("YOU HAVE 1 MOVE ");// Final attempt warning
				delay_s(1);
			}
		}
		CmdLCD(CLEAR_LCD);
	}
	// If login was not successful after all chances
	if(!flag1)
	{
		IOSET0=1<<LED;
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD((s8 *)"                ");
		StrLCD("OUT OF MOVES ");// Notify user that all attempts are used
		send_buf_to_uart0((s8*)"#BLK$"); // Inform the server to block the card
		recv_buf_from_uart0(buffer,sizeof(buffer));// Wait for confirmation from server
		// If server confirms blocking
		if(str_cmp(buffer,(s8*)"@BLK$")==0)
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("YOUR CARD BLOCKED ");// Display block confirmation
			delay_s(1);
			StrLCD((s8 *)"                ");
			return 0;// Exit with failure
		}		
		IOCLR0=1<<LED;				
	}
	return 0;// Final return if all attempts failed
}
//function to validate 
u32  validate_RFID()
{
	s8 buf1[10]; // Buffer to store received RFID string
	s8 buf2[30];// Buffer to store formatted message for UART0
#ifdef DEBUG
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER UART1 BUFF");// Display debug message
#endif
		recv_str_from_uart1(buf1,10);// Receive RFID data from UART1 (likely from RFID module)
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD((s8*)"RFID NO:");//Display label
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD(buf1);// Display the RFID received
		delay_s(2);
#ifdef DEBUG
	memset((void*)uart1_rx_buf,0,MAX_BUF_LEN1);// Clear UART1 receive buffer
	recv_str_from_uart1(buf1,9);// Receive RFID again (debug purpose)
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD(buf1);// Display again for debug
#endif
	sprintf((char*)buf2,"#r%s$",buf1);// Format RFID into a protocol message for server
#ifdef DEBUG
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD(buf2);// Show formatted message
	delay_ms(200);
	send_buf_to_uart0(buf2);// Send to UART0 (server)
#endif
	send_buf_to_uart0(buf2);// Send the formatted RFID message to server through UART0
#ifdef DEBUG
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER UART0 BUFF");// Debug message
#endif 
	recv_buf_from_uart0(buf2,30);// Receive response from server via UART0
	CmdLCD(GOTO_LINE2_POS0);
	//StrLCD(buf2);
	delay_ms(200);
#ifdef DEBUG
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("TESTING UART0");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD(buf2);// Display server response
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD(buf2);// Display server response
	delay_ms(10);
#endif
	// Check if the response indicates that the card is valid and active
	if(str_cmp(buf2,(s8 *)"@OK#ACTV$")==0)
	{
		return 1;// Return success
	}
	// Check if the card is blocked
	else if(str_cmp(buf2,(s8*)"@BLKD$")==0)
	{
			 // Display block message
			IOSET0=1<<LED;
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8 *)"CARD BLOCKED !");
			CmdLCD(GOTO_LINE2_POS0);
			// Advise user to contact branch
			StrLCD("CONTACT MAIN BRANCH");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			IOCLR0=1<<LED;
	}
	// Check if the response indicates invalid card
	else if(str_cmp(buf2,(s8*)"@ERR#CARD$")==0)
	{
			// Display "ERROR
			IOSET0=1<<LED;
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8 *)"ERROR");
			// Inform invalid card info
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("INVALID CARD DETAILS ");
		  	delay_s(1);
			CmdLCD(CLEAR_LCD);
			IOCLR0=1<<LED;
	}
	return 0;// Default return: RFID validation failed
}
//function to Rotate string
void rotate_string(const char *str,int len,u32 stop)
{
	s32 i,j,pos;
	s8 buffer[16];// Temporary buffer to hold 16 characters for one LCD line
	while(1)// Infinite loop to continuously rotate the string
	{
		for(i=-16;i<len;i++)// Start from -16 to create an initial padding effect
		{
			for(j=0;j<16;j++)// Fill 16 characters for the LCD line
			{
				pos=i+j;// Calculate the actual index in the original string
				if(pos<0||pos>=len)// If out of bounds of original string
				{
					buffer[j]=' ';// Fill with space
				}
				else
				{
					buffer[j]=str[pos];// Otherwise copy character from original string
				}
				 // If UART1 has received new data, exit early
				if(uart1_rx_complete)
				{
					break;
				}
			}
			// If UART1 received data during inner loop
			if(uart1_rx_complete)
			{
				CmdLCD(CLEAR_LCD);
				break;// Exit outer loop as well
			}
			buffer[j]='\0';
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD(buffer);// Display current portion of the string
			delay_ms(200);
		}
		// Display current portion of the string
		if(uart1_rx_complete)
		{
			break; // Exit the outer while loo
		}
		// If external stop condition is triggered
		else if(stop)
		{
			break;
		}
	}
}
//function to select the option
void main_MENU()
{
	s8 c;//character for user choice
	while(1)
	{
		CmdLCD(CLEAR_LCD);		
		c=Validate(4,MENU);//to validate the user input
		CmdLCD(CLEAR_LCD);
		//if time out occured
		if(c==NULL)
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8*)"SESSION TIMED OUT ! ");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("PLEASE TRY AGAIN ");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			//Sending the Time out message to UART0
			send_buf_to_uart0((s8*)"#TIMEOUT$");
			break;
		}
		//function to Balance Enquery
		if(c=='1')
		{
			CmdLCD(CLEAR_LCD);
			Bal_Enq();
			CmdLCD(CLEAR_LCD);
		}
		//function to Deposit balance
		else if(c=='2')
		{
			CmdLCD(CLEAR_LCD);
			//if deposit break the while loop
			if(Deposit())
			{
				break;
			}
			CmdLCD(CLEAR_LCD);
		}
		//function to Withdraw amount
		else if(c=='3')
		{
			CmdLCD(CLEAR_LCD);
			//if Withdrwal fail break the while loop
			if(Withdraw())
			{
				break;
			}
			CmdLCD(CLEAR_LCD);
		}
		//function to Change the PIN
		else if(c=='4')
		{
			CmdLCD(CLEAR_LCD);
			//if PIN Change failed
			if(Pin_Change())
			{
				break;
			}
			CmdLCD(CLEAR_LCD);			
		}
		//function to MINI Statement
		else if(c=='5')
		{
			CmdLCD(CLEAR_LCD);
			Mini_Statement();
			CmdLCD(CLEAR_LCD);			
		}
		//function to exit from the while loop
		else if(c=='6')
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8 *)"   EXITED !");
			delay_s(2);
			CmdLCD(CLEAR_LCD);
			//Sending the EXIT Message to the UART0
			send_buf_to_uart0((s8*)"#EXIT$");
			break;
		}
		//if Wromg input is given inform the user
		else
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8 *)"WRONG INPUT!");
			delay_s(2);
			CmdLCD(CLEAR_LCD);	
		}
	}
	CmdLCD(CLEAR_LCD);
}
//function to validate the user entered input correct or not
s8 Validate(u32 j,s8 (*str)[16])
{
	u32 i=0;// Index to track the current selection position
	u8 c;//chracter to user input
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD(str[i]);// Display the first string option
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD(str[i+1]);// Display the second string option
	// Infinite loop to wait for user selection
	while(1)
	{
		c=Read_key();// Read a key from the keypad
		while((ColScan()&1)==0);// Wait until key release (debouncing)
		if(c==TIMEOUT_FLAG)// If timeout occurred
		{
			return NULL; // Return NULL to indicate timeout
		}
		else if(c=='*')// If user pressed '*' (navigate forward)
		{
			if(i<j)// Make sure we don't go past the end
				i++;// Move to the next pair of options
			else // Stay at current position if at end
				continue;
		}
		else if(c=='/')// If user pressed '/' (navigate backward)
		{
			if(i>0)// Ensure we don't go below zero
				i--;// Move back to the previous pair
			else 
				continue;// Stay at current position if at beginning
		}
		// Check if user selected one of the two displayed options
		else if((c==str[i][0])||(c==str[i+1][0]))
		{
			break;// Valid selection, break the loop
		}
		// Update LCD with current options after any key press
		CmdLCD(CLEAR_LCD);		
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD(str[i]);
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD(str[i+1]);
	}
	// Return the valid selected character
	return c;
}
//function for Receving the CARD number from UART!
void recv_str_from_uart1(s8 *str,u32 len)
{
#ifdef DEBUG
	    strcpy((char*)str,"12345678");//directly initialising for Debugging purpose	
#else
    while(!uart1_rx_complete);//waits for until completion of uart1_rx_complete
    strncpy((char*)str,(char *)uart1_rx_buf,len > MAX_BUF_LEN1 ? MAX_BUF_LEN1 : len);//copying to the str
#endif 
    uart1_rx_complete=0;//setting the uart1_rx_complete 
}
//Receveing Response from the UART0
void recv_buf_from_uart0(s8 *str,u32 len)
{	
	//filling with null character in uart0_rx_buffer
		memset((void*)uart0_rx_buf,0,MAX_BUF_LEN2);
		while(!uart0_rx_complete);//until waits for Reception is completed
    strncpy((char*)str,(char *)uart0_rx_buf,len);//copying to the str
		uart0_rx_complete=0;//setting the uart0_rx_complete
}
//sending the request to the UART0
void send_buf_to_uart0(s8 *str)
{
	s8 buf1[14]="#OK:CNTD$",buf2[14];
	
			while(1)//checking for proper connection is there or not 
			{
				U0_TxStr(buf1);
				recv_buf_from_uart0(buf2,14);
				//if there it breaks
				if(str_cmp(buf2,(s8*)"@OK:CNTD$")==0)
				{
					break;
				}
				else//until waits for proper connection
				{
					CmdLCD(CLEAR_LCD);		
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD((s8*)"WAITING FOR RESPONSE");
				}
			}
			U0_TxStr(str);//Transmitting originral buffer
}/*
void send_buf_to_uart0(s8 *str) 
{
    s8 buf1[14] = "#OK:CNTD$", buf2[14];

    while (1) 
    {
        uart0_rx_complete = 0;  // Reset flag before transmission
        uart0_rx_valid = 0;  // Ensure fresh validation

        U0_TxStr(buf1);  // Send handshake message

        while (!uart0_rx_complete);  // Wait for response

        recv_buf_from_uart0(buf2, 14);  // Read response

        // Retry if message is incorrect
        if (uart0_rx_valid == 1 && str_cmp(buf2,"@OK:CNTD$") == 0) 
        {
            break;  // Stop retransmitting once correct response arrives
        }
        else 
        {
            CmdLCD(CLEAR_LCD);
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD((s8 *)"WAITING FOR RESPONSE");
            
            // Continue looping until response is valid
        }
    }

    // Once handshake is successful, send actual data
    U0_TxStr(str);
}*/
// Function to compare two strings
u32 str_cmp(s8 *str1, s8 *str2) 
{
	 //while loop for comparing and checking the buffer
	while (*str1 && (*str1 == *str2))
	{
        	str1++;//incrementing the str1
        	str2++;//increamenting the str2
    	}
    	//checking and sending difference or both are equal
	return (u32)(*(unsigned char *)str1 - *(unsigned char *)str2);
}

// Function to compare two strings up to a given number of characters
u32 str_ncmp(s8 *str1, s8 *str2, u32 n) 
{
	//while loop for comparing and checking the buffer
    	while (n-- && *str1 && (*str1 == *str2)) 
	{
        	str1++;//incrementing the str1
        	str2++;//increamenting the str2
    	}
	//checking and sending difference or both are equal
    	return n == (u32)-1 ? 0 : (u32)(*(unsigned char *)str1 - *(unsigned char *)str2);
}
//user defined streln
u32 str_len(s8 *str) 
{
    int length = 0;
    //while loop for checking and increamenting the length count
    while (str[length] != '\0') {
        length++;
    }
    return length;//return the length
}
//user defined ASCII TO INTEGER
int atoi_arm(s8 *str)
{
    int result = 0;
    while (*str)
    {
	//checking the numeric charcter or not
        if (*str >= '0' && *str <= '9') 
            result = result * 10 + (*str - '0');  // Convert ASCII to integer
        else 
            return -1;  // Invalid input
        str++;
    }
    return result;//return the integer
}
