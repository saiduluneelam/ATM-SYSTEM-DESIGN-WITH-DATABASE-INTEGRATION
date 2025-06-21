#include "header.h"// Include necessary header file
// Function to sync account details from stored files
void Sync_From_File(void)
{
	int size,num=0,i;// Variables for data size and iteration
	char filename[30];// Buffer for storing file name
	SLL var,*node,temp;// Temporary variables for handling data
	FILE *fptr1,*fptr2;// File pointers for reading account details
	fptr1=fopen("Bank_Details.csv","r");// Open CSV file containing account details
	size=sizeof(SLL)-sizeof(SLL*);// Calculate size excluding pointer
	if(fptr1)// Check if file opened successfully
	{
			while(fscanf(fptr1,"%[^,],%d,%d,%d,%d,%[^,],%[^,],%ld,%lf,%d,%ld,%d\n",temp.Name,&temp.Account_Number,&temp.flag1,&temp.flag2,&temp.block,temp.pin,temp.RFID,&temp.Contact_Number,&temp.Account_Balance,&temp.Trasnction_Count,&temp.Aadhar_Number,&temp.number)==12)
			{
		// Generate file name for individual transaction history		
                sprintf(filename,"%d.csv",temp.Account_Number);
                fptr2=fopen(filename,"r");// Open corresponding file for transaction history
                if(temp.flag1)// If transaction history limit exceeded
                {
                        for(i=0;i<5;i++)// Load last 5 transactions
                        {
                                fscanf(fptr2,"%[^,],%lf,%d,%d,%d,%d,%d,%d,%d\n",temp.history[i].type,&temp.history[i].amount,&temp.history[i].Acc_Num,&temp.history[i].month,&temp.history[i].day,&temp.history[i].year,&temp.history[i].hour,&temp.history[i].min,&temp.history[i].trsncid);
                        }
                }
                else// Otherwise, load all available transactions
                {
                        for(i=0;i<temp.Trasnction_Count;i++)
                        {
				       fscanf(fptr2,"%[^,],%lf,%d,%d,%d,%d,%d,%d,%d\n",temp.history[i].type,&temp.history[i].amount,&temp.history[i].Acc_Num,&temp.history[i].month,&temp.history[i].day,&temp.history[i].year,&temp.history[i].hour,&temp.history[i].min,&temp.history[i].trsncid);
                        }

                }
		temp.next=0;// Set next pointer to NULL
                fclose(fptr2);// Close transaction history file
        	node=calloc(1,sizeof(SLL));	// Allocate memory for new account node
		memmove(node,&temp,sizeof(temp));// Copy temporary data into allocated node
		// If list is empty, set first node
		if(Account_Details==NULL)
		{
			Account_Details=node;
		}
		else// Otherwise, insert node at the beginning
		{
			node->next=Account_Details;
			Account_Details=node;
		}
	}
	}
	fclose(fptr1);// Close account details file
}
