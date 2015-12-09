/*
 * 00helloworld.c
 *
 *  Created on: Oct 20, 2015
 *      Author: SensorLab
 */
#include "string.h"
#include "uart.h"
#include "board.h"
#include "rtc_timer.h"
#include "leds.h"

const char debugStr[] = "Hello World!!!\n";

#define ALARM_PERIOD	327680	//10 seconds

void alarm_cb(void);

int mote_main(void){
	uint8_t i;
	// initialize board
	board_init();
	rtc_timer_init();
	rtc_timer_setAlarmCb(alarm_cb);
	rtc_timer_start(ALARM_PERIOD);
	while(1){
		for (i = 0;i < strlen(debugStr);i++){
			uart_writeByte(debugStr[i]);
		}
		board_timeDelayMS(2000);
	board_sleep();
	}
}

void alarm_cb(void){
	leds_error_toggle();
	rtc_timer_resetCounter();
}
