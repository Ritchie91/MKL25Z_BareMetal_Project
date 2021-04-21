
//PTB18  RED cathode
//PTB19  GREEN cathode
//PTD1   BLUE cathode

#include "MKL25Z4.h"                    // Device header

void delayMs(int delay);
int main(void)
{
	SIM -> SCGC5 |= 0x400;  //Enable clock to PORTB
	SIM -> SCGC5 |= 0x1000; //Enable clock to PORTD
  
	PORTB -> PCR[18] = 0x100;  //make PTB18 a GPIO
	PORTB -> PCR[19] = 0x100;  //make PTB19 a GPIO
	PORTD -> PCR[1] = 0x100;  //make PTD1 a GPIO
	
	PTB -> PDDR |= 0xC0000;   //make PTB18 and PTB19 output pins
	PTD -> PDDR |= 0x02;      //make PTD1 an output pin 
	
	while(1)
	{
		PTB -> PDOR &=~0xC0000; //turn on red and green leds
		PTD -> PDOR &=~0x02;    //turn off blue led
		delayMs(100);
		
		PTB -> PDOR |= 0xC0000; //turn off red and green leds
		PTD -> PDOR |= 0x02;    //turn off blue led
		delayMs(100);
	}
}



void delayMs(int delay)
{
	for(int i = 0; i < delay; i++){
		for(int j = 0; j < 7000; j++){}
	}
}