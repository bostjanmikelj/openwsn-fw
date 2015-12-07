/**
\brief VESNA SNC-STM32 definition of the RCC.

\author Bostjan Mikelj,  September 2015.
*/
#include "stm32f10x_lib.h"
#include "rcc.h"
//=========================== defines =========================================

//=========================== variables =======================================

//=========================== prototypes ======================================

//=========================== public ==========================================

void RCC_Configuration(SNC_Clock freq)
{
	uint32_t multiplier;
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();
	//todo start with HSI
	FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_Disable);
	/* Disable Clock Security System(CSS) external clock not used */
	RCC_ClockSecuritySystemCmd(DISABLE);
	switch (freq){
	case SNC_CLOCK_8MHZ:
	{
		/* Disable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Disable);
		/* No PLL, direct HSI */
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 8MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1);  	/* PCLK2 = HCLK/1 = 8MHz */
		RCC_PCLK1Config(RCC_HCLK_Div1);  	/* PCLK1 = HCLK/1 = 8MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 1MHz */
		/* Flash 0 wait state */
		FLASH_SetLatency(FLASH_Latency_0);
		FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_Enable);
		return;
	}

	case SNC_CLOCK_12MHZ:
	{
		multiplier = RCC_PLLMul_3;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 12MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1);  	/* PCLK2 = HCLK/1 = 12MHz */
		RCC_PCLK1Config(RCC_HCLK_Div1);  	/* PCLK1 = HCLK/1 = 12MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	/* ADCCLK = HCLK/8 = 1,5MHz */
		/* Flash 0 wait state */
		FLASH_SetLatency(FLASH_Latency_0);
		break;
	}
	case SNC_CLOCK_16MHZ:
	{
		multiplier = RCC_PLLMul_4;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 16MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 16MHz */
		RCC_PCLK1Config(RCC_HCLK_Div1); 	/* PCLK1 = HCLK/1 = 16MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 2MHz */
		/* Flash 0 wait state */
		FLASH_SetLatency(FLASH_Latency_0);
		break;
	}
	case SNC_CLOCK_20MHZ:
	{
		multiplier = RCC_PLLMul_5;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1);	/* HCLK = SYSCLK = 20MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 20MHz */
		RCC_PCLK1Config(RCC_HCLK_Div1); 	/* PCLK1 = HCLK/1 = 20MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 2,5MHz */
		/* Flash 0 wait state */
		FLASH_SetLatency(FLASH_Latency_0);
		break;
	}
	case SNC_CLOCK_24MHZ:
	{
		multiplier = RCC_PLLMul_6;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 24MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 24MHz */
		RCC_PCLK1Config(RCC_HCLK_Div1); 	/* PCLK1 = HCLK/1 = 24MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 3MHz */
		/* Flash 0 wait state */
		FLASH_SetLatency(FLASH_Latency_0);
		break;
	}
	case SNC_CLOCK_28MHZ:
	{
		multiplier = RCC_PLLMul_7;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 28MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 28MHz */
		RCC_PCLK1Config(RCC_HCLK_Div1); 	/* PCLK1 = HCLK/1 = 28MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 3,5MHz */
		/* Flash 1 wait state */
		FLASH_SetLatency(FLASH_Latency_1);
		break;
	}
	case SNC_CLOCK_32MHZ:
	{
		multiplier = RCC_PLLMul_8;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 32MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 32MHz */
		RCC_PCLK1Config(RCC_HCLK_Div1); 	/* PCLK1 = HCLK/1 = 32MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 4MHz */
		/* Flash 1 wait state */
		FLASH_SetLatency(FLASH_Latency_1);
		break;
	}
	case SNC_CLOCK_36MHZ:
	{
		multiplier = RCC_PLLMul_9;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 36MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 36MHz */
		RCC_PCLK1Config(RCC_HCLK_Div1); 	/* PCLK1 = HCLK/1 = 36MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 4,5MHz */
		/* Flash 1 wait state */
		FLASH_SetLatency(FLASH_Latency_1);
		break;
	}
	case SNC_CLOCK_40MHZ:
	{
		multiplier = RCC_PLLMul_10;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 40MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 40MHz */
		RCC_PCLK1Config(RCC_HCLK_Div2); 	/* PCLK1 = HCLK/2 = 20MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 5MHz */
		/* Flash 1 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		break;
	}
	case SNC_CLOCK_44MHZ:
	{
		multiplier = RCC_PLLMul_11;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 44MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 44MHz */
		RCC_PCLK1Config(RCC_HCLK_Div2); 	/* PCLK1 = HCLK/2 = 22MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 5,5MHz */
		/* Flash 1 wait state */
		FLASH_SetLatency(FLASH_Latency_1);
		break;
	}
	case SNC_CLOCK_48MHZ:
	{
		multiplier = RCC_PLLMul_12;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 48MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 48MHz */
		RCC_PCLK1Config(RCC_HCLK_Div2); 	/* PCLK1 = HCLK/2 = 24MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 6MHz */
		/* Flash 1 wait state */
		FLASH_SetLatency(FLASH_Latency_1);
		break;
	}
	case SNC_CLOCK_52MHZ:
	{
		multiplier = RCC_PLLMul_13;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 52MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 52MHz */
		RCC_PCLK1Config(RCC_HCLK_Div2); 	/* PCLK1 = HCLK/2 = 26MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 6,5MHz */
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		break;
	}
	case SNC_CLOCK_56MHZ:
	{
		multiplier = RCC_PLLMul_14;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 56MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 56MHz */
		RCC_PCLK1Config(RCC_HCLK_Div2); 	/* PCLK1 = HCLK/2 = 28MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 7MHz */
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		break;
	}
	case SNC_CLOCK_60MHZ:
	{
		multiplier = RCC_PLLMul_15;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 60MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 60MHz */
		RCC_PCLK1Config(RCC_HCLK_Div2); 	/* PCLK1 = HCLK/2 = 30MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 7,5MHz */
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		break;
	}
	case SNC_CLOCK_64MHZ:
	{
		multiplier = RCC_PLLMul_16;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 64MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 64MHz */
		RCC_PCLK1Config(RCC_HCLK_Div2); 	/* PCLK1 = HCLK/2 = 32MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 8MHz */
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		break;
	}
	default:
	{
		/*Set clock to 16MHZ*/
		multiplier = RCC_PLLMul_4;
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 16MHZ */
		RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 16MHz */
		RCC_PCLK1Config(RCC_HCLK_Div1); 	/* PCLK1 = HCLK/1 = 16MHz */
		RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 2MHz */
		/* Flash 0 wait state */
		FLASH_SetLatency(FLASH_Latency_0);
	}

	}
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, multiplier);
	RCC_PLLCmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}
	/* Select PLL as system clock source */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x08);
	//enable AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

//when wakeup by alarm, configure rcc
void RCC_Wakeup(void)
{
	//do nothing using HSI
}

