/**
* @file adc.cpp
* @author Christoph Jurczyk
* @date December 07, 2018
* @brief This file contains all functions for the ADC communication of the ATmega64M1
*
*/

#include <avr/io.h>
#include "adc.h"

/** Offset correction parameter for internal temperature sensor */
int8_t temp_offset = 0;

/**
* @brief Function to set the ADC/DAC voltage reference selection
* The configuration of the voltage reference selection is applied to the ADC and DAC.
* Independent voltage references are not possible.
*
* @param mode
* Is the the desired mode of the ADC/DAC according to ::ADC_REF
*/
void adcReference(ADC_REF mode)
{
	switch(mode)
	{
		case ADC_EXTERNAL_REF:
			ADMUX &= !((1 << REFS1)|(1 << REFS0));
			ADCSRB &= !(1 << ISRCEN);
			ADCSRB |= (1 << AREFEN);
		break;
		
		case ADC_INTERNAL_VCC_EXT_CAP:
			ADMUX &= !((1 << REFS1));
			ADMUX |= (1 << REFS0);
			ADCSRB &= !(1 << ISRCEN);
			ADCSRB |= (1 << AREFEN);
		break;
		
		case ADC_INTERNAL_VCC_REF:
			ADMUX &= !((1 << REFS1));
			ADMUX |= (1 << REFS0);
			ADCSRB &= !(1 << ISRCEN);
			ADCSRB &= !(1 << AREFEN);
		break;
		
		case ADC_INTERAL_2V56_CAP:
			ADMUX |= ((1 << REFS1)|(1 << REFS0));
			ADCSRB &= !(1 << ISRCEN);
			ADCSRB |= (1 << AREFEN);
		break;
		
		case ADC_INTERNAL_2V56:
			ADMUX |= ((1 << REFS1)|(1 << REFS0));
			ADCSRB &= !(1 << AREFEN);
		break;	
	}	
}



/**
* @brief Function to initialize ADC
*
* @param clk_div_value
* Is the the desired clock divider according to ::ADC_CLK_DIV
*/
void adcInit(ADC_CLK_DIV clk_div_value)
{
	// Set clock divider
	switch(clk_div_value)
	{		
		case ADC_CLK_DIV_2:
			ADCSRA &= !((1 << ADPS2)||(1 << ADPS1)||(1 << ADPS0));
		break;
		
		case ADC_CLK_DIV_4:
			ADCSRA &= !((1 << ADPS2)||(1 << ADPS0));
			ADCSRA |= (1 << ADPS1);
		break;
		
		case ADC_CLK_DIV_8:
			ADCSRA &= !(1 << ADPS2);
			ADCSRA |= (1 << ADPS1)||(1 << ADPS0);
		break;
		
		case ADC_CLK_DIV_16:
			ADCSRA &= !((1 << ADPS1)||(1 << ADPS0));
			ADCSRA |= (1 << ADPS2);
		break;
		
		case ADC_CLK_DIV_32:
			ADCSRA &= !(1 << ADPS1);
			ADCSRA |= (1 << ADPS2)||(1 << ADPS0);
		break;
		
		case ADC_CLK_DIV_64:
			ADCSRA &= !(1 << ADPS0);
			ADCSRA |= (1 << ADPS2)||(1 << ADPS1);
		break;
		
		case ADC_CLK_DIV_128:
			ADCSRA |= (1 << ADPS2)||(1 << ADPS1)||(1 << ADPS0);
		break;
	}
	
	// Enable ADC
	ADCSRA |= (1 << ADEN);
	
	// Dummy readout to prevent further error readings
	ADCSRA |= (1 << ADSC);
	while ( ADCSRA & (1 << ADSC)){}
	(void) ADCW;
}


/**
* @brief Function to read ADC value
*
* @param channel
* Is the the desired ADC channel according to ::ADC_CH
*
* @return Returns the value of the channel
*/
uint16_t adcRead(ADC_CH channel)
{
	// Select channel
	ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
	// Start conversion
	ADCSRA |= (1 << ADSC);
	// Wait for conversion finish
	while ( ADCSRA & (1 << ADSC)){}
	// Return value
	return ADCW;
}



