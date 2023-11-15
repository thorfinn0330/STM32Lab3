/*
 * global.c
 *
 *  Created on: Nov 12, 2023
 *      Author: PC
 */
#include "global.h"

int index_7SEG = -1;

int PRE_NORMAL_RED_TIME = 500;
int PRE_NORMAL_AMBER_TIME = 200;
int PRE_NORMAL_GREEN_TIME = 300;

int RED_OLD_TIME = 500;
int AMBER_OLD_TIME = 200;
int GREEN_OLD_TIME = 300;

int RED_TIME = 500;
int AMBER_TIME = 200;
int GREEN_TIME = 300;

int buffer_time = 0;

int status =INIT;
int mode_led = 0;

int counter1 = 5;
int counter2 = 3;


int flag_red_change = 0;
int flag_yellow_change = 0;
int flag_green_change = 0;

int frequency = 1000;
int TIME_DURATION = 1;
