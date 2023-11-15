/*
 * led_control.c
 *
 *  Created on: Nov 12, 2023
 *      Author: PC
 */

#include "led_control.h"

void setLedOnWay1(int led) {
	HAL_GPIO_WritePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin, led==RED_LED?RESET:SET);
	HAL_GPIO_WritePin(LED_YELLOW_0_GPIO_Port, LED_YELLOW_0_Pin, led==AMBER_LED?RESET:SET);
	HAL_GPIO_WritePin(LED_GREEN_0_GPIO_Port, LED_GREEN_0_Pin, led==GREEN_LED?RESET:SET);
}
void setLedOnWay2(int led) {
	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, led==RED_LED?RESET:SET);
	HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, led==AMBER_LED?RESET:SET);
	HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, led==GREEN_LED?RESET:SET);

}

void clearAllLed() {
	HAL_GPIO_WritePin(LED_RED_0_GPIO_Port, LED_RED_0_Pin, SET);
	HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, SET);
	HAL_GPIO_WritePin(LED_YELLOW_0_GPIO_Port, LED_YELLOW_0_Pin, SET);
	HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, SET);
	HAL_GPIO_WritePin(LED_GREEN_0_GPIO_Port, LED_GREEN_0_Pin, SET);
	HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, SET);
}
