/**
\brief VESNA SNC-STM32 definition of the RCC.

\author Chang Tengfei <tengfei.chang@gmail.com>,  July 2012.
*/

#ifndef __RCC_H
#define __RCC_H

//=========================== defines =========================================
/* SNC SysClock frequency type define */
typedef enum {
	SNC_CLOCK_8MHZ  = 8000000,
	SNC_CLOCK_12MHZ = 12000000,
	SNC_CLOCK_16MHZ = 16000000,
	SNC_CLOCK_20MHZ = 20000000,
	SNC_CLOCK_24MHZ = 24000000,
	SNC_CLOCK_28MHZ = 28000000,
	SNC_CLOCK_32MHZ = 32000000,
	SNC_CLOCK_36MHZ = 36000000,
	SNC_CLOCK_40MHZ = 40000000,
	SNC_CLOCK_44MHZ = 44000000,
	SNC_CLOCK_48MHZ = 48000000,
	SNC_CLOCK_52MHZ = 52000000,
	SNC_CLOCK_56MHZ = 56000000,
	SNC_CLOCK_60MHZ = 60000000,
	SNC_CLOCK_64MHZ = 64000000,
} SNC_Clock;
//=========================== variables =======================================

//=========================== prototypes ======================================

void RCC_Configuration(SNC_Clock freq);

void RCC_Wakeup(void);

#endif
