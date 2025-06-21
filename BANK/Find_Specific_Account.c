#include "header.h"// Include necessary header file
// Function to read a string dynamically from user input
char* getstring(void)
{
	int i=0;// Counter for characters
	char *p=NULL;// Pointer to dynamically allocated string
	__fpurge(stdin);// Clear input buffer
	do
	{
		p=realloc(p,(i+1)*sizeof(char));// Allocate memory for new character
		p[i]=getchar();// Read a character from input
	}while(p[i++]!='\n');// Repeat until newline character is encountered
	p[i-1]='\0';// Replace newline character with null terminator
	return p;// Return dynamically allocated string
}
// Function to convert numeric string to long integer
long int myatoi(char *name)
{
	int i;// Loop iterator
	long int num=0;// Initialize numeric value
	for(i=0;name[i]!='\0';i++)// Traverse the string
	{
		num=(num*10)+(name[i]-48);// Convert character to numeric value
	}
	return num;// Return converted integer
}
// Function to find and display specific account details
void Find_Specific_Account(void)
{
	SLL *temp;// Pointer to traverse linked list
	char *name;// Pointer to store user input
	long int acc_num;// Variable to store account/Aadhar number
	printf("Enter Account Number/Aadhar Number:");// Prompt user for input
	name=getstring();// Read user input
	temp=Account_Details;// Initialize traversal pointer
	// Check if input is numeric
	if((name[0]>='0')&&(name[0]<='9'))
	{
		acc_num=myatoi(name);// Convert input string to numeric value
		while(temp)
		{
			if((acc_num==temp->Account_Number)||(acc_num==temp->Aadhar_Number))
			{
				break;// Exit loop if match is found
			}
			temp=temp->next;// Move to the next node
		}
		if(temp==NULL)// If no matching account found
		{
			printf("Invalid account/Contact Number!\n");// Notify user
			
		}
		else// If account exists, display details
		{
			printf("name:%s\n",temp->Name);
			printf("Account Number:%d\n",temp->Account_Number);
			printf("Contact Number: +91 %ld\n",temp->Contact_Number);
			printf("Aadhar Number:%ld\n",temp->Aadhar_Number);
			printf("No.of Trasnctions:%d\n",temp->Trasnction_Count);
		}

	}
	else
	{

		printf("Account Details Should BE Displayed Only on Account/AAddhar Number\n");
	}
}
