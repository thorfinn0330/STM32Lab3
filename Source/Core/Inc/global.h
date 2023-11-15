/*
 * global.h
 *
 *  Created on: Nov 11, 2023
 *      Author: PC
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define MAX_LED7SEG  4

#define INIT		1
#define RED_GREEN	2
#define RED_AMBER	3
#define GREEN_RED	4
#define AMBER_RED	5
#define INC_RED		6
#define INC_AMBER	7
#define INC_GREEN	8
#define TIME_ERROR	9

#define RED_LED		10
#define AMBER_LED		11
#define GREEN_LED		12

extern int RED_OLD_TIME;
extern int AMBER_OLD_TIME;
extern int GREEN_OLD_TIME;

extern int RED_TIME;
extern int AMBER_TIME;
extern int GREEN_TIME;

extern int status;

extern int counter1;
extern int counter2;

extern int index_7SEG;
extern int led7SEG_buffer[MAX_LED7SEG];

extern int flag_red_change;
extern int flag_yellow_change;
extern int flag_green_change;

extern int frequency;
extern int TIME_DURATION;

#endif /* INC_GLOBAL_H_ */
