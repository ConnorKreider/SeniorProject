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
#define FOSC 8000000 // Clock speed (need to go back and change this based on data sheet)
#define BAUDRATE 9600	// Baud Rate
//#define MYUBRR FOSC/16/BAUD-1


void adc_init();


void USART_init(void);
void USART_transmit(uint16_t data);

void main()
{
	uint16_t adc_value;
	uint16_t i;

	// Initalize adc
	//adc_init();

	// Initalize USART
	USART_init();

	while(1) {
		// Sample rate is based on the frequency
		// because the max frequency we filter til is 200Hz
		// Sample rate is 10 * 200 = 2kSPS. Increase some more for overhead
		// For bluetooth transmission so bits don't get dropped. 3kSPS
		for(i=0;i<4095;i++)
			
	
	//	adc_value = adc_read(PC0);	// Read value of adc from PC0, ADC pin		
			USART_transmit(i);
	}
	
	return 0;
}

#if 0
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
#endif

void USART_init(void)
{
	// Set Baud Rate
	//UBRROH = (unsigned char) (baud >> 8);
	//UBRROL = (unsigned char) baud;
	UBRR0 = 51;	// Found on page 202 datasheet

	// Set up frame
	// 8-bit data, 1 stopbit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
	// Enable Rx and Tx pins
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

}

void USART_transmit(uint16_t data)
{
	// Wait for empty transmit buffer
	while( !(UCSR0A & (1 << UDRE0)));

	// Put data into buffer and send the data
	UDR0 = data;
	// Send low byte
	 // Send high byte need to make sure both are sent before starting next one
}


