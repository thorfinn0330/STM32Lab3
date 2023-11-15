/*
 * button.c
 *
 *  Created on: Nov 11, 2023
 *      Author: PC
 */
#include "button.h"

#define NO_OF_BUTTONS	3
#define NORMAL_STATE	GPIO_PIN_SET
#define PRESSED_STATE	GPIO_PIN_RESET
#define DURATION_FOR_AUTO_INCREASING	50

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTONS];

static uint8_t flagForButtonPressed1s[NO_OF_BUTTONS];
static uint16_t counterForButtonPressed1s[NO_OF_BUTTONS];

int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;

GPIO_PinState readButton(int index) {
	if(index == 1) return HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
	else if(index == 2) return HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
	else if(index == 3) return HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
	else return GPIO_PIN_SET;
}

int isButton1Pressed() {
	if(button1_flag == 1) {
		button1_flag = 0;
		return 1;
	}
	return 0;
}

int isButton2Pressed() {
	if(button2_flag == 1) {
		button2_flag = 0;
		return 1;
	}
	return 0;
}

int isButton3Pressed() {
	if(button3_flag == 1) {
		button3_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess1(){
	//TODO
	button1_flag = 1;
}

void subKeyProcess2(){
	//TODO
	button2_flag = 1;
}

void subKeyProcess3(){
	//TODO
	button3_flag = 1;
}

void getKeyInput() {
	for(int i=0; i<NO_OF_BUTTONS; i++) {
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = readButton(i+1);

		if((debounceButtonBuffer1[i]==debounceButtonBuffer2[i]) && (debounceButtonBuffer1[i]==debounceButtonBuffer3[i])) {
			if(buttonBuffer[i] != debounceButtonBuffer1[i]) {
				buttonBuffer[i] = debounceButtonBuffer1[i];
				if(debounceButtonBuffer1[i] == PRESSED_STATE) {
					switch (i) {
					case 0:
						subKeyProcess1();
						break;
					case 1:
						subKeyProcess2();
						break;
					case 2:
						subKeyProcess3();
						break;
					default:
						break;
					}
					counterForButtonPressed1s[i] = 100;
				}
			}
			else {
				counterForButtonPressed1s[i]--;
				if(counterForButtonPressed1s[i] == 0) {
					counterForButtonPressed1s[i] = 100;
					flagForButtonPressed1s[i] = 1;
					buttonBuffer[i] = NORMAL_STATE;
				}
			}
		}
	}
}
