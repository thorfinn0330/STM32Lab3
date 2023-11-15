/*
 * display7SEG.c
 *
 *  Created on: Nov 12, 2023
 *      Author: PC
 */

#include "display7SEG.h"
int led7SEG_buffer[] = {0, 5, 0, 3};
char AnodeNumber[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x80}; //0 - 9,dp

void enable7SEG(int num) {
	HAL_GPIO_WritePin(EN_0_GPIO_Port, EN_0_Pin, num==0?RESET:SET);
	HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, num==1?RESET:SET);
	HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, num==2?RESET:SET);
	HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_3_Pin, num==3?RESET:SET);
}

void display7SEG(int num) {
	if((num<0) || (num>9)) num=0;
	HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, AnodeNumber[num]&0x01?SET:RESET);
	HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, AnodeNumber[num]&0x02?SET:RESET);
	HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, AnodeNumber[num]&0x04?SET:RESET);
	HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, AnodeNumber[num]&0x08?SET:RESET);
	HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, AnodeNumber[num]&0x10?SET:RESET);
	HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, AnodeNumber[num]&0x20?SET:RESET);
	HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, AnodeNumber[num]&0x40?SET:RESET);

}

void updateBuffer7SEG(int value1, int value2) {
	led7SEG_buffer[0] = value1/10;
	led7SEG_buffer[1] = value1%10;
	led7SEG_buffer[2] = value2/10;
	led7SEG_buffer[3] = value2%10;
}

void scan7SEG() {
	if(index_7SEG == -1) {
		updateBuffer7SEG(RED_TIME, GREEN_TIME);
		HAL_GPIO_WritePin(EN_0_GPIO_Port, EN_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_3_Pin, GPIO_PIN_SET);
		index_7SEG = 0;
		setTimer5(5);
	}
	else {
		if(timer5_flag == 1) {
			index_7SEG++;
			setTimer5(5);
		}
		if(index_7SEG >= 4) index_7SEG = 0;
		enable7SEG(index_7SEG);
		display7SEG(led7SEG_buffer[index_7SEG]);

	}
}

void scan7SEG1() {
	switch(index_7SEG) {
	case -1:
		HAL_GPIO_WritePin(EN_0_GPIO_Port, EN_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_3_Pin, GPIO_PIN_SET);
		index_7SEG = 0;
		setTimer3(10);
	break;
	case 0:
		enable7SEG(0);
		display7SEG(led7SEG_buffer[0]);
		if(timer3_flag == 1) {
			index_7SEG=1;
			setTimer3(10);
		}
		break;
	case 1:
		enable7SEG(1);
		display7SEG(led7SEG_buffer[1]);
		if(timer3_flag == 1) {
			index_7SEG=2;
			setTimer3(10);
		}
		break;
	case 2:
		enable7SEG(2);
		display7SEG(led7SEG_buffer[2]);
		if(timer3_flag == 1) {
			index_7SEG=3;
			setTimer3(10);
		}
		break;
	case 3:
		enable7SEG(3);
		display7SEG(led7SEG_buffer[3]);
		if(timer3_flag == 1) {
			index_7SEG=0;
			setTimer3(10);
		}
		break;
	default:

		break;

	}
}
