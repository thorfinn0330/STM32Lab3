/*
 * fsm_main.c
 *
 *  Created on: Nov 12, 2023
 *      Author: PC
 */

#include "fsm_main.h"
//use timer2 for main_fsm
void count_down() {
	if(timer1_flag == 1) {
	  setTimer1(100);
	  counter1--;
	  counter2--;
	  updateBuffer7SEG(counter1, counter2);
	  HAL_GPIO_TogglePin(LED_TEST_GPIO_Port, LED_TEST_Pin);
  }
}
void main_fsm() {

	switch(status) {
		case INIT:
			clearAllLed();
			status = RED_GREEN;
			setTimer1(100);
			setTimer2(GREEN_TIME);
			counter1 = RED_TIME/100;
			counter2 = GREEN_TIME/100;
			break;
		case RED_GREEN:
			setLedOnWay1(RED_LED);
			setLedOnWay2(GREEN_LED);
			if(timer2_flag == 1) {
				setTimer2(AMBER_TIME);
				counter2 = AMBER_TIME/100;
				status = RED_AMBER;
			}
			if(isButton1Pressed() == 1) {
				clearAllLed();
				setTimer4(25);
				status = INC_RED;
				RED_OLD_TIME = RED_TIME;
			}
			break;
		case RED_AMBER:
			setLedOnWay1(RED_LED);
			setLedOnWay2(AMBER_LED);
			if(timer2_flag == 1) {
				setTimer2(GREEN_TIME);
				counter1 = GREEN_TIME/100;
				counter2 = RED_TIME/100;
				status = GREEN_RED;
			}
			if(isButton1Pressed() == 1) {
				clearAllLed();
				setTimer4(25);
				status = INC_RED;
				RED_OLD_TIME = RED_TIME;
			}
			break;
		case GREEN_RED:
			setLedOnWay1(GREEN_LED);
			setLedOnWay2(RED_LED);
			if(timer2_flag == 1) {
				setTimer2(AMBER_TIME);
				counter1 = AMBER_TIME/100;
				status = AMBER_RED;
			}
			if(isButton1Pressed() == 1) {
				clearAllLed();
				setTimer4(25);
				status = INC_RED;
				RED_OLD_TIME = RED_TIME;
			}
			break;
		case AMBER_RED:
			setLedOnWay1(AMBER_LED);
			setLedOnWay2(RED_LED);
			if(timer2_flag == 1) {
				setTimer2(GREEN_TIME);
				counter1 = RED_TIME/100;
				counter2 = GREEN_TIME/100;
				status = RED_GREEN;
			}
			if(isButton1Pressed() == 1) {
				clearAllLed();
				setTimer4(25);
				status = INC_RED;
				RED_OLD_TIME = RED_TIME;
			}
			break;
		case INC_RED:
			red_led_blinky();
			updateBuffer7SEG(2, RED_TIME/100);
			if(isButton1Pressed() == 1){
				if(flag_red_change == 0){
					RED_TIME = RED_OLD_TIME;
				}
				flag_red_change = 0;
				clearAllLed();
				setTimer4(25);
				status = INC_AMBER;
				AMBER_OLD_TIME = AMBER_TIME;
			}
			if(isButton2Pressed() == 1){
				RED_TIME += 100;
				if(RED_TIME >= 10000) RED_TIME = 100;
			}
			if(isButton3Pressed() == 1){
				flag_red_change = 1;
			}
			break;
		case INC_AMBER:
			amber_led_blinky();
			updateBuffer7SEG(3, AMBER_TIME/100);
			//display mode and time for AMBER_LED
			if(isButton1Pressed() == 1){
				if(flag_yellow_change == 0){
					AMBER_TIME = AMBER_OLD_TIME;
				}
				flag_yellow_change = 0;
				clearAllLed();
				setTimer4(25);
				status = INC_GREEN;
				GREEN_OLD_TIME = GREEN_TIME;
			}
			if(isButton2Pressed() == 1){
				AMBER_TIME += 100;
				if(AMBER_TIME >= 10000) AMBER_TIME = 100;
			}
			if(isButton3Pressed() == 1){
				flag_yellow_change = 1;
			}
			break;
		case INC_GREEN:
			green_led_blinky();
			updateBuffer7SEG(4, GREEN_TIME/100);

			//display mode and time for GREEN_LED
			if(isButton1Pressed() == 1){
				if(flag_green_change == 0){
					GREEN_TIME = GREEN_OLD_TIME;
				}
				flag_green_change = 0;
				//check valid of time
				if(GREEN_TIME + AMBER_TIME != RED_TIME) {
					status = TIME_ERROR;
					setTimer2(200);
				}
				else {
					status = RED_GREEN;
					setTimer2(GREEN_TIME);
					counter1 = RED_TIME/100;
					counter2 = GREEN_TIME/100;
				}
			}
			if(isButton2Pressed() == 1){
				GREEN_TIME += 100;
				if(GREEN_TIME >= 10000) GREEN_TIME = 100;
			}
			if(isButton3Pressed() == 1){
				flag_green_change = 1;
			}
			break;
		case TIME_ERROR:
			//all led7SED display 0 for error
			updateBuffer7SEG(0, 0);
			clearAllLed();
			RED_TIME = RED_OLD_TIME;
			AMBER_TIME = AMBER_OLD_TIME;
			GREEN_TIME = GREEN_OLD_TIME ;
			if(timer2_flag == 1) {
				status = RED_GREEN;
				setTimer2(GREEN_TIME);
				counter1 = RED_TIME/100;
				counter2 = GREEN_TIME/100;
			}
			break;
		default:
			break;
		}
	scan7SEG();
	count_down();

}

