#include "header.h"// Include necessary header file
// Function to display transaction history of a specific account
void History(void)
{
	SLL *temp;// Pointer to traverse the linked list
	int i;// Iterator variable
	long int num;// Variable to store account number or Aadhar number
	temp=Account_Details;// Initialize traversal pointer
	if(temp==NULL)// Check if no accounts exist
	{
		printf("no account is created up to now\n");// Notify user
	}
	else
	{
		printf("enter account number/Aadhar number:");// Prompt user for input
		scanf("%ld",&num);// Read account/Aadhar number
		// Traverse linked list to find matching account
		while(temp)
		{
			if((temp->Account_Number==num)||(temp->Aadhar_Number==num))
			{
				break;// Exit loop if match is found
			}
			temp=temp->next;// Move to the next node
		}
		if(temp==NULL)// If no matching account found
		{
			printf("no account found on this number\n\n");// Notify user
		}
		else// If account exists, display transaction history
		{
			printf("\n");
			printf("No.of    Type of Trasnctions       D/M/Y    TIME Account Number      Amount\n");
			if(temp->flag1)// If transaction history limit has been exceeded
			{
				for(i=0;i<5;i++)// Display last 5 transactions
				{
				printf("%d \t%s\t\t\t%d/%d/%d    %d:%d  %d\t\t%.3f",
				i+1,temp->history[i].type,temp->history[i].day,temp->history[i].month,temp->history[i].year,temp->history[i].hour,temp->history[i].min,temp->history[i].Acc_Num,temp->history[i].amount);
					printf("\n");	
				}
			}
			else//Display all recorded transactions
			{
				for(i=0;i<temp->number;i++)
				{
				printf("%d \t%s\t\t\t%d/%d/%d    %d:%d  %d\t\t%.3f",
				i+1,temp->history[i].type,temp->history[i].day,temp->history[i].month,temp->history[i].year,temp->history[i].hour,temp->history[i].min,temp->history[i].Acc_Num,temp->history[i].amount);
					printf("\n");	
				}

			}
		}
		printf("\n");
	}
}
