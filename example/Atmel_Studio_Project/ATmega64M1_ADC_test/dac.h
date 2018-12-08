/**
* @file dac.h
* @author Christoph Jurczyk
* @date December 08, 2018
* @brief Header file for DAC communication
*
*
* @section license License
* This library is released under the GNU General Public License v3.0.
*
*/

#ifndef DAC_H_
#define DAC_H_

// ##### Includes #####
#include <avr/io.h>
#include <stdio.h>


// ##### Definitions #####
/**
	*
	* \enum    DAC_REF
	*
	* \brief   Enum class for possible DAC Vref Selection Bits
**/
enum DAC_REF {
	/// External Vref on AREF pin, Internal Vref is switched off
	DAC_EXTERNAL_REF,	
	/// AVcc with external capacitor connected on the AREF pin
	DAC_INTERNAL_VCC_EXT_CAP,
	/// AVcc (no external capacitor connected on the AREF pin)
	DAC_INTERNAL_VCC_REF,
	/// Internal 2.56V reference voltage with external capacitor connected on the AREF pin
	DAC_INTERAL_2V56_CAP,
	/// Internal 2.56V reference voltage
	DAC_INTERNAL_2V56
	};
	
	
// ##### Functions #####
void dacReference(DAC_REF mode);
DAC_REF dacGetReference(void);
void dacInit(void);
void dacWrite(uint16_t value);


#endif /* DAC_H_ */