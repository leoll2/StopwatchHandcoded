#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"

#include "event.h"
#include "swatch.h"

static CU_pSuite pSuite = NULL;


/* ########################################################################
 * SUITE 'EVENTS':
 * Test events. Ensure that set and reset commands are working properly
 * ######################################################################## */

int init_suite_events(void)
{
	return 0;
}

int clean_suite_events(void)
{
	return 0;
}

/* Test ClearEvents function.
 * Note: no guarantee yet that SetEvent() and IsEvent are working properly,
 * so these need to be validated in a future tests. */
void test_clear_events(void)
{
	ClearEvents();

	CU_ASSERT(!IsEvent(TIMEMODE_EV));
	CU_ASSERT(!IsEvent(TIMESETMODE_EV));
	CU_ASSERT(!IsEvent(ALARMMODE_EV));
	CU_ASSERT(!IsEvent(SWATCHMODE_EV));
	CU_ASSERT(!IsEvent(PLUS_EV));
	CU_ASSERT(!IsEvent(MINUS_EV));

	SetEvent(TIMEMODE_EV);
	SetEvent(TIMESETMODE_EV);
	SetEvent(ALARMMODE_EV);
	SetEvent(SWATCHMODE_EV);
	SetEvent(PLUS_EV);
	SetEvent(MINUS_EV);

	ClearEvents();

	CU_ASSERT(!IsEvent(TIMEMODE_EV));
	CU_ASSERT(!IsEvent(TIMESETMODE_EV));
	CU_ASSERT(!IsEvent(ALARMMODE_EV));
	CU_ASSERT(!IsEvent(SWATCHMODE_EV));
	CU_ASSERT(!IsEvent(PLUS_EV));
	CU_ASSERT(!IsEvent(MINUS_EV));
}

/* Test SetEvent and IsEvent functions.
 * Note: no guarantee yet that IsEvent is working properly. */
void test_set_event(void)
{
	ClearEvents();
	SetEvent(TIMEMODE_EV);
	CU_ASSERT(IsEvent(TIMEMODE_EV));
	CU_ASSERT(!IsEvent(TIMESETMODE_EV));
	CU_ASSERT(!IsEvent(ALARMMODE_EV));
	CU_ASSERT(!IsEvent(SWATCHMODE_EV));
	CU_ASSERT(!IsEvent(PLUS_EV));
	CU_ASSERT(!IsEvent(MINUS_EV));
	ClearEvents();

	ClearEvents();
	SetEvent(TIMESETMODE_EV);
	CU_ASSERT(!IsEvent(TIMEMODE_EV));
	CU_ASSERT(IsEvent(TIMESETMODE_EV));
	CU_ASSERT(!IsEvent(ALARMMODE_EV));
	CU_ASSERT(!IsEvent(SWATCHMODE_EV));
	CU_ASSERT(!IsEvent(PLUS_EV));
	CU_ASSERT(!IsEvent(MINUS_EV));
	ClearEvents();

	ClearEvents();
	SetEvent(ALARMMODE_EV);
	CU_ASSERT(!IsEvent(TIMEMODE_EV));
	CU_ASSERT(!IsEvent(TIMESETMODE_EV));
	CU_ASSERT(IsEvent(ALARMMODE_EV));
	CU_ASSERT(!IsEvent(SWATCHMODE_EV));
	CU_ASSERT(!IsEvent(PLUS_EV));
	CU_ASSERT(!IsEvent(MINUS_EV));
	ClearEvents();

	ClearEvents();
	SetEvent(SWATCHMODE_EV);
	CU_ASSERT(!IsEvent(TIMEMODE_EV));
	CU_ASSERT(!IsEvent(TIMESETMODE_EV));
	CU_ASSERT(!IsEvent(ALARMMODE_EV));
	CU_ASSERT(IsEvent(SWATCHMODE_EV));
	CU_ASSERT(!IsEvent(PLUS_EV));
	CU_ASSERT(!IsEvent(MINUS_EV));
	ClearEvents();

	ClearEvents();
	SetEvent(PLUS_EV);
	CU_ASSERT(!IsEvent(TIMEMODE_EV));
	CU_ASSERT(!IsEvent(TIMESETMODE_EV));
	CU_ASSERT(!IsEvent(ALARMMODE_EV));
	CU_ASSERT(!IsEvent(SWATCHMODE_EV));
	CU_ASSERT(IsEvent(PLUS_EV));
	CU_ASSERT(!IsEvent(MINUS_EV));
	ClearEvents();

	ClearEvents();
	SetEvent(MINUS_EV);
	CU_ASSERT(!IsEvent(TIMEMODE_EV));
	CU_ASSERT(!IsEvent(TIMESETMODE_EV));
	CU_ASSERT(!IsEvent(ALARMMODE_EV));
	CU_ASSERT(!IsEvent(SWATCHMODE_EV));
	CU_ASSERT(!IsEvent(PLUS_EV));
	CU_ASSERT(IsEvent(MINUS_EV));
	ClearEvents();
}

