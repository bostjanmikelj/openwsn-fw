/**
\brief VESNA SNC board definition of the "leds" bsp module.

\author Alaeddine Weslati <alaeddine.weslati@inria.fr>, January 2014.
*/

#include "stm32f10x_lib.h"
#include "leds.h"

//=========================== defines =========================================
#define LED_ERROR_PIN          (1<<7)	//RED
#define LED_SYNC_PIN           (1<<8)	//GREEN
#define LED_RADIO_PIN          (1<<9)	//YELLOW
#define LED_MAIN_PIN		   (1<<2)	//VESNA MAIN LED
#define GPIO_LED_MAIN			GPIOB
#define PIN_LED_MAIN			GPIO_Pin_2
//=========================== variables =======================================
static int32_t pwmCount, pwmCountReload;
//=========================== prototypes ======================================

void Delay(void);

//=========================== public ==========================================

void leds_init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Init main LED indicator*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

  GPIO_InitStructure.GPIO_Pin = PIN_LED_MAIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_LED_MAIN, &GPIO_InitStructure);

  /* LED PWM default values 0.1Hz, 50% */
  pwmCount = 0;
  pwmCountReload = 99;
  GPIO_ResetBits(GPIO_LED_MAIN, PIN_LED_MAIN);
  /* Init pins for LEDs*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_7);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);

//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

// red
void leds_error_on()
{
	GPIOA->ODR &= ~LED_ERROR_PIN;
}
void leds_error_off()
{
	GPIOA->ODR |= LED_ERROR_PIN;
}
void leds_error_toggle()
{
	GPIOA->ODR ^= LED_ERROR_PIN;
}
uint8_t leds_error_isOn()
{
  u8 bitstatus = 0x00;
  if ((GPIOA->ODR & LED_ERROR_PIN) != (u32)0)
  {
    bitstatus = 0x00;
  }
  else
  {
    bitstatus = 0x01;
  }
  return bitstatus;
}
void leds_error_blink() {
	/*turn OFF error LED*/
	leds_error_off();
	leds_error_toggle();
	/*delay 10ms */
	board_timeDelayMS(100);
	leds_error_toggle();
	board_timeDelayMS(100);
}

// green
void leds_sync_on()
{
	GPIOB->ODR &= ~LED_SYNC_PIN;
}
void leds_sync_off()
{
	GPIOB->ODR |= LED_SYNC_PIN;
}
void leds_sync_toggle()
{
	GPIOB->ODR ^= LED_SYNC_PIN;
}
uint8_t leds_sync_isOn()
{
  u8 bitstatus = 0x00;
  if ((GPIOB->ODR & LED_SYNC_PIN) != (u32)0)
  {
    bitstatus = 0x00;
  }
  else
  {
    bitstatus = 0x01;
  }
  return bitstatus;
}

// yellow
void leds_radio_on()
{
	GPIOB->ODR &= ~LED_RADIO_PIN;
}
void leds_radio_off()
{
	GPIOB->ODR |= LED_RADIO_PIN;
}
void leds_radio_toggle()
{
	GPIOB->ODR ^= LED_RADIO_PIN;
}
uint8_t leds_radio_isOn()
{
  u8 bitstatus = 0x00;
  if ((GPIOB->ODR & LED_RADIO_PIN) != (u32)0)
  {
    bitstatus = 0x00;
  }
  else
  {
    bitstatus = 0x01;
  }
  return bitstatus;
}
// yellow
void leds_debug_on() {}
void leds_debug_off() {}
void leds_debug_toggle() {}
uint8_t leds_debug_isOn() {
	return 0;
}

void leds_all_on()
{
  leds_error_on();
  leds_sync_on();
  leds_radio_on();
}
void leds_all_off()
{
  leds_error_off();
  leds_sync_off();
  leds_radio_off();
}
void leds_all_toggle()
{
  leds_error_toggle();
  leds_sync_toggle();
  leds_radio_toggle();
}

void leds_circular_shift()
{
  leds_error_toggle();
  Delay();
  leds_sync_toggle();
  Delay();
  leds_radio_toggle();
  Delay();
}

void leds_increment() {}

void 	leds_main_on(void){
	GPIOB->ODR |= LED_MAIN_PIN;
}
void 	leds_main_off(void){
	GPIOB->ODR &= ~LED_MAIN_PIN;
}
void 	leds_main_toggle(void){
	GPIOB->ODR ^= LED_MAIN_PIN;
}

void leds_indToggle(void){
	if(pwmCount < 49){
		leds_main_on();
	}
	else{
		leds_main_off();
	}
	pwmCount++;
	if (pwmCount == pwmCountReload){
		pwmCount = 0;
	}
}

//=========================== private =========================================

void Delay(void)
{
  uint32_t i;
  for(i=0; i<0xfffff; i++);
}

