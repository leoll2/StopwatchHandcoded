#include "mock.h"

uint16_t alarm_task_alarm_buzzer = 0,
	alarm_task_stopwatch = 0,
	alarm_task_clock = 0,
	alarm_task_interface = 0,
	alarm_task_touch = 0;

uint16_t * const AlarmTaskAlarmBuzzer = &alarm_task_alarm_buzzer,
	* const AlarmTaskStopwatch = &alarm_task_stopwatch,
	* const AlarmTaskClock = &alarm_task_clock,
	* const AlarmTaskInterface = &alarm_task_interface,
	* const AlarmTaskTouch = &alarm_task_touch;

uint16_t my_counter;
uint16_t MyWatchScr[1];

uint16_t buzz_active;

void SystemInit(void) {}
void EE_system_init(void) {}
void EE_systick_set_period(uint16_t a) {}
void EE_systick_enable_int(void) {}
void EE_systick_start(void) {}
void IOE_Config(void) {}
void STM32f4_Discovery_LCD_Init(void) {}
void debug_init(void) {}
void InitTouch(float a, float b, float c, float d) {}
void display_time(Mode m) {}
void update_mode_visual(Mode m1, Mode m2) {}
void DrawInit(uint16_t* a) {}
void LCD_SetTextColor(uint16_t a) {}
void LCD_SetBackColor(uint16_t a) {}
void LCD_DrawFullRect(uint16_t a, uint16_t b, uint16_t c, uint16_t d) {}
void WPrint(uint16_t* a, char* b) {}
void CounterTick(uint16_t a) {}
unsigned char GetTouch_SC_Async(unsigned *a, unsigned *b) {return 1;}
void OnTouch(uint16_t* a, TPoint* p) {}

void buzzer_init(void) {
	buzz_active = 0;
}

void buzzer_unmute(void) {
	buzz_active = 1;
}

void buzzer_mute(void) {
	buzz_active = 0;
}

void SetRelAlarm(uint16_t * const a, uint16_t b, uint16_t c)
{
	*a = 1;
}

void CancelAlarm(uint16_t * const a) {
	*a = 0;
}
