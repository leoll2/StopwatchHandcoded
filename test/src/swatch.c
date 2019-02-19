/* Main file of the actual stopwatch application */

#include <stdio.h>

#include "swatch.h"

#include "custom_types.h"
#include "event.h"

uint8_t hours, minutes, seconds, tenths;	// clock time
uint8_t s_minutes, s_seconds, s_tenths; 	// stopwatch time
uint8_t a_hours, a_minutes;					// alarm time
Mode mode = TIMEMODE;						// current mode
TimeSetMode tsmode = SETHOURS;				// current submode of timeset
AlarmSetMode asmode = ASETHOURS;			// current submode of alarmset
bool plus_pressed;							// plus button press signal
bool minus_pressed;							// minus button press signal
bool timemode_pressed;						// time mode button press signal
bool timesetmode_pressed;					// timeset mode button press signal
bool alarmmode_pressed;						// alarmset mode button press signal
bool swatchmode_pressed;					// stopwatch mode button press signal
bool swatch_running;						// stopwatch currently running

char s[64];									// buffer for debug messages


/* SysTick ISR2 handler */
ISR2(systick_handler)
{
	CounterTick(my_counter);
}


/* React to external user-triggered events, performing the appropriate action */
void handle_events(Mode old_mode)
{
	// Switch mode
	if (timemode_pressed)
		mode = TIMEMODE;
	else if (timesetmode_pressed)
		mode = TIMESETMODE;
	else if (swatchmode_pressed)
		mode = SWATCHMODE;
	else if (alarmmode_pressed)
		mode = ALARMMODE;

	// If in timeset mode, select the digit to change
	if (timesetmode_pressed && (old_mode == TIMESETMODE) && (mode == TIMESETMODE))
		tsmode = (tsmode == SETHOURS) ? SETMINUTES : SETHOURS;

	// If in alarmset mode, select the digit to change
	if (alarmmode_pressed && (old_mode == ALARMMODE) && (mode == ALARMMODE))
		asmode = (asmode == ASETHOURS) ? ASETMINUTES : ASETHOURS;

	// Plus button pressed
	if (plus_pressed) {
		switch (mode) {
			case TIMESETMODE:
				if (tsmode == SETHOURS)
					hours = (hours + 1) % 24;		// increment hours
				else
					minutes = (minutes + 1) % 60;	// increment minutes
				break;
			case ALARMMODE:
				if (asmode == ASETHOURS)
					a_hours = (a_hours + 1) % 24;	  // increment alarm hours
				else
					a_minutes = (a_minutes + 1) % 60; // increment alarm minutes
				break;
			case SWATCHMODE:
				if (!swatch_running) {
					SetRelAlarm(AlarmTaskStopwatch, 10, 100); // start stopwatch
					swatch_running = true;
				} else {
					CancelAlarm(AlarmTaskStopwatch);		  // pause stopwatch
					swatch_running = false;
				}
				break;
			default:
				break;
		}
	}
	// Minus button pressed
	if (minus_pressed) {
		switch (mode) {
			case TIMESETMODE:
				if (tsmode == SETHOURS)
					hours = (hours + 23) % 24;		// decrement hours
				else
					minutes = (minutes + 59) % 60; 	// decrement minutes
				break;
			case ALARMMODE:
				if (asmode == ASETHOURS)
					a_hours = (a_hours + 23) % 24;	   // decrement alarm hours
				else
					a_minutes = (a_minutes + 59) % 60; // decrement alarm minutes
				break;
			case SWATCHMODE:
				s_minutes = s_seconds = s_tenths = 0;  // reset stopwatch
				break;
			default:
				break;
		}
	}
}


/* Check if it's time to trigger the alarm */
void check_alarm(void)
{
	if (hours == a_hours && minutes == a_minutes && seconds == 0)
		SetRelAlarm(AlarmTaskAlarmBuzzer, 10, 1000);
}