/* Test ClearEvent function. This implicitly tests IsEvent too. */
void test_clear_event(void)
{
	ClearEvents();

	SetEvent(TIMEMODE_EV);
	ClearEvent(TIMEMODE_EV);
	CU_ASSERT(!IsEvent(TIMEMODE_EV));

	SetEvent(TIMESETMODE_EV);
	ClearEvent(TIMESETMODE_EV);
	CU_ASSERT(!IsEvent(TIMESETMODE_EV));

	SetEvent(ALARMMODE_EV);
	ClearEvent(ALARMMODE_EV);
	CU_ASSERT(!IsEvent(ALARMMODE_EV));

	SetEvent(SWATCHMODE_EV);
	ClearEvent(SWATCHMODE_EV);
	CU_ASSERT(!IsEvent(SWATCHMODE_EV));

	SetEvent(PLUS_EV);
	ClearEvent(PLUS_EV);
	CU_ASSERT(!IsEvent(PLUS_EV));

	SetEvent(MINUS_EV);
	ClearEvent(MINUS_EV);
	CU_ASSERT(!IsEvent(MINUS_EV));
}


/* ########################################################################
 * SUITE 'MODES':
 * Test modes. Ensure that switching between modes works properly when the
 * corresponding event is generated.
 * ######################################################################## */

int init_suite_modes(void)
{
	return 0;
}

int clean_suite_modes(void)
{
	return 0;
}

/* Transition Tour between the 4 modes. Here below the sequence of nodes (abbreviated)
 * T -> TS -> A -> SW -> TS -> T -> A -> TS -> SW -> T -> SW -> A */
void test_mode_transitions(void)
{
	SetEvent(TIMEMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, TIMEMODE);

	SetEvent(TIMESETMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, TIMESETMODE);

	SetEvent(ALARMMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, ALARMMODE);

	SetEvent(SWATCHMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, SWATCHMODE);

	SetEvent(TIMESETMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, TIMESETMODE);

	SetEvent(TIMEMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, TIMEMODE);

	SetEvent(ALARMMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, ALARMMODE);

	SetEvent(TIMESETMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, TIMESETMODE);

	SetEvent(SWATCHMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, SWATCHMODE);

	SetEvent(TIMEMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, TIMEMODE);

	SetEvent(SWATCHMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, SWATCHMODE);

	SetEvent(ALARMMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, ALARMMODE);
}

/* Test TimesetMode sub-modes. */
void test_timeset_modes(void)
{
	SetEvent(TIMESETMODE_EV);
	TaskInterface();
	CU_ASSERT((tsmode == SETHOURS) || (tsmode == SETMINUTES));
	Mode pmode = tsmode;

	SetEvent(TIMESETMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, TIMESETMODE);
	CU_ASSERT((tsmode == SETHOURS) || (tsmode == SETMINUTES));
	CU_ASSERT_NOT_EQUAL(tsmode, pmode);
	pmode = tsmode;

	SetEvent(TIMESETMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, TIMESETMODE);
	CU_ASSERT((tsmode == SETHOURS) || (tsmode == SETMINUTES));
	CU_ASSERT_NOT_EQUAL(tsmode, pmode);
}

