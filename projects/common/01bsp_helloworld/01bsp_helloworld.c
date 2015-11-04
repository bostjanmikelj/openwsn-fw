/*
 * 00helloworld.c
 *
 *  Created on: Oct 20, 2015
 *      Author: SensorLab
 */
#include "string.h"
#include "uart.h"
#include "board.h"

const char debugStr[] = "Hello World!!!\n";


int mote_main(void){
	uint8_t i;
	// initialize board
	board_init();
	while(1){
		for (i = 0;i < strlen(debugStr);i++){
			uart_writeByte(debugStr[i]);
		}
		i = 0;
		board_timeDelayMS(5000);
	}
}
