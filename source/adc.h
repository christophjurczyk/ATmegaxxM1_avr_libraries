/**
* @file adc.h
* @author Christoph Jurczyk
* @date December 07, 2018
* @brief Header file for ADC communication
*
*
* @section license License
* This library is released under the GNU General Public License v3.0.
*
*/

#ifndef ADC_H_
#define ADC_H_

// ##### Includes #####
#include <avr/io.h>
#include <stdio.h>


// ##### Definitions #####
/**
 *
 * \enum    ADC_REF
 *
 * \brief   Enum class for possible ADC Vref Selection Bits
**/
enum ADC_REF {
	/// External Vref on AREF pin, Internal Vref is switched off
	ADC_EXTERNAL_REF,	
	/// AVcc with external capacitor connected on the AREF pin
	ADC_INTERNAL_VCC_EXT_CAP,
	/// AVcc (no external capacitor connected on the AREF pin)
	ADC_INTERNAL_VCC_REF,
	/// Internal 2.56V reference voltage with external capacitor connected on the AREF pin
	ADC_INTERAL_2V56_CAP,
	/// Internal 2.56V reference voltage
	ADC_INTERNAL_2V56
	};
	

/**
 *
 * \enum    ADC_CLK_DIV
 *
 * \brief   Enum class for possible ADC Prescaler Selection Bits
**/
enum ADC_CLK_DIV {
	/// Clock divider: 2
	ADC_CLK_DIV_2,		
	/// Clock divider: 4
	ADC_CLK_DIV_4,		
	/// Clock divider: 8
	ADC_CLK_DIV_8,		
	/// Clock divider: 16
	ADC_CLK_DIV_16,		
	/// Clock divider: 32
	ADC_CLK_DIV_32,		
	/// Clock divider: 64
	ADC_CLK_DIV_64,		
	/// Clock divider: 128
	ADC_CLK_DIV_128,	
	};


/**
 *
 * \enum    ADC_CH
 *
 * \brief   Enum class for possible ADC Input Channel Selection
**/
enum ADC_CH {
	ADC0 = 0,
	ADC1 = 1,
	ADC2 = 2,
	ADC3 = 3,
	ADC4 = 4,
	ADC5 = 5,
	ADC6 = 6,
	ADC7 = 7,
	ADC8 = 8,
	ADC9 = 9,
	ADC10 = 10,
	VCC_4 = 12,
	AMP0 = 14,
	AMP1 = 15,
	AMP2 = 16,
	BANDGAP = 17,
	GND = 18,		
	};
	
/**
 *
 * \enum    ADC_GAIN
 *
 * \brief   Enum class for possible ADC Input Gain Selection
**/
enum ADC_GAIN {
	ADC_GAIN5  = 0,
	ADC_GAIN10 = 1,
	ADC_GAIN20 = 2,
	ADC_GAIN40 = 3,
	};
	

// ##### Functions #####
void adcReference(ADC_REF mode);
void adcInit(ADC_CLK_DIV clk_div_value);
uint16_t adcRead(ADC_CH channel);
int16_t adcReadDiff(ADC_CH channel, ADC_GAIN gain);
int8_t adcTempRead(void);
void adcTempOffset(int8_t offset);
ADC_REF adcGetReference(void);


#endif /* ADC_H_ */