/* p5_5.c Toggling blue LED using TPM0 delay (prescaler)
* This program uses TPM0 to generate maximal delay to
* toggle the blue LED.
* MCGFLLCLK (20.97152 MHz) is used as timer counter clock.
* Prescaler is set to divided by 128 and the Modulo register
* is set to 65,535. The timer counter overflows at
* (20.97152 MHz / 128) / 65,536 = 2.5 Hz
*
*The blue LED is connected to PTD1.
*/

#include "MKL25Z4.h"                    // Device header

int main (void)
{
	SIM -> SCGC5 |= 0x1000;      // Enable clock to Port D
	PORTD -> PCR [1] = 0x100;    // Make PTD1 pin as GPIO
	PTD -> PDDR |= 0x02;         // make PTD1 as output pin
	
	SIM -> SCGC6 |= 0x01000000;  // Enable clock source for the timer module TPM0
	SIM -> SOPT2 |= 0x01000000;  // SOPT2 contains the controls for selecting many 
	                             // of the module clock source options on this device
	
	TPM0 -> SC = 0;              // Disable timer while configuring
	TPM0 -> SC = 0x07;           // Prescaler/128
	TPM0 -> MOD = 0xFFFF;        // max modulo value (20.97152 MHz/128)/65536 = 2.5 Hz
	TPM0 -> SC |= 0x80;          // Clear TOF
	TPM0 -> SC |= 0x08;          // enable timer free-running mode
	
	
	while(1)
	{
		/* Wait until the TOF is set */
		while((TPM0 -> SC & 0x80) == 0){}
			TPM0 -> SC |= 0x80;      // Clear TOF
			PTD -> PTOR = 0x02;      // Toggle blue LED
	}
}


