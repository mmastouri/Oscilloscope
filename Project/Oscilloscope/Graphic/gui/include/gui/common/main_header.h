
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
	};

enum ButtonID
{
	MOVE_UP_BTN = 0,
	MOVE_DOWN_BTN,
	MOVE_LEFT_BTN,
	MOVE_RIGHT_BTN
};

enum VoltageScale
{
	DIV_2V    = 7,
	DIV_1V    = 6,
	DIV_500mV = 5,
	DIV_200mV = 4,
	DIV_100mV = 3,
	DIV_50mV  = 2,
	DIV_20mV  = 1,
	DIV_10mV  = 0
};

enum TimeScale
{
	DIV_50uS  = 0,
	DIV_100uS = 1,
	DIV_200uS = 2,
	DIV_500uS = 3,
	DIV_1mS   = 4,
	DIV_2mS   = 5,
	DIV_5mS   = 6,
	DIV_10mS  = 7,
	DIV_20mS  = 8,
	DIV_50mS  = 9,
	DIV_100mS = 10,
	DIV_200mS = 11,
	DIV_500mS = 12,
};

#ifndef SIMULATOR
uint16_t * PushDaTaToModel_1(void);
uint16_t * PushDaTaToModel_2(void);
void GetDataFromModel(int channel, int value);
#endif // !SIMULATOR

#endif

