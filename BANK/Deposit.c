#include "header.h"// Include the necessary header file
// Function to handle deposit transactions
void Deposit(void)
{
	SLL *temp;// Pointer to traverse the linked list
	int i,max=23578432,min=22548765;// Variables for generating transaction ID
	size_t now;// Variable to store the current time
	struct tm *current_time;// Structure to store the local time
	double amount;// Variable to store deposit amount
	long int acc_num;// Variable to store account number or Aadhar number
	time(&now);// Get the current time
	current_time=localtime(&now);// Convert to local time structure
	printf("Enter account number/Aadhar Number:");// Prompt user for account/Aadhar number
	__fpurge(stdin);// Clear input buffer
	scanf("%ld",&acc_num);// Convert to local time structure
	temp=Account_Details;// Initialize traversal pointer
	// Traverse linked list to find matching account
	while(temp)
	{
		if((temp->Account_Number==acc_num)||(temp->Aadhar_Number==acc_num))
		{
			break;// Exit loop if match is found
		}
		temp=temp->next;// Move to the next node
	}
	if(temp==NULL)// If no matching account found
	{
		printf("Invalid account number !\n");// Notify user
	}
	else// If account exists
	{
		if(count(acc_num))// Check if OTP authentication is required
		{
Otp:printf("Enter OTP sent to your phone number:");// Prompt for OTP
			scanf("%d",&i);// Read OTP from user
			if(i<0)
			{
				printf("Invalid OTP!\n");// Notify user
				goto Otp;// Retry OTP input
			}
		}
		amount=Read_Bal(0);// Read deposit amount from user
		temp->Trasnction_Count++;// Increment transaction count
		temp->Account_Balance=(temp->Account_Balance+amount);// Update account balance
		printf("DEPSOIT SUCCESSFUL\n"); // Notify user
		if(temp->number>=5)// If transaction history exceeds limit
		{
			temp->number=0;// Reset transaction index
			temp->flag1=1;// Set flag indicating transaction history shift
		}
		// Shift old transaction history entries
		memmove(&temp->history[1],&temp->history[0],4*sizeof(Trsnc));
		// Store the new transaction details
		strcpy(temp->history[0].type,"DEPOSIT");
		temp->history[0].amount=amount;
		temp->history[0].Acc_Num=temp->Account_Number;
		temp->history[0].year=current_time->tm_year+1900;
		temp->history[0].month=current_time->tm_mon+1;
		temp->history[0].day=current_time->tm_mday;
		temp->history[0].hour=current_time->tm_hour;
		temp->history[0].min=current_time->tm_min;
		// Generate a unique transaction ID
		temp->history[0].trsncid=(rand()%(max-min+1))+min;
		temp->number++; // Increment transaction count index
	}
}
