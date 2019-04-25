/*
*	Author: Connor Kreider
*	
*	This code is for the ATMega328P for the receiver module
*	The reciver gets a digital signal from the transmitter BLUESMiRF which is
*	transmitted to the BLUESMiRF on the receiver. The digital signal is then sent to 
*	the MCP4725 DAC, and that analog signal goes to the Push-Pull stage of the reciever
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>	// for testing avr
#include <stdlib.h>

#define FOSC 1843200
#define BAUD 9600
//#define MYBURR FOSC/16/BAUD-1

//void USART_init(unsigned int baud)
//{
//	//Set Baud rate
//	UBRROH = (unsigned char)(ubrr>>8);
//	UBRROL = (unsigned char)ubrr;

//	// Enable Rx and Tx pins
//	UCSROB = (1<<RXEN0)|(1<<TXEN0);

//	// Frame format
//	UCSROC = (1<<USBS0)|(3<<UCSZ00);

//}

//unsigned char USART_receive(void)
//{
	// Wait for an empty transmit buffer
	//while(!(UCSRnA & (1<<UDREn)));

	// Put data recieved into the buffer that sends data
	//UDRn = data;

	// Wait for data to be received
//	while(!(UCSRnA & (1<<RXCn);

	// Return data received
//	return UDRn;
//}

int main(void)
{
	int blink = 0;
	DDRD = 0x00;
	PORTD = 0xFF;
	DDRB = 0xFF;


	//LED on
	PORTB |= (1<<1);



	// USART
//	USART_init(BAUD);

	// Start condition to enable communicate with DAC
//	if ((TWSR & 0xF8) != START)

//	while (!(TWCR & (1<<TWINT))); // Wait to see if start condition is transmitted
	
	// Check value of TWI status register
	// If the status is different from Start go to Error	
//	if ((TWSR & 0xF8) != START) {
//		ERROR();
//	}
	

	// Constantly read in value from BLUESMiRF and send to DAC
//	while(1) {
//		USART_receive();	
	

		// TO-DO // Need to change bits from 8 to 12 for DAC
		// Pad the 2 most signifcant bits of the buffer
		// This keeps the value from changing. 		

		/*************************/
		// Communicate to the DAC
		
/*		// Clear to start transmission of address
		TWDR = SLA_W;		
		TWCR = (1<<TWINT)|(1<<TWEN);

		// Wait for flag to be set
		while(!(TWCR & (1<<TWINT)));

		// Check TWI status
		if ((TWSR & 0xF8) != MT_SLA_ACK){
			ERROR();
		}

		// Load the data into the register
		TWDR = DATA;

		// Clear the TWINT bit to start transmitting
		TWCR = (1<<TWINT)|(1<<TWEN);

		// Waits to make sure data was transmitted
		while(!(TWCR & (1<<TWINT)));

		// Check TWI status
		if ((TWSR & 0xF8) != MT_DATA_ACK){
			ERROR();
		}

	}

	// Have the data stop being transmitted
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
*/	
	return 0;


}



