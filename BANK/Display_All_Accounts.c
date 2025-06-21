#include "header.h"// Include the necessary header file
// Function to display all registered accounts
void Display_All_Accounts(void)
{
	SLL *temp=Account_Details;// Pointer to traverse the linked list
	if(Account_Details==NULL)// Check if the list is empty
	{
		printf("list is empty\n");// Notify user
	}
	else
	{
		printf("\n");
		printf("       ACCOUNT MEMBERS LIST\n\n");// Print header
		while(temp)
		{
			printf("Name:              %s\n",temp->Name);
			printf("Contact Number:    +91 %ld\n",temp->Contact_Number);
			printf("Account Number:    %d\n",temp->Account_Number);
			printf("Aadhar Number:     %ld\n",temp->Aadhar_Number);
			printf("No.of Trasnctions: %d\n",temp->Trasnction_Count);
			printf("RFID:              %s\n",temp->RFID);
			printf("PIN:               %s\n",temp->pin);
			printf("\n");
			temp=temp->next;// Move to the next account in the list
		}
	}
}
