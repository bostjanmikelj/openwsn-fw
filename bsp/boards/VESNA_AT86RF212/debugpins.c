/**
\brief VESNA-SNC-STM32 definition of the "debugpins" bsp module.

\author Bostjan Mikelj,  September 2015.
*/
#include "stm32f10x_lib.h"
#include "debugpins.h"

//=========================== defines =========================================
#define DEBUG_FRAME_PIN          (1<<1)
#define DEBUG_SLOT_PIN           (1<<2)
#define DEBUG_FSM_PIN          	 (1<<3)
#define DEBUG_TASK_PIN           (1<<4)
#define DEBUG_ISR_PIN            (1<<5)
#define DEBUG_RADIO_PIN          (1<<6)
#define DEBUG_PORT 				  GPIOA
//=========================== variables =======================================

//=========================== prototypes ======================================

//=========================== public ==========================================

//todo find some (optionally 6) debug pins available and write code for initializing, setting, clearing and toggling them

void debugpins_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable debug port clock*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	/* Init debug pins*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void debugpins_frame_toggle() {
	DEBUG_PORT->ODR ^= DEBUG_FRAME_PIN;
}
void debugpins_frame_clr() {
	DEBUG_PORT->ODR &= ~DEBUG_FRAME_PIN;
}
void debugpins_frame_set() {
	DEBUG_PORT->ODR |= DEBUG_FRAME_PIN;
}

void debugpins_slot_toggle() {
	DEBUG_PORT->ODR ^= DEBUG_SLOT_PIN;
}
void debugpins_slot_clr() {
	DEBUG_PORT->ODR &= ~DEBUG_SLOT_PIN;
}
void debugpins_slot_set() {
	DEBUG_PORT->ODR |= DEBUG_SLOT_PIN;
}

void debugpins_fsm_toggle() {
	DEBUG_PORT->ODR ^= DEBUG_FSM_PIN;
}
void debugpins_fsm_clr() {
	DEBUG_PORT->ODR &= ~DEBUG_FSM_PIN;
}
void debugpins_fsm_set() {
	DEBUG_PORT->ODR |= DEBUG_FSM_PIN;
}

void debugpins_task_toggle() {
	DEBUG_PORT->ODR ^= DEBUG_TASK_PIN;
}
void debugpins_task_clr() {
	DEBUG_PORT->ODR &= ~DEBUG_TASK_PIN;
}
void debugpins_task_set() {
	DEBUG_PORT->ODR |= DEBUG_TASK_PIN;
}

void debugpins_isr_toggle() {
	DEBUG_PORT->ODR ^= DEBUG_ISR_PIN;
}
void debugpins_isr_clr() {
	DEBUG_PORT->ODR &= ~DEBUG_ISR_PIN;
}
void debugpins_isr_set() {
	DEBUG_PORT->ODR |= DEBUG_ISR_PIN;
}

void debugpins_radio_toggle() {
	DEBUG_PORT->ODR ^= DEBUG_RADIO_PIN;
}
void debugpins_radio_clr() {
	DEBUG_PORT->ODR &= ~DEBUG_RADIO_PIN;
}
void debugpins_radio_set() {
	DEBUG_PORT->ODR |= DEBUG_RADIO_PIN;
}

