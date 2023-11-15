/*
 * fsm_main.c
 *
 *  Created on: Nov 12, 2023
 *      Author: PC
 */

#include "fsm_main.h"
//use timer1 for couting 1s to update counter1, counter2
//use timer2 for main_fsm
//use timer4 for blinking led

//Saves Normal Mode time variables before switching to Mode 2,3,4
//used when time adjustment is not satisfactory
void saveNormalTime() {
	PRE_NORMAL_RED_TIME = RED_TIME;
	RED_OLD_TIME = RED_TIME;
	PRE_NORMAL_AMBER_TIME = AMBER_TIME;
	PRE_NORMAL_GREEN_TIME = GREEN_TIME;
}

void normalToMode2() {
	clearAllLed();
	setTimer4(25);
	status = INC_RED;
	saveNormalTime();
}

//count down to display led 7SEG in Normal Mode
void count_down() {
	if(timer1_flag == 1) {
	  setTimer1(100);
	  counter1--;
	  counter2--;
	  if(counter1 >= 0 && counter2 >=0) {
		  updateBuffer7SEG(counter1, counter2);
	  }
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
				updateBuffer7SEG(counter1, counter2);
				status = RED_AMBER;
			}

			//Check Button1 press
			if(isButton1Pressed() == 1) {
				normalToMode2();
			}
			break;
		case RED_AMBER:
			setLedOnWay1(RED_LED);
			setLedOnWay2(AMBER_LED);
			if(timer2_flag == 1) {
				setTimer2(GREEN_TIME);
				counter1 = GREEN_TIME/100;
				counter2 = RED_TIME/100;
				updateBuffer7SEG(counter1, counter2);
				status = GREEN_RED;
			}

			//Check Button1 press
			if(isButton1Pressed() == 1) {
				normalToMode2();
			}
			break;
		case GREEN_RED:
			setLedOnWay1(GREEN_LED);
			setLedOnWay2(RED_LED);
			if(timer2_flag == 1) {
				setTimer2(AMBER_TIME);
				counter1 = AMBER_TIME/100;
				updateBuffer7SEG(counter1, counter2);
				status = AMBER_RED;
			}

			//Check Button1 press
			if(isButton1Pressed() == 1) {
				normalToMode2();
			}
			break;
		case AMBER_RED:
			setLedOnWay1(AMBER_LED);
			setLedOnWay2(RED_LED);
			if(timer2_flag == 1) {
				setTimer2(GREEN_TIME);
				counter1 = RED_TIME/100;
				counter2 = GREEN_TIME/100;
				updateBuffer7SEG(counter1, counter2);
				status = RED_GREEN;
			}

			//Check Button1 press
			if(isButton1Pressed() == 1) {
				normalToMode2();
			}
			break;
		case INC_RED:							//Mode 2
			red_led_blinky();					//Blinking red led

			//The top 2 7SEG leds use to display the mode.
			//The bottom 2 7SEG leds use to display time of correspond LED.
			updateBuffer7SEG(2, RED_TIME/100);

			//RED_TIME is the latest value but not sure to be set or not
			if(isButton1Pressed() == 1){
				if(flag_red_change == 0){		//Button3 not press
					RED_TIME = RED_OLD_TIME;	//set the most recently saved value
				}
				flag_red_change = 0;
				clearAllLed();
				setTimer4(25);
				status = INC_AMBER;
				AMBER_OLD_TIME = AMBER_TIME;	//save value
			}
			if(isButton2Pressed() == 1){
				if(flag_red_change == 1){
					RED_OLD_TIME = RED_TIME;	//save value
					flag_red_change = 0;
				}
				RED_TIME += 100;
				//guaranteed to be between 1-99
				if(RED_TIME >= 10000) RED_TIME = 100;
			}
			if(isButton3Pressed() == 1){
				flag_red_change = 1;
			}
			break;
		case INC_AMBER:							//Mode 3
			amber_led_blinky();					//Blinking amber led
			//display mode and time for AMBER_LED
			updateBuffer7SEG(3, AMBER_TIME/100);
			//AMBER_TIME is the latest value but not sure to be set or not
			if(isButton1Pressed() == 1){
				if(flag_yellow_change == 0){	//Button3 not press
					AMBER_TIME = AMBER_OLD_TIME;//set the most recently saved value
				}
				flag_yellow_change = 0;
				clearAllLed();
				setTimer4(25);
				status = INC_GREEN;
				GREEN_OLD_TIME = GREEN_TIME;	//save value
			}
			if(isButton2Pressed() == 1){
				if(flag_yellow_change == 1){
					AMBER_OLD_TIME = AMBER_TIME;//save value
					flag_yellow_change = 0;
				}
				AMBER_TIME += 100;
				//guaranteed to be between 1-99
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
				//If the time setting is not satisfied,
				//switch to TIME_ERROR state for 2 seconds to let the user know
					status = TIME_ERROR;
					setTimer2(200);
				}
				else {
				//If the time setting is satisfied,
				//back to Normal Mode
					status = RED_GREEN;
				//setTimer and counter
					setTimer2(GREEN_TIME);
					counter1 = RED_TIME/100;
					counter2 = GREEN_TIME/100;
				}
			}
			if(isButton2Pressed() == 1){
				if(flag_green_change == 1){
					GREEN_OLD_TIME = GREEN_TIME;	//save value
					flag_green_change = 0;
				}
				GREEN_TIME += 100;
				//guaranteed to be between 1-99
				if(GREEN_TIME >= 10000) GREEN_TIME = 100;
			}
			if(isButton3Pressed() == 1){
				flag_green_change = 1;
			}
			break;
		case TIME_ERROR:
			//all led7SED display 0 for error
			updateBuffer7SEG(0, 0);
			//all single leds off
			clearAllLed();
			//Ignore all changes, reassign the value of the previous Normal Mode
			RED_TIME = PRE_NORMAL_RED_TIME;
			AMBER_TIME = PRE_NORMAL_AMBER_TIME;
			GREEN_TIME = PRE_NORMAL_GREEN_TIME;
			//After 2s, back to Normal Mode
			if(timer2_flag == 1) {
				status = RED_GREEN;
				setTimer2(GREEN_TIME);
				counter1 = RED_TIME/100;
				counter2 = GREEN_TIME/100;
				updateBuffer7SEG(counter1, counter2);
}
			break;
		default:
			break;
		}

}

