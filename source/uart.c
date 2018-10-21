/**
* @file uart.c
* @author Christoph Jurczyk
* @data October 21, 2018
* @brief This file contains all functions for the UART communication.
*
*/

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/sfr_defs.h>
#include "uart.h"

/**
* @brief UART initialization function
* 
* To initialize the UART connection call this function with the desired LINBRR value, which can be calculated wit the following command:
* @code
* BAUD_CALC(9600)
* @endcode
* @note The baudrate can be change to your desired baudrate.
* 
* Call the initialization function as follow:
* @code
* uart_init(BAUD_CALC(9600));
* @endcode
*/
void uart_init(uint8_t brr_value)
{
	LINBTR = _BV(LDISR); // Clear LINBTR and set bit timing re-synchronization enabled
	LINBTR |= UART_LBT; // Set LIN Bit Timing
	LINBRR = brr_value; // Set scaling of system clock
	
	while (LINSIR & _BV(LBUSY)); // Wait until LIN is ready
	
	LINCR = _BV(LENA);  // Clear LINCR and enable byte transfer mode
	LINCR |= _BV( LCMD2) | _BV( LCMD1) | _BV( LCMD0);  // Set UART to full duplex
	PORTD |= _BV( PORTD4); // Enable pull-up on RX
	LINENIR |= _BV(LENRXOK) | _BV(LENTXOK); // Enable Transmit and Receive Performed Interrupt
}

/**
* @brief Function to transmit characters.
* 
* Call this function with a character or character array to transmit data via the UART connection.
* Example call:
* @code
* uart_transmit('a');
* @endcode
*
* @param byte_data
* Is the to transmitted data e.g. a character.
*
* @param stream
* Is an optional parameter for the FDEV_SETUP_STREAM.
*
* @return Returns a 0 after successful transmission. This is necessary for the optional use in FDEV_SETUP_STREAM.
*/
int uart_transmit(char byte_data, FILE *stream)
{
	while (LINSIR & _BV(LBUSY));  // wait for free buffer	
	LINDAT = byte_data;
	return 0;
}

/**
* @brief Function to read characters.
* 
* Call this function to read a character from the UART buffer.
* Example call:
* @code
* char a = uart_receive();
* @endcode
*
* @param stream
* Is an optional parameter for the FDEV_SETUP_STREAM.
*
* @return Returns the character.
*/
int uart_receive(FILE *stream)
{
	while (LINSIR & _BV(LBUSY));  // wait for free buffer	
	loop_until_bit_is_set(LINSIR, LRXOK);
	return LINDAT;
}

/**
* @brief Function to read line.
* 
* Call this function to read a string until '\n' termination. 
* Example call:
* @code
* char read_buffer[256];
* while(uart_getline(read_buffer, 256) != EOF)
* @endcode
*
* @param line
* Is the buffer for the read line.
*
* @param max
* Maximum number of receiving characters.
*
* @return Returns numbers of received characters or EOF flag.
*/
int uart_getline(char line[], int max)
{
	int nch = 0;
	int c;
	max = max - 1;

	while((c = getchar()) != EOF)
	{
		if(c == '\n')
		break;

		if(nch < max)
		{
			line[nch] = c;
			nch = nch + 1;
		}
	}

	if(c == EOF && nch == 0)
	return EOF;

	line[nch] = '\0';
	return nch;
}