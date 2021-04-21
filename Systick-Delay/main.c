/* p5_3.c Toggling green LED using SysTick delay
* This program uses SysTick to generate one second delay to
* toggle the green LED.
* System clock is running at 41.94 MHz. SysTick is configure
* to count down from 41939 to give a 1 ms delay.
* For every 1000 delays (1 ms * 1000 = 1 sec), toggle the
* green LED once. The green LED is connected to PTB19.
*/

#include "MKL25Z4.h"                    // Device header


void SysTickDelayMs(int delay);

int main()
{
	SIM -> SCGC5 |= 0x400;
	PORTB -> PCR[19] = 0x100;
	PTB -> PDDR |= 0x080000;
	
	while(1)
	{
		SysTickDelayMs(50);
		PTB -> PTOR = 0x080000;
	}
	
}



void SysTickDelayMs(int delay)
{
	int i;
	SysTick -> LOAD = 41940 -1; // Because systick clock is running at 41.94MHz
  SysTick -> CTRL = 0x5;
	for(i = 0; i < delay; i++)
	{
		// wait until the COUNT flag is set, dura 1ms en setear la bandera
		while((SysTick -> CTRL & 0x10000) == 0) {}
	}
	SysTick -> CTRL = 0;
}