/**
* @brief Function to read differential ADC value
*
* @param channel
* Is the the desired ADC channel according to ::ADC_CH
*
* @return Returns the value of the channel
*/
int16_t adcReadDiff(ADC_CH channel, ADC_GAIN gain)
{
	// Configure amplifier
	switch(channel)
	{
		case AMP0:
			AMP0CSR |= (1 << AMP0EN);
			switch(gain)
			{
				case ADC_GAIN5:
					AMP0CSR &= ~((1 << AMP0G1) | (1 << AMP0G0));
				break;
				
				case ADC_GAIN10:
					AMP0CSR &= ~(1 << AMP0G1);
					AMP0CSR |= (1 << AMP0G0);
				break;
				
				case ADC_GAIN20:
					AMP0CSR &= ~(1 << AMP0G0);
					AMP0CSR |= (1 << AMP0G1);
				break;
				
				case ADC_GAIN40:
					AMP0CSR |= (1 << AMP0G1) | (1 << AMP0G0);
				break;
			}			
		break;
		
		case AMP1:
			AMP1CSR |= (1 << AMP1EN);
			switch(gain)
			{
				case ADC_GAIN5:
				AMP1CSR &= ~((1 << AMP1G1) | (1 << AMP1G0));
				break;
				
				case ADC_GAIN10:
				AMP1CSR &= ~(1 << AMP1G1);
				AMP1CSR |= (1 << AMP1G0);
				break;
				
				case ADC_GAIN20:
				AMP1CSR &= ~(1 << AMP1G0);
				AMP1CSR |= (1 << AMP1G1);
				break;
				
				case ADC_GAIN40:
				AMP1CSR |= (1 << AMP1G1) | (1 << AMP1G0);
				break;
			}
		break;
		
		case AMP2:
			AMP2CSR |= (1 << AMP2EN);
			switch(gain)
			{
				case ADC_GAIN5:
				AMP2CSR &= ~((1 << AMP2G1) | (1 << AMP2G0));
				break;
				
				case ADC_GAIN10:
				AMP2CSR &= ~(1 << AMP2G1);
				AMP2CSR |= (1 << AMP2G0);
				break;
				
				case ADC_GAIN20:
				AMP2CSR &= ~(1 << AMP2G0);
				AMP2CSR |= (1 << AMP2G1);
				break;
				
				case ADC_GAIN40:
				AMP2CSR |= (1 << AMP2G1) | (1 << AMP2G0);
				break;
			}
		break;
		
		default:
			return 0;
		break;
	}	
	// Select channel
	ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);	
	// Start conversion
	ADCSRA |= (1 << ADSC);
	// Wait for conversion finish
	while ( ADCSRA & (1 << ADSC)){}
	// Return value
	if (ADCW > 0x1FF)
	{
		return ADCW - 0x3FF;
	} 
	else
	{
		return ADCW;
	}
	
	
}

/**
* @brief Function to read the current ADC/DAC voltage reference selection
*
* @return Returns the ADC/DAC voltage reference selection as ::ADC_REF
*/
ADC_REF adcGetReference(void)
{
	uint8_t ref_value = ((ADMUX & ((1 << REFS1)|(1 << REFS0))) >> REFS0); // shift REFS1/0 bits to the right

	switch(ref_value)
	{
		case 0:
			return ADC_EXTERNAL_REF;
		break;
			
		case 1:
			if(ADCSRB & (1 << AREFEN))
			{
				return ADC_INTERNAL_VCC_EXT_CAP;
			} else {
				return ADC_INTERNAL_VCC_REF;
			}			
		break;
		
		case 3:
			if(ADCSRB & (1 << AREFEN))
			{
				return ADC_INTERAL_2V56_CAP;
			} else {
				return ADC_INTERNAL_2V56;
			}
		break;		
	}
	
	return ADC_EXTERNAL_REF;
}

/**
* @brief Function to read internal temperature sensor
*
* @return Returns the internal temperature in DegC
*/
int8_t adcTempRead(void)
{
	// Store previous reference selection
	ADC_REF prevRefMode = adcGetReference();
	// Switch to internal reference
	adcReference(ADC_INTERNAL_2V56);
	
	// Read temperature
	// Select channel
	ADMUX = (ADMUX & ~(0x1F)) | (11 & 0x1F);
	
	// wait for multiplexer
	uint8_t volatile i;	
	for (i=0; i<255; i++);
	
	// Read multiple value from ADC to reduce noise
	uint32_t sum = 0;
	uint8_t nsamples = 100;
		
	for (uint8_t i = 0; i < nsamples; ++i ) {
	// Start conversion
	ADCSRA |= (1 << ADSC);
	// Wait for conversion finish
	while ( ADCSRA & (1 << ADSC)){}
		sum += ADCW;
	}
		
	
	// Convert to degC
	int16_t temperature = sum/nsamples - 280 + temp_offset;
	
	// Restore previous reference selection
	adcReference(prevRefMode);
	
	// Return value
	return (int8_t) temperature;
}


/**
* @brief Function to set a offset correction of internal temperature measurement
* Parameter should be stored in EEPROM and configured on startup with this function.
*
* @param offset
* Is the the desired offset in degC
*/
void adcTempOffset(int8_t offset)
{
	temp_offset = offset;
}