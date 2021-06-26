/* p6_3: Toggle blue LED by PTD4 interrupt on both edges */
/* PTD4 is configured to interrupt on both rising edge and falling edge. In the
interrupt handler, the blue LED (PTD1) is toggled. */

#include "MKL25Z4.h"                    // Device header

int main(void)
{
__disable_irq();          // disable all IRQs
SIM -> SCGC5 |= 0x1000;   // enable clock to Port D
PORTD -> PCR[1] = 0x100;  // make PTD1 pin as GPIO
PTD -> PDDR |= 0x02;      // make PTD1 as output pin
PTD -> PDOR |= 0x02;      // turn off blue LED
	
/* configure PTD4 for interrupt */
PORTD -> PCR[4] |= 0x00100;  // make it GPIO
PORTD -> PCR[4] |= 0x00003;  // enable and select pull-up
PTD -> PDDR &= ~0x0010;      // make pin input
PORTD -> PCR[4] &= ~0xF0000; // clear interrupt selection
PORTD -> PCR[4] |= 0xB0000;  // enable both edge interrupt
NVIC -> ISER[0] |= 0x80000000; // enable INT31 (bit 31 of ISER[0])
__enable_irq();              // global enable IRQs
while(1)
{ }
} 

/*A pushbutton switch is connected to PTD4 pin to trigger PORTD interrupt */
void PORTD_IRQHandler(void){
if (PORTD->ISFR & 0x00000010){
	/* toggle blue LED (PTD1) */
	PTD -> PTOR |= 0x0002;  // toggle blue LED
	PORTD -> ISFR = 0x0010; // clear interrupt flag
	}
}