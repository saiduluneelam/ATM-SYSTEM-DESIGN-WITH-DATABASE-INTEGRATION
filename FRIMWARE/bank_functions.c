#include "headers.h"// Include required header file
// Function to check account balance inquiry
void Bal_Enq()
{
	s8 buffer[20]={0},bal[6]={0};// Buffers for request and balance value
	strcpy((char *)buffer,"#REQ$");// Set balance inquiry request
	send_buf_to_uart0(buffer);// Send request via UART
	recv_buf_from_uart0(buffer,sizeof(buffer));// Receive response via UART
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD((s8*)"WAITING FOR RESPONSE");
	delay_s(1);
	CmdLCD(CLEAR_LCD);
	// Check if response contains balance details		
	if(str_ncmp(buffer,(s8*)"@BAL:",5)==0)
	{
		strcpy((char*)bal,(const char*)buffer+5);// Extract balance
		bal[str_len(bal)-1]='\0';// Remove trailing character
		// Display balance on LCD
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);	
		StrLCD((s8 *)"AVL BALANCE:");
		CmdLCD(GOTO_LINE2_POS0);	
		StrLCD(bal);
		delay_s(2);
	}
}
// Function to process a deposit transaction
u32 Deposit()
{
	s8 amount[10],buffer[30];// Buffers for deposit amount and request
	u32 paisa;// Variable for amount entered
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD((s8 *)"DEPOSIT AMOUNT");
		givenpin=Read_String();// Read user input
	       // Check for timeout
		if(givenpin==NULL)
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8*)"SESSION TIMED OUT ! ");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("PLEASE TRY AGAIN ");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			send_buf_to_uart0((s8*)"#TIMEOUT$");
			return 1;
		}
		paisa=atoi_arm(givenpin);// Convert input to integer
		// Validate deposit amount
		if((paisa>0&&paisa<=MAX_AMOUNT))
		{
			break;  // **Exit loop if amount is valid**
		} 
		else 
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("INVALID AMOUNT! ");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("AMOUNT <= 30000");
			delay_s(1);
		}

	}
	strcpy((char *)amount,(const char*)givenpin);// Copy amount input
	sprintf((char*)buffer,"#DEP:%s$",amount);// Format deposit request
	send_buf_to_uart0(buffer);// Send request via UART
	recv_buf_from_uart0(buffer,sizeof(buffer));// Receive response via UART
	CmdLCD(GOTO_LINE1_POS0);	
	delay_ms(400);
	// If deposit is successful
	if(str_ncmp(buffer,(s8*)"@BAL:",5)==0)
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);	
		StrLCD((s8 *)"DEPOSIT SUCCESS");
		CmdLCD(GOTO_LINE2_POS0);	
		StrLCD(amount);		
		delay_s(2);					
	}
	return 0;
}
//Withdraw function for the withdrwal amount
u32 Withdraw()
{
	s8 amount[10],buffer[40],bal[6];
	u32 paisa;

	while(1)
	{
		 CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD((s8 *)"WITHDRWAL AMOUNT");
		givenpin=Read_String();
		//checking for TIMEOUT
		if(givenpin==NULL)
		{
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8*)"SESSION TIMED OUT ! ");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("PLEASE TRY AGAIN ");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			send_buf_to_uart0((s8*)"#TIMEOUT$");
			return 1;
		}
		//convering the given amount in string format to the integer format
		paisa=atoi_arm(givenpin);
		//Checking the given amount is valid or not like multiples of 100 or not
		//if((givenpin[strlen((const char*)givenpin)-1]!='0')&&(givenpin[strlen((const char*)givenpin)-2]!='0'))
		if(givenpin[strlen((const char*)givenpin)-1]!='0')
		{
			if(givenpin[strlen((const char*)givenpin)-2]!='0')
			{
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD("INVALID AMOUNT! ");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("MULTIPLES OF 100's");
				delay_s(1);
			}
		}
		//if entered amount is >0 and <30000
		else if(paisa>0&&paisa<=MAX_AMOUNT) 
		{
				break;  // **Exit loop if amount is valid**
		} 
		else 
		{
			//if amount enterd is less than 0 or greater than 30000 diaplaying message on LCD
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD("INVALID AMOUNT! ");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("AMOUNT <= 30000");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8 *)"DEPOSIT AMOUNT"); 	
		}
	}
	strcpy((char *)amount,(const char*)givenpin);
	sprintf((char*)buffer,"#WTHD:%s$",amount);
	//Sending the withdrwal message to Uart0
	send_buf_to_uart0(buffer);
	//Receving the message from UART0
	recv_buf_from_uart0(buffer,sizeof(buffer));
	CmdLCD(GOTO_LINE1_POS0);	
	delay_ms(100);
	//checking if payement is success
	if(str_ncmp(buffer,(s8*)"@BAL:",5)==0)
	{	
		//if Withdrwal success
		//Displaying the message on LCD
		strcpy((char*)bal,(const char*)buffer+5);
		bal[str_len(bal)-1]='\0';
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);	
		StrLCD((s8 *)"WITHDRAW SUCCESS");
		CmdLCD(GOTO_LINE2_POS0);	
		StrLCD(amount);
		delay_s(2);
	}
	//if payement is failed 
	else if(str_cmp(buffer,(s8*)"@ERR$")==0)
	{
		//Displaying message on LCD
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD((s8*)"ERROR !");
		CmdLCD(GOTO_LINE2_POS0);	
		StrLCD((s8 *)"LESS FUNDS !!!");
		delay_s(2);
	}
	return 0;
}
//Function for pin change
u32 Pin_Change()
{
	s8 *oldpassword,newpassword[5],buffer[20];//buffer for pin change
	u8 c;
	u32 cont=0;
	//message on LCD to enter OLD PIN
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD((s8 *)"ENTER OLD PIN");
	//Read PIN From the KEYPAD
	oldpassword=Read_PIN(1);
	//Check if TIME OUT
	if(oldpassword==NULL)
	{
		//Showing message on LCD TIME OUT
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD((s8*)"SESSION TIMED OUT ! ");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("PLEASE TRY AGAIN ");
		delay_s(1);
		CmdLCD(CLEAR_LCD);
		//Sending the message to the UART0 TIME OUT
		send_buf_to_uart0((s8*)"#TIMEOUT$");
		return 1;
	}
	CmdLCD(CLEAR_LCD);
	//incrementing the attempets count
	attempts++;
	//Checking the OLD PIN &Enetred PIN matched or not
	if(str_cmp(pin,oldpassword)==0)
	{
		delay_ms(5);
		while(1)
		{
			//inrement the pin change count
			pinchange++;
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8 *)"ENTER NEW PIN");	
			//Read the PIN from the KEYPAD
			oldpassword=Read_PIN(1);
			///Check if TIME OUT
			if(oldpassword==NULL)
			{	
				//Showing message on LCD TIME OUT
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD((s8*)"SESSION TIMED OUT ! ");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("PLEASE TRY AGAIN ");
				delay_s(1);
				CmdLCD(CLEAR_LCD);
				//Sending the message to the UART0 TIME OUT
				send_buf_to_uart0((s8*)"#TIMEOUT$");
				return 1;
			}
			//copying the given PIN into buffer
			strcpy((char*)newpassword,(const char*)oldpassword);
			delay_ms(50);
			//showing the message to re enter the message
			CmdLCD(CLEAR_LCD);	
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8 *)"RE ENTER NEW PIN");	
			//Reading the PIN from KEYPAD
			oldpassword=Read_PIN(1);
			//checling the TIME out condition
			if(oldpassword==NULL)
			{	
				//diplaying the TIMe out Message
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD((s8*)"SESSION TIMED OUT ! ");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("PLEASE TRY AGAIN ");
				delay_s(1);
				CmdLCD(CLEAR_LCD);
				//sending the TIME OUT mseeage to UART0
				send_buf_to_uart0((s8*)"#TIMEOUT$");
				return 1;
			}
			CmdLCD(CLEAR_LCD);
			delay_ms(50);
			//comparing the Entered PIN and ReEntered PIN
			if(str_cmp(oldpassword,newpassword)==0)
			{
				//Copying the Entered Pin if it is correct
				strcpy((char *)pin,(const char *)oldpassword);
				sprintf((char*)buffer,"#PINCHG:%s$",pin);
				//Sending the NEW PIN to the PC through UAR0
				send_buf_to_uart0(buffer);
				//Receving the buffer from the UART0
				recv_buf_from_uart0(buffer,sizeof(buffer));
				//Checking the Recevied buffer is PIN CHANGD or not
				if(str_cmp(buffer,(s8*)"@CGD$")==0)
				{	
					//Showing the message on LCD PIN changed				
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD((s8 *)"SUCCEFULLY UPDATED");
					delay_s(2);
					CmdLCD(CLEAR_LCD);
					//assigning the values to ZERO
					pinchange=0;
					attempts=0;
					return 0;
				}
			}
			else
			{
				//if Reentered pin is not matched
				IOSET0=1<<LED;
				CmdLCD(GOTO_LINE1_POS0);
				StrLCD((s8 *)"WRONG NEW PIN!");
				delay_s(2);
				IOCLR0=1<<LED;
				//FOR NEW PIN WROGN ENETRY 3 TIMES TO Block the CARD
				if(pinchange>=3)
				{		
					//Sending the BLOCK meassage to the UART0
					send_buf_to_uart0((s8*)"#BLK$");
					//Receving the buffer from the UART0
					recv_buf_from_uart0(buffer,sizeof(buffer));
					//comparing the recevied message CARD is blocked or not
					if(str_cmp(buffer,(s8*)"@BLK$")==0)
					{
						//Displaying the message 
						IOSET0=1<<LED;
						CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE2_POS0);
						StrLCD((s8 *)"CARD BLOCKED !");
						delay_s(2);
						StrLCD((s8 *)"                ");
						IOCLR0=1<<LED;
						return 1;
					}
				}
				//user has to seklect the option has to reentre the pin or exit from pin change function
				while(1)
				{
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD((s8 *)"1:TRY AGAIN PIN CHG");
					CmdLCD(GOTO_LINE2_POS0);						
					StrLCD((s8 *)"2:EXIT");
					//Reading from the KEYPAD
					c=Read_key();
					while((ColScan()&1)==0);
					CmdLCD(CLEAR_LCD);
					//Checking for the TIMEOUT
					if(c==TIMEOUT_FLAG)
					{	
						//Displaying the message TIMEOUT
						CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE1_POS0);
						StrLCD((s8*)"SESSION TIMED OUT ! ");
						CmdLCD(GOTO_LINE2_POS0);
						StrLCD("PLEASE TRY AGAIN ");
						delay_s(1);
						CmdLCD(CLEAR_LCD);
						send_buf_to_uart0((s8*)"#TIMEOUT$");
						return 1;
					}
					//This condition for again Entering the pin
					if(c=='1')
					{
						cont=1;
						break;
					}
					//This conditioin for exit the pin change function
					else if(c=='2')
					{
						//Showing the message EXIT from the pin change function
						CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE2_POS0);						
						StrLCD((s8 *)"EXIT PIN CHANGE");
						delay_s(2);
						StrLCD((s8 *)"                ");
						break;
					}
					else
					{
						//Showing the if invalid number is entered
						CmdLCD(CLEAR_LCD);
						CmdLCD(GOTO_LINE2_POS0);
						StrLCD((s8 *)"INVALID ENTRY");
						delay_s(2);
						StrLCD((s8 *)"                ");
					}
				}
				//continue to re enter the pin
				if(cont)
				{
					continue;
				}
				//return from the function if given exit from the function
				else
				{
					return 0;
				}
			}
		}	
	}					
	else
	{
		//Showing that given old pin is wrong
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD((s8 *)"WRONG OLD PIN!");
		delay_s(2);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD((s8 *)"                ");
	}
	//FOR 3 ATTEMPTS OVERED
	if(attempts>=3)
	{
		//Sending to block the card
		send_buf_to_uart0((s8 *)"#BLK$");
		//Receving the buffer from the UART0
		recv_buf_from_uart0(buffer,sizeof(buffer));		
		//Checking if CARD is Blocked or not
		if(str_cmp(buffer,(s8*)"@BLK$")==0)
		{
			//Displaying message on LCD
			CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8 *)"CARD BLOCKED !");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD((s8 *)"CONTACT MAIN BRCH");
			delay_s(2);
			return 1;
		}
	}
	return 0;
}
//Function for MiniStatement
void Mini_Statement()
{
    s8 buffer[100], *ptr;
    s8 transaction[30];  // Buffer for individual transaction
    send_buf_to_uart0((s8*)"#MINI#REQ$");
    recv_buf_from_uart0(buffer, sizeof(buffer));

    if (str_ncmp(buffer, (s8*)"@OK#STMT:", 9) == 0)
    {   	     
        strcpy((char*)buffer, (const char*)buffer + 9);  // Remove prefix "@OK#STMT:"
        buffer[str_len(buffer) - 1] = '\0';  // Remove trailing '$'        

        // **Process transactions one by one**
        ptr=(s8*)strtok((char*)buffer, "|");  // Split transactions using '|'
        while (ptr != NULL)
        {
            strcpy((char *)transaction,(const char*)ptr);  // Copy individual transaction
            
            CmdLCD(CLEAR_LCD);
			CmdLCD(GOTO_LINE1_POS0);
			StrLCD((s8*)"TRSNC HISTORY");
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD(transaction);  // Display transaction

            delay_s(2);  // Wait 2 seconds before showing next transaction

            ptr=(s8*)strtok(NULL,"|");  // Get the next transaction
        }
    }
}
