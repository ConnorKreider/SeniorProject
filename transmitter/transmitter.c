/*
*	Author: Connor Krieder
*	
*	This code is for the ATMega328P for the transmitter module. 
*	The transmitter takes an Analog signal and uses the ADC to 
*	convert it to a digital signal that can be sent to the reciever with the BLUESMiRF.
*/

#include "transmitter.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>


void main()
{
	uint8_t adc_val;

	// Initalize adc
	adc_init();

	// Initalize USART
	USART_init();

	while(1) {
		
		adc_val = adc_read(PC0);	// Read value of adc from PC0, ADC pin		
		USART_transmit(adc_val);
	}
	
	return 0;

}
