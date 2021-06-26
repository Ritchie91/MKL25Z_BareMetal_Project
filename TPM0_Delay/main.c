/* p5_4.c Toggling blue LED using TPM0 delay
* This program uses TPM0 to generate maximal delay to toggle the blue LED.
* MCGFLLCLK (20.97152 MHz) is used as timer counter clock.
* The Modulo register is set to 65,535. The timer counter overflows at
* 20.97152 MHz / 65,536 = 320 Hz
* We put the time out delay in a for loop and repeat it for 160 times before we
* toggle the LED. This results in the LED flashing at half second on and half
* second off.
* The blue LED is connected to PTD1.
*/

#include "MKL25Z4.h"                    // Device header

int main(void){
int i;
SIM -> SCGC5 |= 0x1000;            // enable clock to Port D
PORTD -> PCR[1] = 0x100;           // make PTD1 pin as GPIO
PTD -> PDDR |= 0x02;               // make PTD1 as output pin
SIM -> SCGC6 |= 0x01000000;        // enable clock to TPM0
SIM -> SOPT2 |= 0x01000000;        // use MCGFLLCLK as timer counter clock
TPM0 -> SC = 0;                    // disable timer while configuring
TPM0 -> MOD = 0xFFFF;              // max modulo value
TPM0 -> SC |= 0x80;                // clear TOF
TPM0 -> SC |= 0x08;                // enable timer free-running mode
while (1) {
for(i = 0; i < 160; i++) {         // repeat timeout for 160 times
while((TPM0->SC & 0x80) == 0) { }  // wait until the TOF is set
TPM0 -> SC |= 0x80;                // clear TOF
} 
PTD -> PTOR = 0x02;                // toggle blue LED
}
}