/**
\brief VESNA-SNC-STM32 definition of the "debugpins" bsp module.

\author Bostjan Mikelj,  September 2015.
*/
#include "stm32f10x_lib.h"
#include "debugpins.h"

//=========================== defines =========================================

//=========================== variables =======================================

//=========================== prototypes ======================================

//=========================== public ==========================================

//todo find some (optionally 6) debug pins available and write code for initializing, setting, clearing and toggling them

void debugpins_init() {}

void debugpins_frame_toggle() {}
void debugpins_frame_clr() {}
void debugpins_frame_set() {}

void debugpins_slot_toggle() {}
void debugpins_slot_clr() {}
void debugpins_slot_set() {}

void debugpins_fsm_toggle() {}
void debugpins_fsm_clr() {}
void debugpins_fsm_set() {}

void debugpins_task_toggle() {}
void debugpins_task_clr() {}
void debugpins_task_set() {}

void debugpins_isr_toggle() {}
void debugpins_isr_clr() {}
void debugpins_isr_set() {}

void debugpins_radio_toggle() {}
void debugpins_radio_clr() {}
void debugpins_radio_set() {}

