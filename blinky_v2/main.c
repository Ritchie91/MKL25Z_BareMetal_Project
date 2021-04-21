//PTB18  RED cathode
//PTB19  GREEN cathode
//PTD1   BLUE cathode


#include "MKL25Z4.h"                    // Device header

void delayMs(int delay);

int main(void)
{
	SIM -> SCGC5 |= 0x400; // Enable clock for PORTB
	PORTB -> PCR[19] = 0x100; // Make PTB19 as GPIO
	PTB -> PDDR |= 0x80000; // Make PTB as an output pin
	
  while(1)
	{
		PTB -> PCOR = 0x80000; // Turn on green LED
		delayMs(50);
		PTB -> PSOR = 0x80000; // Turn off green LED
		delayMs(50);
	}		
	
	
}

void delayMs(int delay)
{
	for(int i = 0; i < delay; i++){
		for(int j = 0; j < 7000; j++){}
	}
}
