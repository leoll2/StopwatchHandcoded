/*
 * swatch.h
 *
 *  Created on: 12/feb/2019
 *      Author: leona
 */

#ifndef SWATCH_H_
#define SWATCH_H_

#include "custom_types.h"
#include "mock.h"

extern uint8_t hours, minutes, seconds, tenths;
extern uint8_t s_minutes, s_seconds, s_tenths;
extern uint8_t a_hours, a_minutes;
extern Mode mode;
extern TimeSetMode tsmode;
extern AlarmSetMode asmode;
extern bool plus_pressed;
extern bool minus_pressed;
extern bool timemode_pressed;
extern bool timesetmode_pressed;
extern bool alarmmode_pressed;
extern bool swatchmode_pressed;
extern bool swatch_running;


TASK(TaskInterface);
TASK(TaskClock);
TASK(TaskStopwatch);
TASK(TaskAlarmBuzzer);
TASK(TaskTouch);

void init_swatch(void);
void handle_events(Mode old_mode);

#endif /* SWATCH_H_ */
