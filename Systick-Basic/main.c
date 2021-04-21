#include "MKL25Z4.h"                    // Device header

//Configure Systick to toggle RED led at 200ms

int main ()
{
	SIM -> SCGC5 |= 0x0400;
	PORTB -> PCR [18] = 0x100;
	PTB -> PDDR |= 0x040000;
	
	//Configure Systick
	SysTick -> LOAD = 8388000 -1; // System clock is 41.94MHz
	SysTick -> CTRL = 5;          // Enable systick, no interrupt, use system clock
	
	while(1)
	{
		if(SysTick -> CTRL & 0x10000) //if COUNT flag is set
		{
			PTB -> PTOR = 0x040000; //Toggle
		}
	}
  
}