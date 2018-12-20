/*
*	Author: Connor Kreider
*
*	This file includes the functions needed for the reciever.
*	Includes recieveing signals from the Rx and Tx of the BLUESMiRF,
*	and setting up i2c for the MCP4725 DAC communication
*
*
*/

#ifndef RECIEVER_H
#define RECIEVER_H

//For UART
#define FOSC 1843200
#define BAUD 9600
#define MYBURR FOSC/16/BAUD-1

unsigned char USART_receive(void)
{
	// Wait for an empty transmit buffer
	while(!(UCSRnA & (1<<UDREn)));

	// Put data recieved into the buffer that sends data
	UDRn = data;

	// Wait for data to be received
	while(!(UCSRnA & (1<<RXCn);

	// Return data recieved
	return UDRn;

}
