
#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stdlib.h"
#include "stdio.h"
#ifndef SIMULATOR
#include "stm32f7xx_hal.h"
#include "settings.h"
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

#define PRESS_SIGTYPE          0x100
#define PRESS_SAVE             0x101
#define PRESS_SWITCH_CHANNEL   0x102
#define PRESS_TIME_UP          0x103
#define PRESS_TIME_DOWN        0x104
#define PRESS_VOLT_UP          0x105
#define PRESS_VOLT_DOWN        0x106

#ifndef SIMULATOR
uint16_t * PushDaTaToModel_1(void);
uint16_t * PushDaTaToModel_2(void);
void UpdateHWTimeScale(int channel, int value);
void ControlHWRunStop(int state);

void gen_set_signal_type(int type);
void gen_set_signal_freq(int freq);
	
int32_t Get_CLI_UX_Commands(void);
#endif // !SIMULATOR
#ifdef __cplusplus
}
#endif
#endif

