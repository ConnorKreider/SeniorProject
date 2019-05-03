/*
*	Author: Connor Krieder
*	
*	This code is for the ATMega328P for the transmitter module. 
*	The transmitter takes an Analog signal and uses the ADC to 
*	convert it to a digital signal that can be sent to the reciever with the BLUESMiRF breakout board.
*/

//#include "transmitter.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// For UART
#define FOSC 8000000 // Clock speed (need to go back and change this based on data sheet
// Baud Rate 38.4K
//#define LED() PORTB=0x02


void adc_init(void);
uint16_t adc_read(void);
void USART_init(void);
void USART_transmit(uint16_t data);

int main(void)
{
	uint16_t adc_value;
	//uint16_t i;

	DDRB=0x02;
	// Initalize USART and ADC
	USART_init();
	adc_init();

	while(1) {
		// Sample rate is based on the frequency
		// because the max frequency we filter til is 200Hz
		// Sample rate is 10 * 200 = 2kSPS. Increase some more for overhead
		
		adc_value = adc_read();
		USART_transmit((adc_value>>2)&0xFF);
		PORTB=PORTB^0x02;
		
	#if 0
		for(i=0;i<16;i++){
	
			USART_transmit('a'+i);
		}
		USART_transmit('\n');
	#endif
	}
	
	return 0;
}


void adc_init(void)
{
	// Set ARef equal to AVcc, and use of ADC0
	ADMUX = (1 << REFS0) | (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0);
	// Enable ADC
	ADCSRA = (1 << ADEN) | 7; //prescale = 128 (8MHz/128 = 62.5kHz)
}

uint16_t adc_read(void)
{
	//ADMUX = (1 << REFS0) | (input & 0x0F); // Select the input and reference
	ADCSRA |= (1 << ADSC);	// Start of conversion
	
	while (ADCSRA & (1 << ADSC));	// Wait for end of conversion

	return (ADC);	// Return converted value
}


void USART_init(void)
{
	// Enable 2x mode
	UCSR0A = (1<<U2X0);

	// Set Baud Rate
	//UBRROH = (unsigned char) (baud >> 8);
	//UBRROL = (unsigned char) baud;
	UBRR0 = 24;	// Found on page 202 datasheet

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


