#include "header.h"// Include the required header file
// Function to perform balance inquiry
void Balance_Enquery(void)
{
	SLL *temp;// Temporary pointer to traverse the account list
	long int acc_num;// Variable to store account number or Aadhar number
	int i;// Variable for OTP input
	temp=Account_Details;// Initialize temp with the account details list
	if(temp==NULL)// Check if no accounts exist
	{
		printf("no Account created upto now\n");// Notify the user
	}
	printf("Enter Account Number/Aadhar Number:");// Prompt user for account/Aadhar number
	__fpurge(stdin);// Clear the input buffer
	scanf("%ld",&acc_num);// Read the account number
	// Traverse the linked list to find the matching account
	while(temp)
	{
		if((temp->Account_Number==acc_num)||(temp->Aadhar_Number==acc_num))
		{
			break;// Exit loop when match is found
		}
		temp=temp->next;// Move to the next node
	}
	if(temp==NULL)// If account is not found
	{
		printf("Invalid Account Number!\n");// Notify the user
	}
	else// If account exists
	{
		if(count(acc_num))// Check if OTP authentication is required
		{
otp:printf("Enter OTP sent to your phone number:");// Prompt for OTP
			scanf("%d",&i);// Read OTP from user
			if(i<0)// Validate OTP input
			{
				printf("Invalid OTP!\n");// Notify user
				goto otp;// Retry OTP input
			}
		}
		printf("Amount is:%.3lf\n",temp->Account_Balance);// Display account balance
	}
}
