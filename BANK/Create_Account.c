#include "header.h"// Include necessary header file
// Function to insert a node in a sorted manner based on Name field
void SortList(SLL *node)
{
	// If the list is empty or the new node's name comes before the first node's name
	if(Account_Details==NULL||strcmp(node->Name,Account_Details->Name)<0)
	{
		node->next=Account_Details;// Insert node at the beginning
		Account_Details=node;// Update head pointer
		return;
	}
	SLL *current=Account_Details; // Pointer to traverse the list
	// Traverse until correct position is found
	while(current->next!=NULL&& strcmp(current->next->Name,node->Name)<0)
	{
		current=current->next;
	}
	node->next=current->next;// Insert node in sorted order
	current->next=node;
}
// Function to generate a random 5-digit account number
int AccountNumber(void)
{
	int i,j;
	int acc_num;// Initialize account number
	acc_num=0;
	for(i=0;i<5;i++)
	{
		j=rand()%10;// Generate a random digit
		acc_num=(acc_num*10)+j;// Append the digit to the account number
	}
	return acc_num;// Return generated account number
}
// Function to read and validate account holder's name
char* Read_Name(void) 
{
	    static char Name[50];// Buffer to store name
	    int i, flag, hasAlpha;
	    __fpurge(stdin);// Clear input buffer
		    while (1) 
		    {
		  	    printf("Enter Account Holder Name: ");
		            fgets(Name, sizeof(Name), stdin);
			    Name[strcspn(Name, "\n")] = '\0';// Remove newline character
			    if (strlen(Name) == 0) // Ensure name is not empty
			    {
				    printf("Invalid Name! Please enter again.\n");
				    continue;
			    }
			    i = 0;
			     // Remove leading spaces
			    while (Name[i] == ' ') 
			    {
				    i++;
			    }
			    // If only spaces were entered
			    if (Name[i] == '\0') 
			    {
				    printf("Invalid Name! Please enter again.\n");
				    continue;
			    }
			    // Shift characters left
			    memmove(Name, Name + i, strlen(Name) - i + 1);
			    hasAlpha = 0;
			    for (i = 0; Name[i] != '\0'; i++) 
			    {
				    // Ensure only alphabets and spaces
				    if (!isalpha(Name[i]) && Name[i] != ' ') 
				    {
					    printf("Invalid Name! Please enter again.\n");
	    				    hasAlpha = -1;
					    break;
				    }
				    if (isalpha(Name[i])) 
				    {
					    hasAlpha = 1;
				    }
			    }
			    if (hasAlpha <= 0) 
			    {
				    continue;
			    }
			    // Capitalize first letter of each word
			    flag = 1;
			    for (i = 0; Name[i] != '\0'; i++) 
			    {
				    if (isalpha(Name[i]) && flag) 
				    {
					    Name[i] = toupper(Name[i]);
					    flag = 0;
				    } 
				    else if (Name[i] == ' ') 
				    {
					    flag = 1;
				    }
			    }
			    return Name;// Return validated name
		    }
}
// Function to read and validate PIN (4-digit numeric value)
char* Read_PIN(void)
{
	static char pin[5];// Buffer to store PIN
	while(1)
	{
		printf("ENTER PIN:");
		__fpurge(stdin);
		scanf("%s",pin);
		if(Compare_int(pin))// Ensure only numeric input
		{
			printf("ENTER NUMERIC CHARACTERS ONLY\n");
			continue;
		}
		else if(strlen(pin)!=4) // Ensure PIN is exactly 4 digits
		{
			printf("ENTER 4 DIGIT PIN\n");
			continue;
		}
		else
		{
			return pin;
		}
	}
}
// Function to read a valid 8-digit numeric RFID from user input
char* Read_RFID(void)
{
	static char rfid[10];// Static buffer to hold RFID string (8 digits + '\0')
	while(1)
	{
		printf("ENTER 8 DIGIT RFID:");
		__fpurge(stdin);// Clear input buffer (glibc-specific, non-standard)
		scanf("%s",rfid);// Read input into rfid buffer
		if(Compare_RFID(rfid))// Check if RFID already exists
		{
			printf("RFID IS ALREADY EXISTED\n");
			continue;// Prompt again
		}
		else if(Compare_int(rfid))// Validate if input contains only digits
		{
			printf("ENTER NUMERIC CHARACTERS ONLY\n");
			continue;// Prompt again
		}
		else if(strlen(rfid)!=8)// Ensure length is exactly 8
		{
			printf("RFID MUST & SHOULD CONTAIN 8 DIGITS !\n");
			continue;// Prompt again
		}
		else
		{
			return rfid;// Valid RFID, return pointer
		}
	}
}
// Function to read a valid 12-digit Aadhar number from user input
long int Read_Aadhar(void)
{
	long int Aadhar_Number,j;// Variable to store Aadhar and its copy for digit counting
	int i;// Counter for number of digits
	char ch;// Used to flush invalid input characters
	while(1)// Loop until a valid Aadhar number is entered
	{
		printf("ENTER 12 DIGIT AADHAR NUMBER:");
		__fpurge(stdin);// Clear input buffer (non-standard, works in Linux with glibc)
		if(scanf("%ld",&Aadhar_Number)!=1)// Check if input is a valid long integer
		{
			printf("ENTER NUMERIC CHARACTERS ONLY\n");
			// Flush remaining invalid characters from the input buffer
			while((ch = getchar()) != '\n' && ch != EOF);
			continue;// Retry input
		}
		j=Aadhar_Number;
		i=0;
		// Count number of digits in the entered Aadhar number
		while(j>0)
		{
			j/=10;
			i++;
		}
		// Aadhar number must be exactly 12 digits
		if((i>12)||(i<12))
		{
			printf("INVALID AADHAR NUMBER!\n");
		}
		else if(Compare_Aadhar(Aadhar_Number))// Check if Aadhar already exists
		{
			printf("ACCOUNT DETECTED WITH THIS AADHAR NUMBER\n");
		}
		else
		{
	
			return Aadhar_Number;// Valid, unique 12-digit Aadhar number
		}
	}
}
// Function to read a valid 10-digit mobile contact number from user input
long int Read_Contact(void)
{
	long int j,Contact_Number;// Variables for storing contact number and its copy for digit counting
	int i;// Digit count
	char ch;// Temporary variable for input flushing
	// Infinite loop until a valid contact number is entered
	while(1)
	{
		printf("ENTER 10 DIGIT CONTACT NUMBER:");
		__fpurge(stdin);// Flush any leftover input from stdin (works with GCC/glibc)
		   // Try reading the contact number as a long integer
		if(scanf("%ld",&Contact_Number)!=1)
		{
			printf("YOU HAVE ENTERED NON NUMERIC CHARACTERS ONLY\n");
			// Flush remaining characters to prevent infinite loop
			while((ch = getchar()) != '\n' && ch != EOF);
			// Retry input
			continue;
		}
		j=Contact_Number;// Copy contact number to count digits
		i=0;
		// Count how many digits are in the number
		while(j)
		{
			j/=10;
			i++;
		}
		// Check for digit count validity
		if((i>10))
		{
			printf("INVALID CONTACT NUMBER!\n");
			printf("YOU HAVE ENTERED MORE THAN 10 NUMERICS\n");
			continue;
		}
		else if(i<10)
		{
			printf("INVALID CONTACT NUMBER!\n");
			printf("YOU HAVE ENTERED LESS THAN 10 NUMERICS\n");
			continue;
		}
		// Check for valid Indian mobile number range (generally starts from 6 to 9)
		else if((Contact_Number<6000000000)||(Contact_Number>9999999999))
		{
			printf("ENTER VALID CONTACT NUMBER\n");
			continue;
		}
		else
		{
			return Contact_Number;// Valid number
		}
	}

}
// Function to read a valid balance amount from user
// // Parameter `min` is used to enforce a minimum balance rule (e.g., during account creation)
double Read_Bal(int min)
{
	double Account_Balance;// Variable to store the entered balance
	char ch;// Temporary variable for flushing unwanted input
	while(1)// Loop until valid input is received
	{
		printf("ENTER AMOUNT:");// Prompt user
		__fpurge(stdin);// Clear input buffer (GCC/glibc specific)
		// Read a double value and validate input
		if(scanf("%lf",&Account_Balance)!=1)
		{
			printf("ENTER NUMERIC CHARACTERS ONLY\n");
			// Flush any remaining characters in the input buffer
			while((ch = getchar()) != '\n' && ch != EOF);
			continue;
		}
		 // If minimum balance rule is enforced (min != 0) and balance is less than 500
		if((Account_Balance<500)&&min)
		{
			printf("MINIMUN BALANCE SHOULD BE 500\- \n");
			continue;
		}
		 // Ensure the amount is meaningful (at least 10) and not too small
		else if(Account_Balance<10)
		{
			printf("AMOUNT SHOULD BE IN MULTIPLES OF 10'S,100'S etc...\n");
			continue;
		}
		 // If all checks pass, return the valid balance
		else
		{
			return Account_Balance;
		}
	}
}
// Function to create a new bank account
void Create_Account(void)
{
	size_t now;
	struct tm *current_time;
	char c;
	int i,flag=1,max,min;
	long int j;
	time(&now);// Get current time
	current_time=localtime(&now);// Convert to local time
	SLL *New_Account=NULL;
	
	New_Account=calloc(1,sizeof(SLL));// Allocate memory for new account
	// Read and store account details
	New_Account->number=0;
	New_Account->flag1=0;
	New_Account->flag2=0;
	New_Account->block=0;
	strcpy(New_Account->Name,Read_Name());
	
	strcpy(New_Account->RFID,Read_RFID());

	strcpy(New_Account->pin,Read_PIN());
	
	New_Account->Account_Number=AccountNumber();
	
	New_Account->Contact_Number=Read_Contact();

	New_Account->Aadhar_Number=Read_Aadhar();
	
	New_Account->Account_Balance=Read_Bal(1);

	New_Account->Trasnction_Count=1;
	// Store transaction history
	strcpy(New_Account->history[New_Account->number].type,"DEPOSIT");
	New_Account->history[New_Account->number].amount=New_Account->Account_Balance;
	New_Account->history[New_Account->number].Acc_Num=New_Account->Account_Number;
	New_Account->history[New_Account->number].year=current_time->tm_year+1900;
	New_Account->history[New_Account->number].month=current_time->tm_mon+1;
	New_Account->history[New_Account->number].day=current_time->tm_mday;
	New_Account->history[New_Account->number].hour=current_time->tm_hour;
	New_Account->history[New_Account->number].min=current_time->tm_min;
	New_Account->next=0;
	// Generate unique transaction ID
	max=23782548;min=24748728;
	New_Account->history[New_Account->number].trsncid=(rand()%(max-min+1))+min;
	New_Account->number++;
	// Insert account into the list
	if(Account_Details==NULL)
	{
		New_Account->next=0;
		Account_Details=New_Account;
	}
	else
	{
		New_Account->next=Account_Details;
		Account_Details=New_Account;
	}
}
