#include"header.h"// Include the required header file
SLL *Account_Details=NULL;// Pointer to the linked list of account details
char pin[10];// Buffer to store PIN information
SLL *rfid;// Pointer for RFID details
// Function to open the UART communication
int open_uart()
{
	struct termios options;// Structure to store UART configurations
	int fd=open("/dev/ttyUSB0",O_RDWR|O_NOCTTY);// Open UART device
	// Check if opening failed
	if(fd==-1)
	{
		perror("unable to open UART");// Print error message
		exit(0);// Exit if UART opening fails
	}
	fcntl(fd,F_SETFL,0); // Set file control flags
	
	tcgetattr(fd,&options);// Get current UART attributes

	cfmakeraw(&options);// Set raw input/output mode
	cfsetispeed(&options,B9600);// Set input baud rate
	cfsetospeed(&options,B9600);// Set output baud rate
	// Configure UART settings
	options.c_cflag &=~PARENB;// Disable parity bit
	options.c_cflag &=~CSTOPB;// Use one stop bit
	options.c_cflag &=~CSIZE;// Clear size bits
	options.c_cflag |=CS8;// Set 8-bit character size
	options.c_cflag |=(CREAD|CLOCAL);// Enable reading and local control
	options.c_lflag &=~(ICANON|ECHO|ECHOE|ISIG);// Set non-canonical mode
	options.c_oflag &=~OPOST;// Disable output processing

	tcsetattr(fd,TCSANOW|TCSAFLUSH,&options);// Apply settings immediately
	usleep(10000);// Delay for stability
	return fd;// Return file descriptor
}
int main()
{
	int fd,i;// File descriptor and loop variable
	char buff[30];// Buffer to store received data
	fd=open_uart(); // Open UART communication
	srand(time(NULL));// Seed the random number generator
	printf("%d\n",fd); // Print UART file descriptor
	Sync_From_File();// Load data from file
	// Infinite loop to handle UART communication
	while(1)
	{
#ifdef  DEBUG
		read_str(0,buff,30);// Read input from stdin
#else 
		puts("in while");// Debugging output
		read_str(fd,buff,30);// Read from UART
		//read(fd,buff,sizeof(buff));
#endif	
		printf("*%s*\n",buff);// Print received data
#ifdef DEBUG
		if(strcmp(buff,"#EXIT$")==0)// Check for exit command
		{
			write(1,"exited",strlen("exited")); // Print exit message
			break; // Exit loop
		}
		if(Account_Details==NULL)// Check if account details are missing
		{
			write(1,"@ERR#INVALID_CARD$",strlen("@ERR#INVALID_CARD$"));// Print error message
			break;// Exit loop
		}
#else 
#endif		
		if(strcmp(buff,"#OK:CNTD$")==0)// Check for connection confirmation
		{
			printf("CONNECTED\n");// Print connection message
#ifdef DEBUG
			write(1,"@OK:CNTD$",strlen("@OK:CNTD$")); // Print debug response
#else
			write(fd,"@OK:CNTD$",strlen("@OK:CNTD$"));// Write response to connect
#endif
		}
		// Handle different commands based on the second character of input
		switch(buff[1])
		{
			case 'r':printf("in rfid call\n");
				 Verify_RFID(buff,fd);// Process RFID verification
				 break;
			case 'p':printf("in pin call\n");
				 Verify_PIN(buff,fd);// Process PIN verification
				 break;
			case 'B':BLK_CARD(fd);// Block card function
				 break;
			case 'R':BAL_ENQ(fd);// Balance inquiry function
				 break;
			case 'D':DEP_BAL(buff,fd);// Deposit balance function
				 break;
			case 'W':WITH_BAL(buff,fd);// Withdraw balance function
				 break;
			case 'P':PIN_CHANG(buff,fd);// PIN change function
				break;
			case 'M':MINI_STMT(fd);// Mini statement function
				 break;

		}
		// Clear the buffer
		for(i=0;buff[i]!='\0';i++)
		{
			buff[i]=0;
		}
	}
	return 0;// End of program
}
