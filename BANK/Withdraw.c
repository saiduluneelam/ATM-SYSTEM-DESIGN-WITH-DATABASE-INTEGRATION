#include "header.h"// Include necessary header file
// Function to verify if the given number has more than 10 digits
int count(long int num)
{
	int d=0,j;
	while(num>0) // Loop until all digits are processed
	{
		j=num%10;// Extract last digit
		d++;// Increment digit count
		num/=10;// Remove last digit
	}
	if(d>10)// If more than 10 digits are present
	return 1;
	else
	return 0;
}
// Function to handle withdrawal transactions
void Withdraw(void)
{
	SLL *temp;// Pointer to traverse the linked list
	size_t now;// Variable to store current time
	struct tm *current_time; // Structure to store transaction time
	long int acc_num;// Variable for account number/Aadhar number
	int i,max=27835438,min=26857429;// Variables for transaction ID generation
	double amount;// Variable for withdrawal amount
	time(&now);// Get the current time
	current_time=localtime(&now);// Convert to local time structure
	printf("Enter Account Number/Aadhar Number:");
	scanf("%ld",&acc_num);// Read account number
	temp=Account_Details;// Initialize traversal pointer
	// Traverse the linked list to find the matching account
	while(temp)
	{
		if((temp->Account_Number==acc_num)||(temp->Aadhar_Number==acc_num))
		{
			break;// Exit loop when match is found
		}
		temp=temp->next;// Move to the next node
	}
	if(temp==NULL)// If account is not found
	{
		printf("Invalid Account Number!\n");
	}
	else 
	{
		if(count(acc_num))
		{
			// Check if OTP authentication is required
OTP:printf("Enter the OTP sent to your mobile number:");
			scanf("%d",&i);// Read OTP from user
			if(i<0)// Validate OTP input
			{
				printf("Invalid OTP !");
				goto OTP;// Retry OTP input
			}
		}

amount:		amount=Read_Bal(0);// Read withdrawal amount from user
		if(amount>temp->Account_Balance)// Check for sufficient balance
		{
			printf("Insufficient balance!\n");
			goto amount;// Retry amount input
		}
		else
		{
			// If transaction history exceeds limit
			if(temp->number>=5)
			{
				temp->number=0;// Reset transaction index
				temp->flag1=1;// Set history shift flag
			}
			// Deduct withdrawal amount from account balance
			temp->Account_Balance=(temp->Account_Balance-amount);
			// Increment transaction count
			temp->Trasnction_Count++;
			// Shift old transaction history entries
			memmove(&temp->history[1],&temp->history[0],4*sizeof(Trsnc));
			 // Store new transaction details
			strcpy(temp->history[0].type,"WITHDRAW");
			temp->history[0].amount=amount;
			temp->history[0].Acc_Num=temp->Account_Number;
			temp->number++;
			temp->history[0].year=current_time->tm_year+1900;
			temp->history[0].month=current_time->tm_mon+1;
			temp->history[0].day=current_time->tm_mday;
			temp->history[0].hour=current_time->tm_hour;
			temp->history[0].min=current_time->tm_min;
			temp->history[0].trsncid=(rand()%(max-min+1))+min;
			printf("WITHDRAWAL SUCCESSFUL\n");	
		}
	}
}