/* Test AlarmMode sub-modes. */
void test_alarm_modes(void)
{
	SetEvent(ALARMMODE_EV);
	TaskInterface();
	CU_ASSERT((asmode == ASETHOURS) || (asmode == ASETMINUTES));
	Mode pmode = asmode;

	SetEvent(ALARMMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, ALARMMODE);
	CU_ASSERT((asmode == ASETHOURS) || (asmode == ASETMINUTES));
	CU_ASSERT_NOT_EQUAL(asmode, pmode);
	pmode = asmode;

	SetEvent(ALARMMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, ALARMMODE);
	CU_ASSERT((asmode == ASETHOURS) || (asmode == ASETMINUTES));
	CU_ASSERT_NOT_EQUAL(asmode, pmode);
}


/* ########################################################################
 * SUITE 'CLOCK':
 * Make sure clock is counting the right time
 * ######################################################################## */

void reset_time()
{
	tenths = seconds = minutes = hours = 0;
}

bool is_equal_time(uint8_t h, uint8_t m, uint8_t s, uint8_t t)
{
	return (h == hours && m == minutes && s == seconds && t == tenths);
}

int init_suite_clock(void)
{
	reset_time();
	return 0;
}

int clean_suite_clock(void)
{
	return 0;
}

/* Test main clock. */
void test_main_clock(void)
{
	unsigned i = 0;

	CU_ASSERT(is_equal_time(0, 0, 0, 0));	// test reset
	TaskClock();
	CU_ASSERT(is_equal_time(0, 0, 0, 1));   // test tenths
	TaskClock();
	CU_ASSERT(is_equal_time(0, 0, 0, 2));

	reset_time();
	for (i = 0; i < 9; ++i)
		TaskClock();
	CU_ASSERT(is_equal_time(0, 0, 0, 9)); 	// test tenths
	TaskClock();
	CU_ASSERT(is_equal_time(0, 0, 1, 0));	// test tenths wrap

	reset_time();
	for (i = 0; i < 40; ++i) 				// 4 seconds
		TaskClock();
	CU_ASSERT(is_equal_time(0, 0, 4, 0));	// test seconds
	for (i = 0; i < 559; ++i) 				// 55.9 seconds more
		TaskClock();
	CU_ASSERT(is_equal_time(0, 0, 59, 9));	// test seconds
	TaskClock();							// 0.1 seconds more
	CU_ASSERT(is_equal_time(0, 1, 0, 0));	// test seconds wrap

	reset_time();
	for (i = 0; i < 4*600; ++i)				// 4 minutes
		TaskClock();
	CU_ASSERT(is_equal_time(0, 4, 0, 0));	// test minutes
	for (i = 0; i < (56*600-1); ++i) 		// 55 minutes, 59 seconds and 9 tenths more
		TaskClock();
	CU_ASSERT(is_equal_time(0, 59, 59, 9));	// test minutes
	TaskClock();
	CU_ASSERT(is_equal_time(1, 0, 0, 0));	// test minutes wrap

	reset_time();
	for (i = 0; i < 4*60*600; ++i)			// 4 hours
		TaskClock();
	CU_ASSERT(is_equal_time(4, 0, 0, 0));	// test hours
	for (i = 0; i < (20*60*600-1); ++i) 	// 20 hours, 59 minutes, 59 seconds and 9 tenths more
		TaskClock();
	CU_ASSERT(is_equal_time(23, 59, 59, 9));// test hours
	TaskClock();
	CU_ASSERT(is_equal_time(0, 0, 0, 0));	// test hours wrap
}



/* ########################################################################
 * SUITE 'STOPWATCH':
 * Make sure stopwatch clock is counting the right time
 * ######################################################################## */

void reset_swtime()
{
	s_tenths = s_seconds = s_minutes = 0;
}

