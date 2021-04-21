/* p5_5.c Toggling blue LED using TPM0 delay (prescaler)
* This program uses TPM0 to generate maximal delay to
* toggle the blue LED.
* MCGFLLCLK (41.94 MHz) is used as timer counter clock.
* Prescaler is set to divided by 128 and the Modulo register
* is set to 65,535. The timer counter overflows at
* 41.94 MHz / 128 / 65,536 = 5.0 Hz
**
The blue LED is connected to PTD1.
*/

#include "MKL25Z4.h"                    // Device header

int main (void)
{
	SIM -> SCGC5 |= 0x1000;
	PORTD -> PCR [1] = 0x100;
	PTD -> PDDR |= 0x02;
	
	SIM -> SCGC6 |= 0x01000000;  // Enable clock source for the timer module TPM0
	SIM -> SOPT2 |= 0x01000000;  // SOPT2 contains the controls for selecting many 
	                             // of the module clock source options on this device
	
	TPM0 -> SC = 0;
	TPM0 -> SC = 0x07;  // Prescaler/128
	TPM0 -> MOD = 0xFFFF;  // 41.94MHz/ 128/ 65536 = 5.0Hz
	TPM0 -> SC |= 0x80;
	TPM0 -> SC |= 0x08;
	
	
	while(1)
	{
		while((TPM0 -> SC & 0x80) == 0){}
			TPM0 -> SC |= 0x80;  // Clear TOF
			PTD -> PTOR = 0x02;
	}
}


