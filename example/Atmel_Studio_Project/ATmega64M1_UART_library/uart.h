/* --------------------------------------------------------------
	UART Library for the ATmega16M1/ATmega32M1/ATmega64M1
	
	Author: Christoph Jurczyk
	Version: 1.0
	Changelog:
	1.0		14.10.18:		Initial Upload
-------------------------------------------------------------- */


#ifndef UART_H_
#define UART_H_

// ##### Includes #####
#include <avr/io.h>
#include <stdio.h>


// ##### Definitions #####
#define UART_LBT 8 // Numbers of samples of a bit
#define BAUD_CALC(baud) ((F_CPU / 4 / baud - 1) / 2) // Returns brr_value for uart_init()


// ##### Functions #####
void uart_init(uint8_t brr_value);
int uart_transmit(char byte_data, FILE *stream);
int uart_receive(FILE *stream);
int uart_getline(char line[], int max);


#endif /* UART_H_ */