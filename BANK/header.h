#ifndef __header_h
#define __header_h
// Include necessary standard library headers
#include<stdio.h>// Standard input/output functions
#include<stdlib.h>// Memory allocation, exit functions
#include<stdio_ext.h>// Extended stdio functions (GNU-specific)
#include<string.h>// String manipulation functions
#include<unistd.h>// System calls for process management
#include<time.h>// Time-related functions
#include<fcntl.h>// File control operations
#include<termios.h>// Terminal I/O configuration
#include<errno.h>// Error handling utilities
#include<stdint.h>// Standard integer types
#include<ctype.h>// Character type utilities

//#define DEBUG// Uncomment for debugging mode
#define MAX 5// Maximum transaction history entries
// Structure to store transaction details
typedef struct trsnc 
{
	char type[10];// Transaction type (e.g., "DEPOSIT", "WITHDRAW")
	double amount;// Transaction amount
	int Acc_Num;// Account number involved
	int month,day,year;// Date of transaction
	int hour,min;// Time of transaction
	int trsncid;// Unique transaction ID
}Trsnc;
// Structure to store account information
typedef struct Manager
{
	char Name[50];// Account holder's name
	int Account_Number;// Unique account number
	int flag1,flag2,block;// Status flags (block status)
	char pin[5];// Account PIN
	char RFID[9];// RFID identifier
	long int Contact_Number;// Contact number
	double Account_Balance;// Account balance
	int Trasnction_Count;// Number of transactions
	long int Aadhar_Number;// Aadhar number
	Trsnc history[5];// Transaction history
	int number;// Number of transactions recorded
	struct Manager *next;// Pointer to next account in list
}SLL;

//Global Variables
extern SLL *Account_Details;// Pointer to stored account 
extern SLL *Details;// Additional details pointer
extern char pin[10];// Global PIN storage
extern SLL* rfid;// RFID-linked list pointer

//function declarations
char* getstring(void);// Function to read a string dynamically
long int myatoi(char *);// Function to convert string to integer
int count(long int);// Function to count occurrences
// File handling functions
void Sync_From_File_H(void);// Sync data from header file
void Sync_From_File(void);// Sync data from main file
void Print_Menu(void);// Display menu options

// Account management functions
void Create_Account(void);// Function to create an account
void History(void);// Function to view transaction history
void Withdraw(void);// Function to process withdrawals
void Deposit(void);// Function to process deposits
void Balance_Enquery(void);// Function to check balance
void Transfer_Money(void);// Function to handle money 
void Display_All_Accounts(void);// Function to display all accounts
void Save_To_File(void);// Function to save data to file
void Save_To_File_H(void);// Function to save header file data
void Find_Specific_Account(void);// Function to find a specific account

//Comparison functions
int  Compare_Aadhar(long int); // Compare Aadhar numbers
int  Compare_RFID(char *);// Compare RFID identifiers
int  Compare_int(char *);// Validate numeric input
void SortList(SLL *);// Function to sort linked list
void Update_Account(void);// Function to update account details
void Update_Menu(void);// Function to update menu options

// Input handling functions
char* Read_Name(void);// Function to read and validate account holder's name
char* Read_PIN(void);// Function to read and validate PIN
char* Read_RFID(void);// Function to read RFID identifier
long int Read_Aadhar(void);// Function to read Aadhar number
long int Read_Contact(void);// Function to read contact number
double Read_Bal(int);// Function to read balance amount

//ARM functions
void Verify_PIN(char *,int);// Verify PIN for authentication
void Verify_RFID(char *,int);// Verify RFID authentication
double extract_dou(char* );// Extract floating-point number from input
char * extract_int(char* );// Extract integer from input
void read_str(int fd,char *str,int len);// Read data from UART device
void Change_Stat(void);// Change account status

//Banking transaction functions
void Verify_PIN(char *,int);//Function to verify PIN
void BAL_ENQ(int);// Balance inquiry function
void DEP_BAL(char *,int);// Deposit function
void WITH_BAL(char *,int);// Withdrawal function
void PIN_CHANG(char *,int);// PIN change function
void BLK_CARD(int);// Card blocking function
void MINI_STMT(int);// Mini statement function

#endif// End of header guard
