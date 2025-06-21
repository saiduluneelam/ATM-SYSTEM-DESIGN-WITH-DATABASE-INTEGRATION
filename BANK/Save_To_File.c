#include "header.h"// Include necessary header file
// Function to save account details and transaction history to files
void Save_To_File(void)
{
	int size,i;// Variables for data size and iteration
	char filename[30];// Buffer for storing file name
	FILE *fptr1,*fptr2,*fptr3;// File pointers for different storage files
	fptr2=fopen("Bank_Details.csv","w");// Open CSV file for storing details
	fptr1=fopen("Bank_Details.txt","w");// Open text file for backup storage
	SLL *temp=Account_Details;// Pointer to traverse the account list
	size=sizeof(SLL)-sizeof(SLL*);// Calculate size excluding pointer
	while(temp)// Loop through all accounts
	{
		// Write account details to CSV file
		fprintf(fptr2,"%s,%d,%d,%d,%d,%s,%s,%ld,%lf,%d,%ld,%d\n",temp->Name,temp->Account_Number,temp->flag1,temp->flag2,temp->block,temp->pin,temp->RFID,temp->Contact_Number,temp->Account_Balance,temp->Trasnction_Count,temp->Aadhar_Number,temp->number);
	//	fwrite(temp,size,1,fptr1);
	//	// Format file name based on account number
		sprintf(filename,"%d.csv",temp->Account_Number);
		fptr3=fopen(filename,"w");// Open individual file for account transaction history
		if(temp->flag1)// If transaction history size exceeded
		{
			for(i=0;i<5;i++)// Save last 5 transactions
			{
				fprintf(fptr3,"%s,%lf,%d,%d,%d,%d,%d,%d,%d\n",temp->history[i].type,temp->history[i].amount,temp->history[i].Acc_Num,temp->history[i].month,temp->history[i].day,temp->history[i].year,temp->history[i].hour,temp->history[i].min,temp->history[i].trsncid);
			}
		}
		else// Otherwise, save all transaction records
		{
			for(i=0;i<temp->Trasnction_Count;i++)
                        {
                                fprintf(fptr3,"%s,%lf,%d,%d,%d,%d,%d,%d,%d\n",temp->history[i].type,temp->history[i].amount,temp->history[i].Acc_Num,temp->history[i].month,temp->history[i].day,temp->history[i].year,temp->history[i].hour,temp->history[i].min,temp->history[i].trsncid);
                        }

		}
		fclose(fptr3);// Close transaction history file
		temp=temp->next;// Move to next account
	}
	fclose(fptr1);// Close backup file
	fclose(fptr2);// Close main details file
	printf("SAVED SUCCESSFULLY\n");// Notify user of successful save
}
