#include"header.h"// Include necessary header file
// Function to extract a floating-point number from a given string
double extract_dou(char *buf)
{
	int end,start;
	char out[10];// Buffer to store extracted number
	end=strlen(buf)-1;// Set end index to last character
	 // Move back until a digit is found
	while(end>=0&&!(buf[end]>=48&&buf[end]<=57))
		end--;
	// If no digits found, return 0
	if(end<0)
	{
		return 0;
	}
	start=end;// Initialize start position
	// Move back until reaching a non-digit character
	while(start>=0&&((buf[start]>=48)&&(buf[start]<=57)))
			start--;
	// Copy extracted number
	strncpy(out,buf+start+1,end-start);
	out[end-start]='\0';// Null-terminate string
	return atof(out);// Convert extracted string to floating-point number
}
// Convert extracted string to floating-point number
char * extract_int(char *buf)
{
	int end,start;
	static char out[10];// Buffer to store extracted number
	end=strlen(buf)-1;// Set end index to last character
	// Move back until a digit is found
	while(end>=0&&!(buf[end]>=48&&buf[end]<=57))
		end--;
	 // If no digits found, return NULL
	if(end<0)
	{
		return 0;
	}
	start=end;// Initialize start position
	// Move back until reaching a non-digit character
	while(start>=0&&((buf[start]>=48)&&(buf[start]<=57)))
			start--;
	// Copy extracted numbe
	strncpy(out,buf+start+1,end-start);
	out[end-start]='\0';// Null-terminate string
	return out;// Return extracted number
}
// Function to verify the user's PIN
void Verify_PIN(char *buff,int fd)
{
	SLL *temp=rfid;// Pointer to stored RFID account details
	char buf[20]; // Buffer to store extracted PIN
	printf("in verify pin");
	printf("%s\n",buff);
	strcpy(buf,extract_int(buff));// Extract integer PIN from input
	printf("after extraction\n");
	printf("%s\n",buf);
	printf("%s\n",pin);
	// Compare extracted PIN with stored PIN
	if(strcmp(pin,buf)!=0)
	{
		printf("INVLAID PIN\n");
#ifdef DEBUG
		write(1,"@ERR#INVLD$",sizeof("@ERR#INVLD$"));
#else
		write(fd,"@ERR#INVLD$",sizeof("@ERR#INVLD$"));
#endif
	}
	else
	{
#ifdef DEBUG
		write(1,"@OK$",sizeof("@OK$"));
#else
		puts("in @ok$ sending");
		write(fd,"@OK$",sizeof("@OK$"));
#endif
		
	}
	
}