/* Update the current time */
TASK(TaskClock)
{
	if (++tenths % 10 == 0) {
		tenths = 0;
		if (++seconds % 60 == 0) {
			seconds = 0;
			if (++minutes % 60 == 0) {
				minutes = 0;
				if (++hours % 24 == 0)
					hours = 0;
			}
		}
	}
}


/* Update the stopwatch time */
TASK(TaskStopwatch)
{
	if (++s_tenths % 10 == 0) {
		s_tenths = 0;
		if (++s_seconds % 60 == 0) {
			s_seconds = 0;
			if (++s_minutes % 60 == 0)
				s_minutes = 0;
		}
	}
}


/* Enable/disable the buzzer when the alarm is active.
 * The acoustic pattern alternates 1 second of beep to
 * 1 second of silence, for N consecutive times */
TASK(TaskAlarmBuzzer)
{
	static uint8_t count = 2 * N_BEEPS_ALARM;

	if (count % 2 == 0)
		buzzer_unmute();
	else
		buzzer_mute();

	if (--count == 0) {
		buzzer_mute();
		count = 2 * N_BEEPS_ALARM;			// reset for next time
		CancelAlarm(AlarmTaskAlarmBuzzer);	// deactivate the alarm
	}
}


/* Handle user-triggered events and update the GUI */
TASK(TaskInterface)
{
	static Mode old_mode = ALARMMODE;

	// Parse the events
	if (IsEvent(TIMEMODE_EV)) timemode_pressed = 1;
	else timemode_pressed = 0;

	if (IsEvent(TIMESETMODE_EV)) timesetmode_pressed = 1;
	else timesetmode_pressed = 0;

	if (IsEvent(ALARMMODE_EV)) alarmmode_pressed = 1;
	else alarmmode_pressed = 0;

	if (IsEvent(SWATCHMODE_EV)) swatchmode_pressed = 1;
	else swatchmode_pressed = 0;

	if (IsEvent(PLUS_EV)) plus_pressed = 1;
	else plus_pressed = 0;

	if (IsEvent(MINUS_EV)) minus_pressed = 1;
	else minus_pressed = 0;

	// Handle the events
	handle_events(old_mode);
	ClearEvents();

	// Activate the alarm if necessary
	check_alarm();

	// Plot the current time
	display_time(old_mode);

	// Plot the current mode if it has changed
	if (mode != old_mode) {
		update_mode_visual(old_mode, mode);
		old_mode = mode;
	}
}


/* Read inputs from the touchscreen */
TASK(TaskTouch)
{
	static bool pressed = false;
	unsigned int i = 0, px = 0, py = 0;
	TPoint p = {0,0};

	/* Read 6 times and average because my screen is damaged and
	   x-coordinate jitter is very high in some regions */
	while ((i < 6) && GetTouch_SC_Async(&px, &py)) {
		++i;
		p.x += px;
		p.y += py;
	}

	if (i > 0) {
#ifdef NO_TOUCH_HOLD
		if (!pressed) {
#endif
			p.x /= i;
			p.y /= i;
			OnTouch(MyWatchScr, &p);
#ifdef NO_TOUCH_HOLD
		}
		pressed = true;
	} else {
		pressed = false;
#endif
	}
}


void init_swatch(void)
{
	// Initialize system and Erika
	SystemInit();
	EE_system_init();

	// Initialize systick
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	// Initializes LCD and touchscreen
	IOE_Config();
	STM32f4_Discovery_LCD_Init();

	// Initialize serial debug
	debug_init();

	// Calibrate the touchscreen
	InitTouch(-0.112, 0.0623, -340, 11);

	// Initialize the buzzer
	buzzer_init();

	// Draw the background
	DrawInit(MyWatchScr);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(Black);
	LCD_DrawFullRect(28, 62, 200, 56);
	WPrint(&MyWatchScr[SEP1STR], ":");
	WPrint(&MyWatchScr[SEP2STR], ":");

	// Program periodic alarms
	SetRelAlarm(AlarmTaskClock, 10, 100);
	SetRelAlarm(AlarmTaskInterface, 10, 50);
	SetRelAlarm(AlarmTaskTouch, 10, 100);

	// Forever loop
	//for (;;) {}
}


