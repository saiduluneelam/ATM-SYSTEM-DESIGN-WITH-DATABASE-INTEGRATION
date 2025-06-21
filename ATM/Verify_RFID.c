#include"header.h" // Include necessary header file
// Function to verify RFID and check the account status
void Verify_RFID(char *buff,int fd)
{

	SLL *temp;// Pointer to traverse the linked list
	char buf[30];// Buffer to store extracted RFID
	temp=Account_Details;// Initialize traversal pointer
	strcpy(buf,extract_int(buff));// Extract RFID from input
	printf("...%s...\n",buf);// Print extracted RFID for debugging
	// Traverse linked list to find a matching RFID
	while(temp)
	{
		if(strcmp(temp->RFID,buf)==0)
		{
			rfid=temp;// Store matched account in the global RFID pointer
			strcpy(pin,temp->pin); // Copy associated PIN
			printf("%s\n",pin);// Print PIN for debugging
			break;// Exit loop on match
		}
		temp=temp->next;// Move to the next node
	}
	if(temp)// If account found
	{
		if(!temp->block)// Check if account is active
		{
			printf("ACTIVE\n");// Print status
#ifdef DEBUG
			write(1,"@OK#ACTV$",strlen("@OK#ACTV$")); // Send active status
#else
			puts("in sending");
			write(fd,"@OK#ACTV$",strlen("@OK#ACTV$")); // Send active status
#endif
		}
		else// If account is blocked
		{
			printf("BLOCKED\n");// Print status
#ifdef DEBUG
			write(1,"@BLKD$",strlen("@BLKD$"));// Send blocked status
#else 
			write(fd,"@BLKD$",strlen("@BLKD$"));// Send blocked status
#endif
		}
	}
	else// If RFID is invalid
	{
		printf("INVALID CARD\n");
#ifdef DEBUG
		write(1,"@ERR#CARD$",strlen("@ERR#CARD$"));// Send error message
#else 
		write(fd,"@ERR#CARD$",strlen("@ERR#CARD$"));// Send error message
#endif
	}
}
