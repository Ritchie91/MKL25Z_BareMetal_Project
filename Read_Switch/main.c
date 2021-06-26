/* p2_8.c Read a switch and write it to the LED.
* This program reads an external switch connected to PTA1
* of FRDM board and writes the value to the green LED.
* When switch is pressed, it connects PTA1 to ground.
* PTA1 pin pull-up is enabled so that it is high when
* the switch is not pressed.
* LED is on when low.
*/

#include "MKL25Z4.h"                    // Device header

int main (void) {
SIM -> SCGC5 |= 0x400;     // enable clock to Port B
PORTB -> PCR[19] = 0x100;  // make PTB19 pin as GPIO 
PTB -> PDDR |= 0x80000;    // make PTB19 as output pin
SIM -> SCGC5 |= 0x200;     // enable clock to Port A
PORTA -> PCR[1] = 0x103;   // make PTA1 pin as GPIO and enable pull-up	
PTA -> PDDR &= ~0x02;      // make PTA1 as input pin
while (1) {
	/* La siguiente condición, checa el estado del switch:
		* Cuando el switch no esta presionado, el pin PTA1 está en
		* alto cumpliendo la condición del if.
		* Cuando se presiona el switch, el pin PTA1 se pone en bajo,
		* no cumpliendo el if y activando las instrucciones del else.
	*/
	if (PTA -> PDIR & 2)       
		PTB -> PSOR = 0x80000;     // Pone en alto el cátodo, LED apagado
	else
		PTB -> PCOR = 0x80000;     // Pone en bajo el cátodo, LED encendido
	}
}