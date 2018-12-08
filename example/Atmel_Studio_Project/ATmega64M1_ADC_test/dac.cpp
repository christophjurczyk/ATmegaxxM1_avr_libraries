/**
* @file dac.cpp
* @author Christoph Jurczyk
* @date December 07, 2018
* @brief This file contains all functions for the DAC communication of the ATmega64M1
*
*/


#include <avr/io.h>
#include "dac.h"


/**
* @brief Function to set the ADC/DAC voltage reference selection
* The configuration of the voltage reference selection is applied to the ADC and DAC. 
* Independent voltage references are not possible.
*
* @param mode
* Is the the desired mode of the ADC/DAC according to ::DAC_REF
*/
void dacReference(DAC_REF mode)
{
	switch(mode)
	{	
		case DAC_EXTERNAL_REF:
		ADMUX &= !((1 << REFS1)|(1 << REFS0));
		ADCSRB &= !(1 << ISRCEN);
		ADCSRB |= (1 << AREFEN);
		break;
		
		case DAC_INTERNAL_VCC_EXT_CAP:
		ADMUX &= !((1 << REFS1));
		ADMUX |= (1 << REFS0);
		ADCSRB &= !(1 << ISRCEN);
		ADCSRB |= (1 << AREFEN);
		break;
		
		case DAC_INTERNAL_VCC_REF:
		ADMUX &= !((1 << REFS1));
		ADMUX |= (1 << REFS0);
		ADCSRB &= !(1 << ISRCEN);
		ADCSRB &= !(1 << AREFEN);
		break;
		
		case DAC_INTERAL_2V56_CAP:
		ADMUX |= ((1 << REFS1)|(1 << REFS0));
		ADCSRB &= !(1 << ISRCEN);
		ADCSRB |= (1 << AREFEN);
		break;
		
		case DAC_INTERNAL_2V56:
		ADMUX |= ((1 << REFS1)|(1 << REFS0));
		ADCSRB &= !(1 << AREFEN);
		break;
	}
}


/**
* @brief Function to read the current ADC/DAC voltage reference selection
*
* @return Returns the ADC/DAC voltage reference selection as ::DAC_REF
*/
DAC_REF dacGetReference(void)
{
	uint8_t ref_value = ((ADMUX & ((1 << REFS1)|(1 << REFS0))) >> REFS0); // shift REFS1/0 bits to the right

	switch(ref_value)
	{
		case 0:
		return DAC_EXTERNAL_REF;
		break;
		
		case 1:
		if(ADCSRB & (1 << AREFEN))
		{
			return DAC_INTERNAL_VCC_EXT_CAP;
			} else {
			return DAC_INTERNAL_VCC_REF;
		}
		break;
		
		case 3:
		if(ADCSRB & (1 << AREFEN))
		{
			return DAC_INTERAL_2V56_CAP;
			} else {
			return DAC_INTERNAL_2V56;
		}
		break;
	}
	
	return DAC_EXTERNAL_REF;
}

/**
* @brief Function to initialize DAC
*/
void dacInit(void)
{
	// Set DAC to right adjust mode
	DACON &= ~(1 << DALA);
	// Enable DAC and set as output
	DACON |= ((1 << DAEN)|(1 << DAOE));
}

/**
* @brief Function write value to DAC
*
* @param value 
* Is the desired value (0-1023) of the DAC output.
*/
void dacWrite(uint16_t value)
{
	// Write value to DAC
	DACL = (uint8_t)value;
	DACH = (uint8_t)((value >> 8) & 0x03);
}