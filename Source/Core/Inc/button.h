/*
 * button.h
 *
 *  Created on: Nov 11, 2023
 *      Author: PC
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"



extern int button1_flag;
extern int button2_flag;
extern int button3_flag;

GPIO_PinState readButton(int index);

int isButton1Pressed();
int isButton2Pressed();
int isButton3Pressed();

void getKeyInput();

#endif /* INC_BUTTON_H_ */
