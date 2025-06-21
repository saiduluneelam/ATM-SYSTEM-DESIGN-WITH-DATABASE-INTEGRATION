#include"header.h"// Include the necessary header file
// Function to compare an Aadhar number with stored account details
int Compare_Aadhar(long int aadhar)
{
	SLL *node;// Pointer for traversing the linked list
	node=Account_Details;// Start from the head of the linked list
	while(node!=NULL)// Traverse through the linked list
	{
		if(node->Aadhar_Number==aadhar)// Check if Aadhar number matche
		{
			return 1;// Return success if a match is found
		}
		node=node->next;// Move to the next node
	}
	return 0;// Return failure if no match is found
}
// Function to compare an RFID value with stored account details
int Compare_RFID(char *str)
{
        SLL *node;// Pointer for traversing the linked list
        node=Account_Details;// Start from the head of the linked list
        while(node!=NULL)// Traverse through the linked list
        {
                if(strcmp(node->RFID,str)==0)// Compare the RFID strings
                {
                        return 1;// Return success if a match is found
                }
                node=node->next;// Move to the next node
        }
        return 0;// Return failure if no match is found
}
// Function to check if a given string consists of only integer digits
int Compare_int(char *str)
{
	char c;// Character variable for checking each digit
	int i=0;// Iterator for traversing the string
        while(str[i]!='\0')// Loop until end of string
        {
		c=str[i++];// Get the current character
                if((c>=48)&&(c<=57))// Check if character is a digit (ASCII range for numbers)
                {
                       continue;// Continue checking next character
                }
		else
		{
			return 1;// Return failure if a non-digit is found
		}
        }
	return 0;// Return success if all characters are digits
}
// Function to read a string from a file descriptor
void read_str(int fd,char *str,int len)
{
	int i=0,j=0;// Loop counters
	char ch;// Character buffer for reading input
	// Loop to read characters until length limit
	for(i=0;i<len-1;i++)
	{
		j=read(fd,&ch,1);// Read one character from file descriptor
		printf("%c",ch);// Print the character
		if(j==-1)// If read operation failed
		{
			perror("read_str");// Print error message
			exit(0);// Exit the program
		}
		else if(j==0)// If no data was read
		{
			i--;// Adjust loop counter to retry
			continue;
		}
		str[i]=ch;// Store the character in the buffer
#ifdef DEBUG
		if(ch=='\n')// If newline character is received
		{
			str[i]='\0'; // Null-terminate the string
			break;
		}
		else if(ch=='\r')// If carriage return is received
		{
			continue;// Ignore and continue readin
		}
#else
		if(ch=='$')// If termination character is received
		{
			str[i+1]='\0';// Null-terminate the string
			break;
		}
#endif
	}
}
// Function to change the blocked status of a card
void Change_Stat()
{
	char str[10];// Buffer to store card number input
	SLL *node=Account_Details;// Pointer to traverse the linked list
	while(1)// Loop until valid input is received
        {
                printf("Enter 8 digit Card Number:");// Prompt user for input
                __fpurge(stdin);// Clear the input buffe
                scanf("%s",str);// Read the card number
                if(Compare_int(str))// Check if input contains only digits
                {
                        printf("enter integers only\n");// Prompt correct input format
                        continue;
                }
                else if(strlen(str)!=8)// Check if input length is valid
                {
                        printf("Enter 8 Digit Card Number\n");// Prompt correct length
                        continue;
                }
                else
                {
                	break;// Exit the loop with valid input
		}
	}
	while(node!=NULL) // Traverse the linked list
        {
                if(strcmp(node->RFID,str)==0)// Compare RFID with entered card number
                {
                       break;// Exit loop if match is found
                }
                node=node->next;// Move to the next node
        }
	if(!node)// If no matching account found
	{
		printf("No Account Found on this Card:%s\n",str);// Notify user
		return ;
	}
	else if(node->block)// If account is currently blocked
	{
		printf("blocked status is changed\n");// Notify user
		printf("Card Is Unblocked Now\n"); // Confirm unblocking
		node->block=0;// Change status to unblocked
	}
	else if(!node->block)// If account is not blocked
	{
		printf("account is not blocked\n");// Notify user
	}

}
