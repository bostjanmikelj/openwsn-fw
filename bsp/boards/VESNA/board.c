/**
\brief VESNA-SNC definition of the "board" bsp module.

\author Bostjan Mikelj, September 2015.
*/
#include "stm32f10x_lib.h"
#include "board.h"
// bsp modules
#include "leds.h"
#include "uart.h"
#include "spi.h"
#include "bsp_timer.h"
#include "radio.h"
#include "radiotimer.h"
#include "rcc.h"
#include "nvic.h"
#include "debugpins.h"
#include "opentimers.h"
#include "gpio.h"
#include "board.h"

static __IO uint32_t boardTimingDelayMS = 0;
//=========================== private functions ==============================

//=========================== main ============================================

extern int mote_main(void);

int main(void)
{
 return mote_main();
}

//=========================== public ==========================================

void board_init()
{
  RCC_Configuration(SNC_CLOCK_32MHZ);//Configure rcc
  NVIC_Configuration();//configure NVIC and Vector Table
  
  //configure ALL GPIO to AIN to get lowest power
  GPIO_Config_ALL_AIN();
  //configuration GPIO to measure the time from sleep to 72MHz
  GPIO_Configuration();
 
  GPIO_InitTypeDef  GPIO_InitStructure;

  //enable GPIOC and GPIOA, Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
  
  //Configure PC.10 as SLP_TR pin of RF
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  //Configure PC.11 as RST pin of RF
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  //set /RST pin high(never reset)
  GPIO_SetBits(GPIOC, GPIO_Pin_11);
  
  // Configure PC.09 as input floating (EXTI Line9)
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);//Connect EXTI Line9 to PC.9
  EXTI_ClearITPendingBit(EXTI_Line9);

  //Configures EXTI line 9 to generate an interrupt on rising edge
  EXTI_InitTypeDef  EXTI_InitStructure; 
  EXTI_InitStructure.EXTI_Line    = EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt; 
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
  EXTI_Init(&EXTI_InitStructure);
  
  RCC_ClocksTypeDef RCC_Clocks_Freq;

  /* Store frequencies of system clocks to RCC_Clocks_Freq structure */
  RCC_GetClocksFreq(&RCC_Clocks_Freq);

  // initialize board
  SysTick_Config(RCC_Clocks_Freq.HCLK_Frequency/SYS_TICK_DIV);
  leds_init();
  uart_init();
  spi_init();
  bsp_timer_init();
  radio_init();
  radiotimer_init();
  debugpins_init();
  //enable nvic for the radio
  NVIC_radio();
}

void board_sleep()
{
#if 0
  uint16_t sleepTime = radiotimer_getPeriod() - radiotimer_getCapturedTime();
  DBGMCU_Config(DBGMCU_STOP, ENABLE);
  
  // Enable PWR and BKP clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
  // Desable the SRAM and FLITF clock in Stop mode
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SRAM | RCC_AHBPeriph_FLITF, DISABLE);

  PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);
  
  if(sleepTime > 0)
  opentimers_sleepTimeCompesation(sleepTime*2);
#endif 
}

void board_reset()
{
	__disable_irq();
	NVIC_SystemReset();
}

void board_timeDelayMS(uint32_t msec){
	boardTimingDelayMS = msec;
	while (boardTimingDelayMS != 0);
}

void board_timeDelayDecrement (void){
	if (boardTimingDelayMS != 0){
		boardTimingDelayMS--;
	}

}
