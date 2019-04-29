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
#include <util/delay.h>
#include <stdlib.h>
#define FOSC 8000000
#define BAUDRATE 9600
#define UBRR_VALUE (((FOSC/(16UL * BAUDRATE))) - 1)
#define SCL_CLOCK 100000

#define LED() PORTB=0x02

// Global variables
// MCP4720 address is 0x62 for slave
//unsigned char read = 1, write = 0;
//unsigned char writeData = 0x01, recVData;


void TWI_init_master(void);
uint16_t TWI_start(uint8_t  address);
uint16_t TWI_write_data(unsigned char data);
void TWI_stop(void);
void USART_init(void);
uint16_t USART_receive(void);
void USART_transmit(uint16_t data);

int main(void)
{
	uint16_t i;
	uint8_t dacAddress = 0x62;
	uint16_t testData;

#if 0
	int blink = 0;
	DDRD = 0x00;
	PORTD = 0xFF;
	DDRB = 0xFF;
	
	PORTB =0xFF;

	while(1);
#endif

	// USART
	USART_init();

	// Get a value from Arduino Uno and send it back
	while(1) {
		testData = USART_receive();	
		testData++;
		USART_transmit(testData);
	}
		// TO-DO // Need to change bits from 8 to 12 for DAC
		// Pad the 2 most signifcant bits of the buffer
		// This keeps the value from changing. 		

		
	

#if 0
   	// Sending data to the DAC
	DDRB = 0xFF;
	TWI_init_master();

	// Go up the wave
	//for(i=0;i<2048;i++){
	
	TWI_start(dacAddress);
	TWI_write_data(0x00);
	TWI_write_data(0x00);
	TWI_stop();

	while (1) {
		for (i=0;i<4096;i++) {
			TWI_start(dacAddress);
			TWI_write_data(i>>8);
			TWI_write_data(i&0xFF);
			TWI_stop();
		}
	}
#endif
	return 0;
}

void USART_init(void)
{
	//Set Baud rate
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)UBRR_VALUE;

	// Enable Rx and Tx pins
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	// Frame format: 8data, 2stopbits
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

uint16_t USART_receive(void)
{
	// Wait for data to be received
	while(!(UCSR0A & (1<<RXC0)));

	// Return data received
	return UDR0;
}

void USART_transmit(uint16_t data)
{
	// Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));

	// Put data into buffer, send the data;
	UDR0 = data;

}

void TWI_init_master(void)
{
	
	TWSR = (0<<TWPS1)|(0<<TWPS0); 
	TWBR = 0;	//((F_CPU/SCL_CLOCK)-16)/2;	// Bit rate
	TWCR = (1<<TWEN);	
/*	DDRD = 0x00;
	PORTD = 0xFF;
	DDRB = 0xFF;
	
	PORTB |= (1<<1);
*/
}


// start i2c
uint16_t TWI_start(uint8_t  address)
{
	uint8_t twst;

	// Send start condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); 

	// Wait for transmission to complete
	while(!(TWCR & (1<<TWINT)));	
	
	// Check value of TWI Status Register
	// Mask Prescaler bits
	twst = TWSR & 0xF8;
	if (twst != 0x08) {
		return 0; // return zero to indicate failure
	}

	// Send slave device address
	TWDR = (address<<1);
	TWCR = (1<<TWINT) | (1<<TWEN);

	// Wait for transmission to complete
	while(!(TWCR & (1<<TWINT)));

	// Check value of TWI Status Register
	// Mask prescaler bits
	twst = TWSR & 0xF8;
	if (twst == 0x18)  {
		LED();
		 return 1;	// Ack received
	}
	if (twst == 0x20){
		return 2; // nack received
	} else {
		return 3; // Slave address + write failed
	}
	
} // Start i2c

/*void TWI_read_address(unsigned char data)
{
	TWDR = data;	// Read instruction
	TWCR = (1<<TWINT)|(1<<TWEN);	// Clear TWI interrupt flag, enable TWI
	while(!(TWCR & (1<<TWINT)));	// Wait for complete byte
	while((TWSR & 0xF8)!= 0x40);	// Check acknoledgement

} */

uint16_t TWI_write_data(unsigned char data)
{
	uint8_t twst;
	
	// Copy data to data register
	TWDR = data;
	// Enable TWI and clear interupt flag
	TWCR = (1<<TWINT)|(1<<TWEN);
	// Wait for current job to finish
	while(!(TWCR & (1<<TWINT)));
	
	twst = TWSR & 0xF8;
	//while((TWSR & 0xF8) != 0x18);
	if(twst == 0x28){
	
/*	DDRD = 0x00;
    PORTD = 0xFF;
    DDRB = 0xFF;
    PORTB |= (1<<1);
*/		
		return 0; // ack received
	}
	
	if(twst == 0x30){
		return 1;	// nack received		

	} else {
		DDRD = 0x00;
	    PORTD = 0xFF;
	    DDRB = 0xFF;
    	PORTB |= (1<<1);


		return 2;	// Data transmission failed
	}
	
}

/*void TWI_write_data(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);	// Clear TWI interrupt, enable TWI
	while(!(TWCR & (1<<TWINT)));	// Wait till TWDR complete byte transmitted
	while((TWSR & 0xF8) != 0x28);	// Check for the acknoledgment
}*/

void TWI_stop(void)
{
	//Clear TWI interrupt flag, SDA stop condition, Enable TWI
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); 
	while(!(TWCR & (1<<TWSTO)));	// Wait until stop condition is transmitted 
}


