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

// For UART
#define FOSC 1843200 // Clock speed
#define BAUD 9600	// Baud Rate
#define MYUBRR FOSC/16/BAUD-1

void adc_init()
{
	// Set ARef equal to AVcc
	ADMUX = (1<<REFS0);
	
	// Enable ADC
	ADCSRA = (1<<ADEN) | 7; // prescale = 128 (16MHz/128 = 125kHz)

}

uint8_t adc_read(uint8_t input)
{

	ADMUX = (1 << REFS0) | (input & 0x0F);	// Select the input and reference
	ADCSRA |= (1 << ADSC);					// Start conversion
	
	while (ADCSRA & (1 << ADSC));			// wair for end of conversion

	return (ADC);	// return converted value
}

void USART_init()
{
	// Set Baud rate
	UBRROH = (unsigned char)(ubbr>>8);
	UBRROL = (unsigned char)ubbr;

	// Enable Rx and Tx pins
	UCSROB = (1<<RXENO)|(1<<TXEN0);

	// Set up frame.
	// 8-bit data, 2 stop bits
	UCSROC = (1<<USBSO)|(3<<UCSZOO);
}

void USART_transmit(uint8_t data)
{
	// Wait for empty transmit buffer
	while( !(UCSRnA & (1<<UDREn));

	// Put data into buffer and send the data
	UDRn = data;
}
#endif 
