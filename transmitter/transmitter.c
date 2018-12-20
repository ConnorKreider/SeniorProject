/*
*	Author: Connor Krieder
*	
*	This code is for the ATMega328P for the transmitter module. 
*	The transmitter takes an Analog signal and uses the ADC to 
*	convert it to a digital signal that can be sent to the reciever with the BLUESMiRF.
*/

#include "transmitter.h"



void main()
{
	uint8_t adc_val;

	// Initalize adc
	init_adc();

	while(1) {
		
		adc_val = read_adc()	// Read value of adc from !!!!!Find out which pin to read from!!!!!		

	}


}
