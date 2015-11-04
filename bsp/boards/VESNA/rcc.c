/**
\brief VESNA SNC-STM32 definition of the RCC.

\author Bostjan Mikelj,  September 2015.
*/
#include "stm32f10x_lib.h"
//=========================== defines =========================================

//=========================== variables =======================================

//=========================== prototypes ======================================

//=========================== public ==========================================

void RCC_Configuration(void)
{
	uint32_t multiplier;
    //ErrorStatus HSEStartUpStatus;
  
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();
    //todo start with HSI
    FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_Disable);
    /* Disable Clock Security System(CSS) external clock not used */
    RCC_ClockSecuritySystemCmd(DISABLE);
    /* Set clock to 16Mhz*/
    multiplier = RCC_PLLMul_4;
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 	/* HCLK = SYSCLK = 16MHZ */
    RCC_PCLK2Config(RCC_HCLK_Div1); 	/* PCLK2 = HCLK/1 = 16MHz */
    RCC_PCLK1Config(RCC_HCLK_Div1); 	/* PCLK1 = HCLK/1 = 16MHz */
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);	/* ADCCLK = HCLK/8 = 2MHz */
    /* Flash 0 wait state */
    FLASH_SetLatency(FLASH_Latency_0);
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, multiplier);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while(RCC_GetSYSCLKSource() != 0x08);
//    /* Enable HSE */
//    RCC_HSEConfig(RCC_HSE_Bypass);	//use external high speed oscillator from SNR-Trx board //todo (probably set pins PD0 and PD1 as input)
//
//    /* Wait till HSE is ready */
//    HSEStartUpStatus = RCC_WaitForHSEStartUp();
//
//    if(HSEStartUpStatus == SUCCESS)
//    {
//      /* Enable Prefetch Buffer */
//      FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
//
//      /* Flash 2 wait state */
//      FLASH_SetLatency(FLASH_Latency_2);
//
//      /* HCLK = SYSCLK */
//      RCC_HCLKConfig(RCC_SYSCLK_Div1);
//
//      /* PCLK2 = HCLK */
//      RCC_PCLK2Config(RCC_HCLK_Div1);
//
//      /* PCLK1 = HCLK/2 */
//      RCC_PCLK1Config(RCC_HCLK_Div2);
//
//      /* PLLCLK = 16MHz / 2 * 9 = 72 MHz */
//      RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);
//
//      /* Enable PLL */
//      RCC_PLLCmd(ENABLE);
//
//      /* Wait till PLL is ready */
//      while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
//      {
//      }
//
//      /* Select PLL as system clock source */
//      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//
//      /* Wait till PLL is used as system clock source */
//      while(RCC_GetSYSCLKSource() != 0x08)
//      {
//      }
//    }
    
    //enable AFIO 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

//when wakeup by alarm, configure rcc
void RCC_Wakeup(void)
{
    ErrorStatus HSEStartUpStatus;

    //enable HSE
    RCC_HSEConfig(RCC_HSE_ON);
    //Wait till HSE is ready
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if(HSEStartUpStatus == SUCCESS)
    {
      //enable PLL
      RCC_PLLCmd(ENABLE);
      //Wait till PLL is ready
      while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
      {}

      // Select PLL as system clock source
      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

      //Wait till PLL is used as system clock source
      while(RCC_GetSYSCLKSource() != 0x08)
      {}
   }
}

