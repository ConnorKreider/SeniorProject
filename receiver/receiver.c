/*
*	Author: Connor Kreider
*	
*	This code is for the ATMega328P for the receiver module
*	The reciver gets a digital signal from the transmitter BLUESMiRF which is
*	transmitted to the BLUESMiRF on the receiver. The digital signal is then sent to 
*	the MCP4725 DAC, and that analog signal goes to the Push-Pull stage of the reciever
*/

#include "receive.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void main()
{
	// USART
	USART_init();

	// Constantly read in value from BLUESMiRF and send to DAC
	while(1) {
		USART_receive();	
	
		// TO-DO // Need to change bits from 8 to 12 for DAC
		
		
	
		// Send to DAC
	}
	
	return 0;





}



