/*
 * mock.h
 *
 *  Created on: 12/feb/2019
 *      Author: leona
 */


#ifndef MOCK_H_
#define MOCK_H_

#include <stdint.h>
#include "custom_types.h"

#define	N_BEEPS_ALARM		3		// number of beeps when alarm triggers
#define NO_TOUCH_HOLD				// events generated only on first press, not hold

#define TASK(taskname) void taskname(void)
#define ISR2(hname) void hname(void)
#define MILLISECONDS_TO_TICKS(a,b) 	0
#define SEP1STR 	0
#define SEP2STR 	0
#define Black 		0
#define White 		0

typedef struct TPoint {
	uint16_t x;
	uint16_t y;
} TPoint;

extern uint16_t * const AlarmTaskAlarmBuzzer,
	* const AlarmTaskStopwatch,
	* const AlarmTaskClock,
	* const AlarmTaskInterface,
	* const AlarmTaskTouch;

extern uint16_t my_counter;
extern uint16_t MyWatchScr[1];

extern uint16_t buzz_active;

void SystemInit(void);
void EE_system_init(void);
void EE_systick_set_period(uint16_t a);
void EE_systick_enable_int(void);
void EE_systick_start(void);
void IOE_Config(void);
void STM32f4_Discovery_LCD_Init(void);
void debug_init(void);
void InitTouch(float a, float b, float c, float d);
void buzzer_init(void);
void buzzer_unmute(void);
void buzzer_mute(void);
void display_time(Mode m);
void update_mode_visual(Mode m1, Mode m2);
void DrawInit(uint16_t* a);
void LCD_SetTextColor(uint16_t a);
void LCD_SetBackColor(uint16_t a);
void LCD_DrawFullRect(uint16_t a, uint16_t b, uint16_t c, uint16_t d);
void WPrint(uint16_t* a, char* b);
void CounterTick(uint16_t a);
void SetRelAlarm(uint16_t * const a, uint16_t b, uint16_t c);
void CancelAlarm(uint16_t * const a);
unsigned char GetTouch_SC_Async(unsigned *a, unsigned *b);
void OnTouch(uint16_t* a, TPoint* p);

#endif /* MOCK_H_ */