bool is_equal_swtime(uint8_t m, uint8_t s, uint8_t t)
{
	return (m == s_minutes && s == s_seconds && t == s_tenths);
}

int init_suite_swatch(void)
{
	reset_swtime();
	return 0;
}

int clean_suite_swatch(void)
{
	return 0;
}

/* Test stopwatch clock. */
void test_swatch_clock(void)
{
	unsigned i = 0;

	CU_ASSERT(is_equal_swtime(0, 0, 0));	// test reset
	TaskStopwatch();
	CU_ASSERT(is_equal_swtime(0, 0, 1));    // test tenths
	TaskStopwatch();
	CU_ASSERT(is_equal_swtime(0, 0, 2));

	reset_swtime();
	for (i = 0; i < 9; ++i)
		TaskStopwatch();
	CU_ASSERT(is_equal_swtime(0, 0, 9)); 	// test tenths
	TaskStopwatch();
	CU_ASSERT(is_equal_swtime(0, 1, 0));	// test tenths wrap

	reset_swtime();
	for (i = 0; i < 40; ++i) 				// 4 seconds
		TaskStopwatch();
	CU_ASSERT(is_equal_swtime(0, 4, 0));	// test seconds
	for (i = 0; i < 559; ++i) 				// 55.9 seconds more
		TaskStopwatch();
	CU_ASSERT(is_equal_swtime(0, 59, 9));	// test seconds
	TaskStopwatch();						// 0.1 seconds more
	CU_ASSERT(is_equal_swtime(1, 0, 0));	// test seconds wrap

	reset_swtime();
	for (i = 0; i < 4*600; ++i)				// 4 minutes
		TaskStopwatch();
	CU_ASSERT(is_equal_swtime(4, 0, 0));	// test minutes
	for (i = 0; i < (56*600-1); ++i) 		// 55 minutes, 59 seconds and 9 tenths more
		TaskStopwatch();
	CU_ASSERT(is_equal_swtime(59, 59, 9));	// test minutes
	TaskStopwatch();
	CU_ASSERT(is_equal_swtime(0, 0, 0));	// test minutes wrap
}

void test_swatch_start_stop(void)
{
	reset_swtime();
	SetEvent(SWATCHMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, SWATCHMODE);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT(swatch_running);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT_FALSE(swatch_running);

	TaskStopwatch();
	CU_ASSERT(is_equal_swtime(0, 0, 1));
	SetEvent(MINUS_EV);
	TaskInterface();
	CU_ASSERT(is_equal_swtime(0, 0, 0));
}

/* ########################################################################
 * SUITE 'TIMESET':
 * Test increment and decrement in TimesetMode.
 * ######################################################################## */

int init_suite_timeset(void)
{
	SetEvent(TIMESETMODE_EV);
	TaskInterface();
	if (!tsmode == SETHOURS) {
		SetEvent(TIMESETMODE_EV);
		TaskInterface();
	}
	return 0;
}

int clean_suite_timeset(void)
{
	return 0;
}

