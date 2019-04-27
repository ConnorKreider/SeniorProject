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
#include <stdlib.h>

#define FOSC 1843200
#define BAUD 9600
//#define MYBURR FOSC/16/BAUD-1





/* void USART_init(unsigned int baud)
{
	//Set Baud rate
	UBRROH = (unsigned char)(ubrr>>8);
	UBRROL = (unsigned char)ubrr;

	// Enable Rx and Tx pins
	UCSROB = (1<<RXEN0)|(1<<TXEN0);

	// Frame format
	UCSROC = (1<<USBS0)|(3<<UCSZ00);

} */

/*unsigned char USART_receive(void)
{
	// Wait for an empty transmit buffer
	while(!(UCSRnA & (1<<UDREn)));

	// Put data recieved into the buffer that sends data
	UDRn = data;

	// Wait for data to be received
	while(!(UCSRnA & (1<<RXCn);

	// Return data received
	return UDRn;
}
*/

void TWI_init_master(void)
{
	TWBR = 0x01;	// Bit rate
	TWSR = (0<<TWPS1)|(0<<TWPS0);
}


void TWI_init_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));	// Wait for start condition to transmit
	while((TWSR & 0xF8)!= 0x08);	// Check for acknowledgement
	
}

void TWI_read_address(unsigned char data)
{
	TWDR = data;	// Read instruction
	TWCR = (1<<TWINT)|(1<<TWEN);	// Clear TWI interrupt flag, enable TWI
	while(!(TWCR & (1<<TWINT)));	// Wait for complete byte
	while((TWSR & 0xF8)!= 0x40);	// Check acknoledgement

}

void TWI_write_data(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);	// Clear TWI interrupt, enable TWI
	while(!(TWCR & (1<<TWINT)));	// Wait till TWDR complete byte transmitted
	while((TWSR & 0xF8) != 0x28);	// Check for the acknoledgment
}

void TWI_stop(void)
{
	//Clear TWI interrupt flag, SDA stop condition, Enable TWI
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(!(TWCR & (1<<TWSTO)));	// Wait until stop condition is transmitted 
}

int main(void)
{
	// MCP4720 address is 0x62 for slave
	int i;

/*
	int blink = 0;
	DDRD = 0x00;
	PORTD = 0xFF;
	DDRB = 0xFF;

	
	PORTB |= (1<<1);
*/


	// USART
	//USART_init(BAUD);

	// Constantly read in value from BLUESMiRF and send to DAC
//	while(1) {
//		USART_receive();	
	

		// TO-DO // Need to change bits from 8 to 12 for DAC
		// Pad the 2 most signifcant bits of the buffer
		// This keeps the value from changing. 		

		/*************************/
		// Communicate to the DAC
		
//	}

	for(i=0;i<2048;i++){
			



	}
	
	return 0;


}



