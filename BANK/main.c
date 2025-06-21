#include "header.h"// Include necessary header file
SLL* Account_Details=NULL;// Global variable to store account details
// Main function to run the banking system
int main()
{
	srand(time(NULL));// Seed the random number generator
	char choice;// Variable to store user menu selection
	Sync_From_File();// Load account details from file
	while(1)// Infinite loop to keep the program running
	{
		Print_Menu();// Display menu options
		__fpurge(stdin);// Clear input buffer
		scanf("%c",&choice);// Read user choice
		switch(choice)// Handle user selection
		{
			case'c':
			case'C':Create_Account();// Create a new account
				break;
			case'h':
			case'H':History();// Display transaction history
				break;
			case'w':
			case'W':Withdraw();// Perform withdrawal
				break;
			case'd':
			case'D':Deposit();// Process deposit
				break;
			case'b':
			case'B':Balance_Enquery();// Check balance
				break;
			case't':
			case'T':Transfer_Money();// Transfer money between accounts
				break;
			case'e':
			case'E':Display_All_Accounts();// Display all account details
				break;
			case's':
			case'S':Save_To_File();// Save account data to file
				break;
			case'f':
			case'F':Find_Specific_Account();// Find account by number or Aadhar
				break;
			case'l':
			case'L':Change_Stat();// Change account status (e.g., block/unblock)
				break;
			case'u':
			case'U':Update_Account();// Update account details
				break;
			case'q':
			case'Q':Save_To_File();// Save before quitting
				return 0;// Exit program
				break;
			default:printf("WRONG! ENTERY\n");// Handle invalid input
		}
	}
}
