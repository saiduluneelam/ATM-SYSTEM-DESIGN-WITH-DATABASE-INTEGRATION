#include "headers.h"// Include necessary header file
// Function to scan the column status
u32 ColScan()
{
	return (((IOPIN1>>COL0)&15)<15)?0:1;// Returns 0 if a key is pressed, otherwise 1
}

// Function to determine which row has the key press
u32 RowCheck()
{
	u32 r;// Row index
	for(r=0;r<4;r++)// Loop through all rows
	{
		// Set a single row low while keeping others high
		IOPIN1=((IOPIN1&~(15<<ROW0))|((~(1<<r))<<ROW0));
		if(ColScan()==0)// Check if any key is pressed in the current row
		{
			break;// Exit loop when a key press is detected
		}
	}
	IOCLR1=15<<ROW0;// Clear row bits
	return r;// Return detected row index
}
// Function to determine which column has the key press
u32 ColCheck()
{
	u32 c;// Column index
	for(c=0;c<4;c++)// Loop through all columns
	{
		if((IOPIN1>>(COL0+c)&1)==0)// Check for key press in column
		{
			break;// Exit loop when key is detected
		}
	}
	return c;// Return detected column index
}
// Function to read a key press with timeout
u8 Read_key(void) 
{
    u32 row, col;// Variables to store detected row and column
    s32 timeout = 30000; // Approximate delay for 30 seconds
    	while (ColScan() && timeout>0)// Wait for key press with timeout 
	{
		timeout--;
	        delay_ms(1); // Decrement timeout every millisecond
    	}
	// If timeout occurred
    	if (timeout == 0) 
	{
        	return TIMEOUT_FLAG; // Indicate timeout occurred
    	}

    	row = RowCheck();// Detect row index
    	col = ColCheck();// Detect column index
	// Return corresponding key from lookup table
    	return KPMLUT[row][col];
}
// Function to initialize the keypad matrix
void InitKPM(void)
{
	IODIR1|=15<<ROW0;// Set row pins as output
}

