/*	
*	Author: Connor Kreider
*
*	This file contains the functions needed to have the transmitter function properly.
*	This includes initalizing the ADC, reading the ADC results, and sending the signal to the RX and TX lines
*	of the BLUESMiRF.
*
*
*/

#ifndef TRANSMITTER_H
#define TRANSMITTER_H



void init_adc()
{
	// Set ARef equal to AVcc
	ADMUX = (1<<REFS0);
	
	// Enable ADC
	ADCSRA = (1<<ADEN) | 7; // prescale = 128 (16MHz/128 = 125kHz)

}

uint8_t read_adc(uint8_t input)
{

	ADMUX = (1 << REFS0) | (input & 0x0F);	// Select the input and reference
	ADCSRA |= (1 << ADSC);					// Start conversion
	
	while (ADCSRA & (1 << ADSC));			// wair for end of conversion

	return (ADC);	// return converted value
}



#endif 
