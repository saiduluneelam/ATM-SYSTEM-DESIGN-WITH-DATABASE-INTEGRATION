#include"header.h" // Include necessary header file
// Function to display the update menu for account details
void Update_Menu()
{
	printf("n/N:Update Name\n"
		"a/A:Update Aadhar number\n"
		"m/M:Update mobile number\n"
		"r/R:update RFID number\n"
		"p/P:Update PIN\n"
		"e/E:Exit\n");// Display options for account updates
	printf("enter your option:\n");// Prompt user for selection
}
// Function to update specific details of an account
void Update_Account()
{
	int account_num;// Variable to store account number
	char c;// Variable to store user choice
	SLL *node=Account_Details;// Pointer to traverse the linked list
	if(node==NULL)// Check if account list is empty
	{
		printf("no account details\n");// Notify user
	}
	else
	{
		printf("ENTER ACCOUNT NUMBER:");// Prompt user for account number
		scanf("%d",&account_num);// Read account number
		while(node!=NULL)// Traverse linked list to find matching account
		{
			if(account_num==node->Account_Number)
			{
				break;// Exit loop if match is found
			}
			node=node->next;// Move to next node
		}
		// If account exists, allow updates
		if(node!=NULL)
		{
			// Loop for multiple updates
			while(1)
			{			
				Update_Menu();// Display update menu
				__fpurge(stdin);// Clear input buffer
				scanf("%c",&c);// Read user choice
				switch(c)// Handle user selection
				{
					case 'a':
					case 'A':node->Aadhar_Number=Read_Aadhar();
						 printf("UPDATED AADHAR NUMBER SUCCESSFULLY\n");
						 break;
					case 'm':
					case 'M':node->Contact_Number=Read_Contact();
						 printf("UPDATED MOBILE NUMBER SUCCESSFULLY\n");
						 break;
					case 'r':
					case 'R':strcpy(node->RFID,Read_RFID());
						 printf("UPDATED RFID SUCCESSFULLY\n");
						 break;
					case 'p':
					case 'P':strcpy(node->pin,Read_PIN());
						 printf("UPDATED PIN SUCCESSFULLY\n");
						 break;
					case 'n':
					case 'N':strcpy(node->Name,Read_Name());
						 printf("UPDATED NAME SUCCESSFULLY\n");
						 break;
					case 'e':
					case 'E':printf("EXITED FROM UPDATION\n");
						 return ;// Exit update process
				}
			}

		}
		else
		{
			printf("NO ACCOUNT FOUND ON THIS NUMBER :%d\n",account_num);// Notify user// Notify user

		}
	}
}
