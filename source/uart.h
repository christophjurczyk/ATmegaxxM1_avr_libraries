/**
* @file uart.h
* @author Christoph Jurczyk
* @data October 21, 2018
* @brief Header file for UART communication.
*
* \mainpage Description
* This is the documentation for the UART library for the ATmega16M1, ATmega32M1 and ATmega64M1.
*
* @section license License
* This library is released under the GNU General Public License v3.0.
*
*/


#ifndef UART_H_
#define UART_H_

// ##### Includes #####
#include <avr/io.h>
#include <stdio.h>


// ##### Definitions #####
/** Numbers of samples per bit. */
#define UART_LBT 8
/** Calculation of LINBRR value for UART initialization. */
#define BAUD_CALC(baud) ((F_CPU / 4 / baud - 1) / 2)


// ##### Functions #####
void uart_init(uint8_t brr_value);
int uart_transmit(char byte_data, FILE *stream);
int uart_receive(FILE *stream);
int uart_getline(char line[], int max);


#endif /* UART_H_ */