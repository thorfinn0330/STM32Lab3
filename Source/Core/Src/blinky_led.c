/*
 * blinky_led.c
 *
 *  Created on: Nov 12, 2023
 *      Author: PC
 */

#include "blinky_led.h"

void red_led_blinky(){
	if(timer4_flag == 1) {
		HAL_GPIO_TogglePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin);
		HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
		if(TIME_DURATION >= 100) {
			if(mode_led == 0) {
				setTimer4(30);
			}
			else {
				setTimer4(20);
			}
			mode_led = 1 - mode_led;
		}
		else {
			setTimer4(25);
		}
	}
}

void amber_led_blinky(){
	if(timer4_flag == 1) {
		HAL_GPIO_TogglePin(LED_YELLOW_0_GPIO_Port, LED_YELLOW_0_Pin);
		HAL_GPIO_TogglePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin);
		if(TIME_DURATION >= 100) {
			if(mode_led == 0) {
				setTimer4(30);
			}
			else {
				setTimer4(20);
			}
			mode_led = 1 - mode_led;
		}
		else {
			setTimer4(25);
		}
	}
}

void green_led_blinky(){
	if(timer4_flag == 1) {
		HAL_GPIO_TogglePin(LED_GREEN_0_GPIO_Port, LED_GREEN_0_Pin);
		HAL_GPIO_TogglePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin);
		if(TIME_DURATION >= 100) {
			if(mode_led == 0) {
				setTimer4(30);
			}
			else {
				setTimer4(20);
			}
			mode_led = 1 - mode_led;
		}
		else {
			setTimer4(25);
		}
	}
}
