#include "headers.h"// Include necessary header file
// Function to create a microsecond delay
void delay_us(u32 delayus)
{
	delayus *=12;// Adjust delay timing based on system speed
	while(delayus--);// Loop to execute the delay
}
void delay_ms(u32 delayms)
{
		delayms *=12000;// Adjust delay timing based on system speed
		while(delayms--);// Loop to execute the delay
}
void delay_s(u32 delays)
{
		delays *= 12000000;// Adjust delay timing based on system speed
	  while(delays--);// Loop to execute the delay
}   