/* Make sure that SetHours mode works as expected. */
void test_timeset_sethours(void)
{
	unsigned i = 0;

	reset_time();
	CU_ASSERT_EQUAL(mode, TIMESETMODE);
	CU_ASSERT_EQUAL(tsmode, SETHOURS);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(hours, 1); 		// test hours positive increment
	CU_ASSERT_EQUAL(minutes, 0);

	for (i = 0; i < 22; ++i) {
		SetEvent(PLUS_EV);
		TaskInterface();
	}
	CU_ASSERT_EQUAL(hours, 23); 	// test hours multiple increments
	CU_ASSERT_EQUAL(minutes, 0);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(hours, 0);		// test hours positive wrap
	CU_ASSERT_EQUAL(minutes, 0);

	SetEvent(MINUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(hours, 23);		// test hours negative wrap
	CU_ASSERT_EQUAL(minutes, 0);

	SetEvent(MINUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(hours, 22);		// test hours negative increment
	CU_ASSERT_EQUAL(minutes, 0);

}


/* Make sure that SetMinutes mode works as expected. */
void test_timeset_setminutes(void)
{
	unsigned i = 0;

	reset_time();
	SetEvent(TIMESETMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, TIMESETMODE);
	CU_ASSERT_EQUAL(tsmode, SETMINUTES);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(hours, 0); 		// test minutes positive increment
	CU_ASSERT_EQUAL(minutes, 1);

	for (i = 0; i < 58; ++i) {
		SetEvent(PLUS_EV);
		TaskInterface();
	}
	CU_ASSERT_EQUAL(hours, 0); 	 	// test minutes multiple increments
	CU_ASSERT_EQUAL(minutes, 59);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(hours, 0);		// test minutes positive wrap
	CU_ASSERT_EQUAL(minutes, 0);

	SetEvent(MINUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(hours, 0);		// test minutes negative wrap
	CU_ASSERT_EQUAL(minutes, 59);

	SetEvent(MINUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(hours, 0);		// test minutes negative increment
	CU_ASSERT_EQUAL(minutes, 58);
}


/* ########################################################################
 * SUITE 'ALARMSET':
 * Test increment and decrement in AlarmMode.
 * ######################################################################## */

void reset_alarm_time()
{
	a_hours = a_minutes = 0;
}

int init_suite_alarmset(void)
{
	SetEvent(ALARMMODE_EV);
	TaskInterface();
	if (!asmode == ASETHOURS) {
		SetEvent(ALARMMODE_EV);
		TaskInterface();
	}
	return 0;
}

int clean_suite_alarmset(void)
{
	return 0;
}

/* Make sure that SetHours mode works as expected. */
void test_alarmset_sethours(void)
{
	unsigned i = 0;

	reset_alarm_time();
	CU_ASSERT_EQUAL(mode, ALARMMODE);
	CU_ASSERT_EQUAL(asmode, ASETHOURS);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(a_hours, 1); 		// test a_hours positive increment
	CU_ASSERT_EQUAL(a_minutes, 0);

	for (i = 0; i < 22; ++i) {
		SetEvent(PLUS_EV);
		TaskInterface();
	}
	CU_ASSERT_EQUAL(a_hours, 23); 	// test a_hours multiple increments
	CU_ASSERT_EQUAL(a_minutes, 0);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(a_hours, 0);		// test a_hours positive wrap
	CU_ASSERT_EQUAL(a_minutes, 0);

	SetEvent(MINUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(a_hours, 23);		// test a_hours negative wrap
	CU_ASSERT_EQUAL(a_minutes, 0);

	SetEvent(MINUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(a_hours, 22);		// test a_hours negative increment
	CU_ASSERT_EQUAL(a_minutes, 0);

}


/* Make sure that SetMinutes mode works as expected. */
void test_alarmset_setminutes(void)
{
	unsigned i = 0;

	reset_alarm_time();
	SetEvent(ALARMMODE_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(mode, ALARMMODE);
	CU_ASSERT_EQUAL(asmode, ASETMINUTES);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(a_hours, 0); 		// test a_minutes positive increment
	CU_ASSERT_EQUAL(a_minutes, 1);

	for (i = 0; i < 58; ++i) {
		SetEvent(PLUS_EV);
		TaskInterface();
	}
	CU_ASSERT_EQUAL(a_hours, 0); 	 	// test a_minutes multiple increments
	CU_ASSERT_EQUAL(a_minutes, 59);

	SetEvent(PLUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(a_hours, 0);		// test a_minutes positive wrap
	CU_ASSERT_EQUAL(a_minutes, 0);

	SetEvent(MINUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(a_hours, 0);		// test a_minutes negative wrap
	CU_ASSERT_EQUAL(a_minutes, 59);

	SetEvent(MINUS_EV);
	TaskInterface();
	CU_ASSERT_EQUAL(a_hours, 0);		// test a_minutes negative increment
	CU_ASSERT_EQUAL(a_minutes, 58);
}


/* ########################################################################
 * SUITE 'BUZZER':
 * Make sure buzzer activation works as expected (software-side).
 * ######################################################################## */

int init_suite_buzzer(void)
{
	buzzer_init();
	return 0;
}

int clean_suite_buzzer(void)
{
	return 0;
}

/* Make sure that mocked buzzer functions work. */
void test_buzzer_mocks(void)
{
	buzzer_mute();
	CU_ASSERT_FALSE(buzz_active);
	buzzer_unmute();
	CU_ASSERT_TRUE(buzz_active);
	buzzer_mute();
	CU_ASSERT_FALSE(buzz_active);
}

void test_buzzer_beeps_number(void)
{
	unsigned beeps = 0;
	buzzer_mute();

	SetRelAlarm(AlarmTaskAlarmBuzzer, 0, 0);
	while(*AlarmTaskAlarmBuzzer) {
		TaskAlarmBuzzer();
		if (buzz_active)
			++beeps;
	}

	CU_ASSERT_EQUAL(beeps, N_BEEPS_ALARM);
}


/* Initialize CUnit registry and suites. */
CU_ErrorCode init_cunit(void)
{
	// Initialize test registry
	if (CUE_SUCCESS != CU_initialize_registry())
	  return CU_get_error();

	// Configure suite 'EVENTS'
	pSuite = CU_add_suite("Suite_events", init_suite_events, clean_suite_events);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "test_clear_events", test_clear_events)) ||
	   (NULL == CU_add_test(pSuite, "test_set_event", test_set_event)) ||
	   (NULL == CU_add_test(pSuite, "test_clear_event", test_clear_event)))
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// Configure suite 'MODES'
	pSuite = CU_add_suite("Suite_modes", init_suite_modes, clean_suite_modes);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "test_mode_transitions", test_mode_transitions)) ||
	   (NULL == CU_add_test(pSuite, "test_timeset_modes", test_timeset_modes)) ||
	   (NULL == CU_add_test(pSuite, "test_alarm_modes", test_alarm_modes)))
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// Configure suite 'CLOCK'
	pSuite = CU_add_suite("Suite_clock", init_suite_clock, clean_suite_clock);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "test_main_clock", test_main_clock)))
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// Configure suite 'STOPWATCH'
	pSuite = CU_add_suite("Suite_stopwatch", init_suite_swatch, clean_suite_swatch);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "test_swatch_clock", test_swatch_clock)) ||
		(NULL == CU_add_test(pSuite, "test_swatch_start_stop", test_swatch_start_stop)))
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// Configure suite 'TIMESET'
	pSuite = CU_add_suite("Suite_timeset", init_suite_timeset, clean_suite_timeset);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "test_timeset_sethours", test_timeset_sethours)) ||
		(NULL == CU_add_test(pSuite, "test_timeset_setminutes", test_timeset_setminutes)))
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// Configure suite 'ALARMSET'
	pSuite = CU_add_suite("Suite_alarmset", init_suite_alarmset, clean_suite_alarmset);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "test_alarmset_sethours", test_alarmset_sethours)) ||
		(NULL == CU_add_test(pSuite, "test_alarmset_setminutes", test_alarmset_setminutes)))
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// Configure suite 'BUZZER'
	pSuite = CU_add_suite("Suite_buzzer", init_suite_buzzer, clean_suite_buzzer);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "test_buzzer_mocks", test_buzzer_mocks)) ||
		(NULL == CU_add_test(pSuite, "test_buzzer_beeps_number", test_buzzer_beeps_number)))
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	return 0;
}

/* Cleanup CUnit registry */
CU_ErrorCode cleanup_cunit(void)
{
	// Clean up registry and return
	CU_cleanup_registry();
	return CU_get_error();
}


void run_cunit_tests(void)
{
	// Run all tests using console interface
	CU_console_run_tests();
	// CU_list_tests_to_file();
}


int main()
{
	init_cunit();

	init_swatch();

	run_cunit_tests();

	return cleanup_cunit();
}
