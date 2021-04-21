//PTB18  RED cathode
//PTB19  GREEN cathode
//PTD1   BLUE cathode

/*Para encender el LED recordar que el ánodo esta a 3.3 V. Por tanto,
  el pin del cátodo deberemos ponerlo a bajo. */

#include "MKL25Z4.h"                    // Device header

void delayMs(int delay);

int main()
{
	//SCGC5
	//Direction Register: PDDR
	//Data  //PDOR
	//PCR - Pin Control Register
	
	
	SIM -> SCGC5 |= 0x400;       // 0b  0100 0000 0000 : Enable clock to Port B
	PORTB -> PCR[18] |= 0x100;  // 0b  0001 0000 0000 : Set PTB18 as GPIO
	PTB -> PDDR |= 0x40000;      // Set PTB18 as output
	/* Es importante aclarar que cuando PTB -> PDDR es configurado, el registro
	   PTB -> PDOR esta en ceros, lo cual implica que el catodo este momentaneamente 
	   en bajo y lo podemos comprobar con el print statement:
	   printf("%x", PTB->PDOR);   */
	
	while(1)
	{
		PTB -> PDOR  &= ~0x40000;  //Turn red on, porque el cátodo se pone a bajo
		delayMs(250);
		PTB -> PDOR  |=0x40000;    //Turn red off, porque el cátodo se pone a alto
		delayMs(250);
	}	
	
}

void delayMs(int delay)
{
	for(int i = 0; i < delay; i++){
		for(int j = 0; j < 7000; j++){}
	}
}
