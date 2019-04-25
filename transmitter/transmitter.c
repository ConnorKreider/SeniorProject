/*
*	Author: Connor Krieder
*	
*	This code is for the ATMega328P for the transmitter module. 
*	The transmitter takes an Analog signal and uses the ADC to 
*	convert it to a digital signal that can be sent to the reciever with the BLUESMiRF breakout board.
*/

//#include "transmitter.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// For UART
#define FOSC 1843200 // Clock speed (need to go back and change this based on data sheet)
#define BAUD 9600	// Baud Rate
//#define MYUBRR FOSC/16/BAUD-1

void adc_init()
{
	// Set ARef equal to AVcc
	ADMUX = (1 << REFS0)|(1<<REFS1);
	// Enable ADC
	ADCSRA = (1 << ADEN) | 7; // prescale = 128 (16MHz/128 = 125kHz) 
}

uint16_t adc_read(uint8_t input)
{
	ADMUC = (1 << REFS0) | (input & 0x0F); // Select the input and reference
	ADCSRA |= (1 << ADSC);	// Start of conversion
	
	while (ADCSRA & (1 << ADSC));	// Wait for end of conversion

	printf("ADC Value: %d\n",ADC);
	return (ADC);	// Return converted value
}

void USART_init(unsigned int baud)
{
	// Set Baud Rate
	UBRROH = (unsigned char) (baud >> 8);
	UBRROL = (unsigned char) baud;

	// Enable Rx and Tx pins
	UCSROB = (1 << RXENOO) | (1 << TXEN0);

	// Set up frame
	// 8-bit data, 2 stop bits
	UCSROC = (1 << USBS0) | (3 << UCSZOO);
}

void USART_transmit(uint16_t data)
{
	// Wait for empty transmit buffer
	while( !(UCSRnA & (1 << UDREn));

	// Put data into buffer and send the data
	URDn = data;
	// Send low byte
	 // Send high byte need to make sure both are sent before starting next one
}


void main()
{
	uint16_t adc_value;

	// Initalize adc
	adc_init();

	// Initalize USART
	USART_init(BAUD);

	while(1) {
		// Sample rate is based on the frequency
		// because the max frequency we filter til is 200Hz
		// Sample rate is 10 * 200 = 2kSPS. Increase some more for overhead
		// For bluetooth transmission so bits don't get dropped. 3kSPS


		adc_value = adc_read(PC0);	// Read value of adc from PC0, ADC pin		
		USART_transmit(adc_val);
	}
	
	return 0;

}
