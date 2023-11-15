/*
 * display7SEG.h
 *
 *  Created on: Nov 12, 2023
 *      Author: PC
 */

#ifndef INC_DISPLAY7SEG_H_
#define INC_DISPLAY7SEG_H_

#include "global.h"
#include "main.h"
#include "software_timer.h"

void enable7SEG(int num) ;
void display7SEG(int num);
void updateBuffer7SEG(int value1, int value2);
void scan7SEG();
void scan7SEG1();

#endif /* INC_DISPLAY7SEG_H_ */
