#include "header.h" // Include necessary header file
// Function to transfer money between two accounts
void Transfer_Money(void)
{
	SLL *temp1,*temp2;// Pointers for sender and receiver accounts
	int acc_num1,acc_num2,max=24753289,min=23186489;// Account numbers and transaction ID range
	double amount;// Variable for transfer amount
	size_t now;// Time variable
	struct tm *current_time;// Structure to store transaction time
	time(&now);// Get current time
	current_time=localtime(&now);// Convert to local time structure
	printf("Enter your Account Number:");// Prompt for sender account number
	__fpurge(stdin); // Clear input buffer
	scanf("%d",&acc_num1);// Read sender account number
	temp1=Account_Details;// Initialize traversal pointer
	// Search for sender account
	while(temp1)
	{
		if(temp1->Account_Number==acc_num1)
		{
			break;// Exit loop if account is found
		}
		temp1=temp1->next;// Move to next node
	}
	if(temp1==NULL)// If sender account not found
	{
		printf("Invalid Account Number!\n");// Notify user
	}
	else
	{
		printf("Enter Amount to be Transfered account number:");// Prompt for recipient account number
		__fpurge(stdin);
	 	scanf("%d",&acc_num2);// Read recipient account number
		temp2=Account_Details;// Initialize traversal pointer for recipient account
		// Search for recipient account
		while(temp2)
		{
			if(temp2->Account_Number==acc_num2)
			{
				break;// Exit loop if account is found
			}
			temp2=temp2->next;// Move to next node
		}
		if(temp2==NULL)// If recipient account not found
		{
			printf("Invalid account number!\n");// Notify user
		}
		else
		{
amount:		amount=Read_Bal(0);	// Read transfer amount
		if(amount>temp1->Account_Balance)// Check for sufficient balance
		{
			printf("Insufficient Balance!\n");// Notify user
			goto amount;// Retry input
		}
		else
		{
			// Deduct amount from sender's account
			temp1->Account_Balance=(temp1->Account_Balance-amount);
			temp1->Trasnction_Count++;
			// Add amount to recipient's account
			temp2->Account_Balance=(temp2->Account_Balance+amount);
			temp2->Trasnction_Count++;
			printf("TRANSFER SUCCESSFUL\n");
			// Manage transaction history for sender		
			if(temp1->number>=5)
                        {
                                temp1->number=0;
                                temp1->flag1=1;
                        }
			memmove(&temp1->history[1],&temp1->history[0],4*sizeof(Trsnc));
			strcpy(temp1->history[0].type,"Transfer Out");
                        temp1->history[0].amount=amount;
                        temp1->history[0].Acc_Num=temp1->Account_Number;
			temp1->history[0].year=current_time->tm_year+1900;
			temp1->history[0].month=current_time->tm_mon+1;
			temp1->history[0].day=current_time->tm_mday;
			temp1->history[0].hour=current_time->tm_hour;
			temp1->history[0].min=current_time->tm_min;
			temp1->history[0].trsncid=(rand()%(max-min+1))+min;
                        temp1->number++;
			 // Manage transaction history for recipient
			if(temp2->number>=5)
                        {
                                temp2->number=0;
                                temp2->flag1=1;
                        }
			memmove(&temp2->history[1],&temp2->history[0],4*sizeof(Trsnc));
                        strcpy(temp2->history[0].type,"Transfer In");
                        temp2->history[0].amount=amount;
                        temp2->history[0].Acc_Num=temp2->Account_Number;
			temp2->history[0].year=current_time->tm_year+1900;
			temp2->history[0].month=current_time->tm_mon+1;
			temp2->history[0].day=current_time->tm_mday;
			temp2->history[0].hour=current_time->tm_hour;
			temp2->history[0].min=current_time->tm_min;
			temp2->history[0].trsncid=(rand()%(max-min+1))+min;
                        temp2->number++;
		}
		}
	}
}
