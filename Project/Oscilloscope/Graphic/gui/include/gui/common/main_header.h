
#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include "stdlib.h"
#include "stdio.h"
#ifndef SIMULATOR
#include "stm32f7xx_hal.h"
#endif // SIMULATOR



#define NUMBER_OF_POINT 306
#define FALLING false
#define RISING  true
 
//#define SIMULATOR 1

enum GraphParameter
	{
		CHANNEL_1 = 0,
		CHANNEL_2,
		Y1_OFFSET = 230 / 2,
		Y2_OFFSET = 230 / 2,
	};

enum ButtonID
{
	MOVE_UP_BTN = 0,
	MOVE_DOWN_BTN,
	MOVE_LEFT_BTN,
	MOVE_RIGHT_BTN
};

#ifndef SIMULATOR
uint16_t * PushDaTaToModel_1(void);
uint16_t * PushDaTaToModel_2(void);
void GetDataFromModel(int channel, int value);
#endif // !SIMULATOR

#endif

