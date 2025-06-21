#include "header.h"// Include necessary header file
// Function to display the bank menu options
void Print_Menu(void)
{
	printf("        !__________________________BANK MENU__________________________!\n");
	printf(	"\t-->c/C---Create Account\t\t\t"// Create a new account
		"Mini Statement---h/H<--\n"// View transaction history
		"\t-->w/W-------Withdrawal\t\t\t"// Withdraw money
		"Deposit----------d/D<--\n"// Deposit money
		"\t-->b/B--Balance Enquiry\t\t\t"// Check account balance
		"Transfer---------t/T<--\n"// Transfer money
		"\t-->e/E----Show Accounts\t\t\t"// Display all accounts
		"Save To File-----s/S<--\n"// Save data to file
		"\t-->f/F-----Find Account\t\t\t"// Find a specific account
		"Update Account---u/U<--\n"// Update account details
		"\t-->l/L-----Change Status\t\t"// Change account status (block/unblock)
		"Exit-------------q/Q<--\n");// Exit the program
	
	printf("Select A Option->");// Prompt user to select an action
}
