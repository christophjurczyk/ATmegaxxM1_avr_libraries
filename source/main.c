/**
* @file main.c
* @author Christoph Jurczyk
* @data October 21, 2018
* @brief Main file for ATmega64M1 UART example.
*
*/

#define F_CPU 8000000UL

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"

// UART initialization
#define BAUDRATE 115200 // define desired baudrate
FILE uart_str = FDEV_SETUP_STREAM(uart_transmit,uart_receive,_FDEV_SETUP_RW);



int main(void)
{
	stdout = stdin = &uart_str;
	uart_init(BAUD_CALC(BAUDRATE));
	
	char read_buffer[256];
	
    while (1) 
    {
		// Print line
		printf("Hi, the number is %d!\n", 10);
		
		// Read line
		while(uart_getline(read_buffer, 256) != EOF)
		printf("You typed \"%s\"\n", read_buffer);
		
    }
}

