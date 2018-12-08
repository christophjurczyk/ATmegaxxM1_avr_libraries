/**
* @file main.cpp
* @author Christoph Jurczyk
* @date December 08, 2018
* @brief Main file for ATmega64M1 UART, ADC, DAC example.
*
* 
* \mainpage Description
* This is the documentation for the UART, ADC, DAC libraries for the ATmega16M1, ATmega32M1 and ATmega64M1.
*
* Note: Floating point is only used for showing
* the functionality in example main.cpp. For professional use
* it is recommend to use integer values.
*
* @section license License
* This library is released under the GNU General Public License v3.0.
*
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
#include "adc.h"
#include "dac.h"

extern "C" {
	#include "uart.h"	
};

// UART initialization
#define BAUDRATE 115200 // define desired baudrate
FILE uart_str;

// VCC declaration
#define VCC 5.0

// Function declaration
void hw_config(void);


int main(void)
{
    // Variable declaration
    uint16_t adc_value;
	int8_t temp_value;
	int16_t adc_diff_value;
	uint16_t dac_value = 0;
		
	// Hardware configuration
	hw_config();
    	
    while (1)
    {	    	
		printf("\nNew data:\n");
			
		// Read VCC/4 via ADC
		adc_value = adcRead(VCC_4);
		fprintf(&uart_str, "VCC/4= %.4fV\n", adc_value*VCC/1024.0);
			
		// Read internal temperature via ADC
		temp_value = adcTempRead();
		fprintf(&uart_str, "Temp= %d degC\n", temp_value);
			
		// Read differential voltage via ADC
		adc_diff_value = adcReadDiff(AMP0,ADC_GAIN5);
		fprintf(&uart_str, "adc_diff_value= %.4fV\n", adc_diff_value/512.0);
			
		// Write DAC value
		fprintf(&uart_str, "dac_value= %d (%.4fV)\n", dac_value, dac_value*VCC/1024.0);
		dacWrite(dac_value);
		dac_value++;
		if (dac_value > 1023) dac_value = 0;
			
		// Wait a second
		_delay_ms(1000);	    	
    }
}


void hw_config()
{
	// UART
	uart_str.put = uart_transmit;
	uart_str.get = uart_receive;
	uart_str.flags = _FDEV_SETUP_RW;

	stdout = stdin = &uart_str;
	uart_init(BAUD_CALC(BAUDRATE));
	printf("\n\n\nStarting ADC example...\n");
	
	// ADC
	adcReference(ADC_INTERNAL_VCC_REF);
	adcInit(ADC_CLK_DIV_64);
	adcTempOffset(10); // Offset correction of internal temperature sensor. Depending on hardware, mine needs +10 degC.
	
	// DAC
	dacInit();
}