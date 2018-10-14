/* --------------------------------------------------------------
	UART Library for the ATmega16M1/ATmega32M1/ATmega64M1
	
	Author: Christoph Jurczyk
-------------------------------------------------------------- */

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/sfr_defs.h>
#include "uart.h"

// Initialization function of UART
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

// Function to transmit
int uart_transmit(char byte_data, FILE *stream)
{
	while (LINSIR & _BV(LBUSY));  // wait for free buffer	
	LINDAT = byte_data;
	return 0;
}

// Function read characters
int uart_receive(FILE *stream)
{
	while (LINSIR & _BV(LBUSY));  // wait for free buffer	
	loop_until_bit_is_set(LINSIR, LRXOK);
	return LINDAT;
}

// Function read line
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