// Function to process balance inquiry request
void BAL_ENQ(int fd)		
{
	char sendbuff[100]={0},floatbuff[20]={0};
	SLL *temp=rfid;// Pointer to stored RFID account details
			
				puts("BALANCE REQ");
				sprintf(floatbuff,"%.1lf",temp->Account_Balance); // Convert balance to string
				strcpy(sendbuff,"@BAL:");// Prefix response
				strcat(sendbuff,floatbuff);// Append balance amount
				strcat(sendbuff,"$");// Append termination character
				printf("balance:%s\n",sendbuff);
#ifdef DEBUG
				write(1,sendbuff,strlen(sendbuff));
#else
				write(fd,sendbuff,strlen(sendbuff));
#endif
			
}
// Function to process deposit request
void DEP_BAL(char *buf,int fd)
{
	char sendbuff[100],floatbuff[30];	
	SLL *temp=rfid;// Pointer to stored RFID account details
	puts("IN DEPOSIT");
	size_t now;
	struct tm *current_time;
	int i,max=27835438,min=26857429;
	double amount;
	time(&now);
        current_time=localtime(&now);
				amount=extract_dou(buf);// Extract deposit amount from input
				printf("%lf\n",amount);
				temp->Account_Balance=(temp->Account_Balance+amount);// Add deposit amount to account balance
				sprintf(floatbuff,"%.1lf",temp->Account_Balance);// Convert updated balance to string
				strcpy(sendbuff,"@BAL:");// Prefix response
				strcat(sendbuff,floatbuff);// Append updated balance
				strcat(sendbuff,"$");// Append termination character
				if(temp->number>=5)
                		{
                        		temp->number=0;
                        		temp->flag1=1;
                		}
                		memmove(&temp->history[1],&temp->history[0],4*sizeof(Trsnc));
				strcpy(temp->history[0].type,"DEPOSIT");
				temp->history[0].amount=amount;
				temp->history[0].Acc_Num=temp->Account_Number;
				temp->history[0].year=current_time->tm_year+1900;
				temp->history[0].month=current_time->tm_mon+1;
				temp->history[0].day=current_time->tm_mday;
				temp->history[0].hour=current_time->tm_hour;
				temp->history[0].min=current_time->tm_min;
				temp->history[0].trsncid=(rand()%(max-min+1))+min;
                		temp->number++;
				temp->Trasnction_Count++;
				Save_To_File(); // Save transaction details
#ifdef DEBUG
				write(1,sendbuff,strlen(sendbuff));
#else
				write(fd,sendbuff,strlen(sendbuff));
#endif
}
// Function to handle withdrawal transaction
void WITH_BAL(char *buf,int fd)
{
	char sendbuff[100],floatbuff[30];
	SLL *temp=rfid;// Pointer to currently authenticated user's node
	size_t now;
	struct tm *current_time;
	int i,max=27835438,min=26857429;
	double amount;
	time(&now);
        current_time=localtime(&now);
	printf("WITHDRAW\n");
	// Extract amount from the request buffer (e.g., from "#TXN:WITHDRAW#100$")
	amount=extract_dou(buf);
	printf("%f\n",amount);
	    // Check if sufficient balance is available
				if(amount>temp->Account_Balance)
				{
					// If insufficient balance, send an error frame
					printf("INSUFFICIENT BALANCE\n");
#ifdef DEBUG
					write(1,"@ERR$",strlen("@ERR$"));// Write to stdout in debug mode
#else
					write(fd,"@ERR$",strlen("@ERR$"));// Write to UART or socket
#endif
				}
				else
				{
					// Proceed with withdrawal
					printf("SUCCESS WITHDRAW\n");
					// Deduct amount from balance
					temp->Account_Balance=(temp->Account_Balance-amount);
					strcpy(sendbuff,"@BAL:");
					sprintf(floatbuff,"%.1lf",temp->Account_Balance);// Convert balance to string
					strcat(sendbuff,floatbuff);
					strcat(sendbuff,"$");
					// If transaction history is full, reset index and set overwrite flag
					if(temp->number>=5)
                        		{
                		                temp->number=0;
					      	temp->flag1=1;
                        		}
                       	 		
   			                // Shift history entries to make space for new entry at index 0
                        		memmove(&temp->history[1],&temp->history[0],4*sizeof(Trsnc));
					// Log the transaction in history[0]
                 		       	strcpy(temp->history[0].type,"WITHDRAW");
                     			temp->history[0].amount=amount;
                        		temp->history[0].Acc_Num=temp->Account_Number;
                        		temp->number++;
                        		temp->history[0].year=current_time->tm_year+1900;
                    		    	temp->history[0].month=current_time->tm_mon+1;
                        		temp->history[0].day=current_time->tm_mday;
                        		temp->history[0].hour=current_time->tm_hour;
                        		temp->history[0].min=current_time->tm_min;
					// Generate a unique transaction ID in the specified range
                        		temp->history[0].trsncid=(rand()%(max-min+1))+min;
					temp->Trasnction_Count++;
					// Save the updated account and transaction info to a file
					Save_To_File();
#ifdef DEBUG
					write(1,sendbuff,strlen(sendbuff));// Send to stdout for debugging
#else
					write(fd,sendbuff,strlen(sendbuff));// Send to connected device (e.g., GSM/UART)
#endif
				}
}
//fumction to change pin
void PIN_CHANG(char *buf,int fd)
{
	SLL *temp=rfid;// Get the current user's account record from the global linked list
				printf("PINCHANGE NEWPIN\n");
				// Extract the new PIN from the buffer and update it in the user structure
				strcpy(temp->pin,extract_int(buf));
				// Optionally update a global variable 'pin' with the new PIN
				strcpy(pin,temp->pin);
				// Save the updated information (with new PIN) to the file
				Save_To_File();
#ifdef DEBUG
				write(1,"@CGD$",strlen("@CGD$"));// In debug mode, write to standard output
#else
				write(fd,"@CGD$",strlen("@CGD$"));// Send to connected device (e.g., GSM/UART)
#endif
}
//function to Block card
void BLK_CARD(int fd)
{
	// Get the current user's account record from the global linked list
	SLL *temp=rfid;
				printf("PIN CHANGE BLOCK\n");
				// Set the block flag to 1 (indicating the card/account is blocked)
				temp->block=1;
				 // Save the updated account information (including blocked status) to persistent storage
				Save_To_File();
#ifdef DEBUG
				write(1,"@BLK$",strlen("@BLK$"));// In debug mode, write to standard output
#else	
				write(fd,"@BLK$",strlen("@BLK$"));// Send to connected device (e.g., GSM/UART)
#endif
}
void MINI_STMT(int fd)
{
	char sendbuff[100],buf[20];
	int i,j;
	// Get the current user's account record from the global linked list
	SLL *temp=rfid;
				printf("IN MINISTMT\n");
				strcpy(sendbuff,"@OK#STMT:");
				j=temp->Trasnction_Count;
				//if Trasnction is greater than 3 sending 3 Trasnctions
				if(j>=3)
				{
					for(i=0;i<3;i++)
					{
						strcat(sendbuff,temp->history[i].type);
						sprintf(buf,"%.2lf",temp->history[i].amount);
						strcat(sendbuff,"-");
						strcat(sendbuff,buf);
						strcat(sendbuff,"|");
					}
				}
				else if(j==2)//if Trasnction count is 2 sending 2 Trasnctions
				{
					for(i=0;i<2;i++)
					{
						strcat(sendbuff,temp->history[i].type);
						sprintf(buf,"%.2lf",temp->history[i].amount);
						strcat(sendbuff,"-");
						strcat(sendbuff,buf);
						strcat(sendbuff,"|");
					}
				}
				else if(j==1)//if Trasnction count is 1 sending 1 Trasnction
				{
					for(i=0;i<1;i++)
					{
						strcat(sendbuff,temp->history[i].type);
						sprintf(buf,"%.2lf",temp->history[i].amount);
						strcat(sendbuff,"-");
						strcat(sendbuff,buf);
						strcat(sendbuff,"|");
					}
				}
				strcat(sendbuff,"$");//adding end charcter to buffer
#ifdef DEBUG
				write(1,sendbuff,strlen(sendbuff));// In debug mode, write to standard output
#else
				write(fd,sendbuff,strlen(sendbuff));// Send to connected device (e.g., GSM/UART)
#endif
}
