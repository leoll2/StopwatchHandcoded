/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SWatch.c
 *
 * Code generated for Simulink model 'SWatch'.
 *
 * Model version                  : 1.125
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Fri Jan 18 19:12:23 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "SWatch.h"
#include "SWatch_private.h"

/* Named constants for Chart: '<S1>/SWatch2018' */
#define SWatch_CALL_EVENT              (-1)
#define SWatch_IN_AlarmSet             ((uint8_T)1U)
#define SWatch_IN_BuzzHigh             ((uint8_T)1U)
#define SWatch_IN_BuzzLow              ((uint8_T)2U)
#define SWatch_IN_Buzzing              ((uint8_T)1U)
#define SWatch_IN_Count                ((uint8_T)1U)
#define SWatch_IN_Idle                 ((uint8_T)1U)
#define SWatch_IN_NO_ACTIVE_CHILD      ((uint8_T)0U)
#define SWatch_IN_Running              ((uint8_T)2U)
#define SWatch_IN_SetHours             ((uint8_T)1U)
#define SWatch_IN_SetMinutes           ((uint8_T)2U)
#define SWatch_IN_Silent               ((uint8_T)2U)
#define SWatch_IN_Stopwatch            ((uint8_T)2U)
#define SWatch_IN_TimeDisplay          ((uint8_T)3U)
#define SWatch_IN_TimeSet              ((uint8_T)4U)
#define SWatch_event_Tick              (3)
#define SWatch_event_alarmsetmode      (8)
#define SWatch_event_minusbutton       (5)
#define SWatch_event_plusbutton        (4)
#define SWatch_event_stopwatchpause    (0)
#define SWatch_event_stopwatchreset    (1)
#define SWatch_event_stopwatchstart    (2)
#define SWatch_event_swatchmode        (9)
#define SWatch_event_timemode          (6)
#define SWatch_event_timesetmode       (7)

/* user code (top of source file) */
#include "Buzzer.h"
#include "Event.h"
#include "WidgetConfig.h"

/* Forward declaration for local functions */
static void SWatch_StopwatchMgmt(DW_SWatch_T *SWatch_DW);
static void SWatch_Interface(uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
    uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode,
    DW_SWatch_T *SWatch_DW);
static void SWatch_chartstep_c3_SWatch(uint8_T *SWatch_Y_hours, uint8_T
    *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths,
    uint8_T *SWatch_Y_mode, B_SWatch_T *SWatch_B, DW_SWatch_T *SWatch_DW);

/* Function for Chart: '<S1>/SWatch2018' */
static void SWatch_StopwatchMgmt(DW_SWatch_T *SWatch_DW)
{
    int32_T tmp;
    if (SWatch_DW->sfEvent == SWatch_event_stopwatchreset) {
        SWatch_DW->Stenths = 0U;
        SWatch_DW->Sseconds = 0U;
        SWatch_DW->Sminutes = 0U;
        SWatch_DW->Shours = 0U;
        SWatch_DW->is_StopwatchMgmt = SWatch_IN_NO_ACTIVE_CHILD;
        switch (SWatch_DW->was_StopwatchMgmt) {
          case SWatch_IN_Idle:
            SWatch_DW->is_StopwatchMgmt = SWatch_IN_Idle;
            SWatch_DW->was_StopwatchMgmt = SWatch_IN_Idle;
            break;

          case SWatch_IN_Running:
            SWatch_DW->is_StopwatchMgmt = SWatch_IN_Running;
            SWatch_DW->was_StopwatchMgmt = SWatch_IN_Running;
            break;

          default:
            SWatch_DW->is_StopwatchMgmt = SWatch_IN_Idle;
            SWatch_DW->was_StopwatchMgmt = SWatch_IN_Idle;
            break;
        }
    } else {
        switch (SWatch_DW->is_StopwatchMgmt) {
          case SWatch_IN_Idle:
            if (SWatch_DW->sfEvent == SWatch_event_stopwatchstart) {
                SWatch_DW->is_StopwatchMgmt = SWatch_IN_Running;
                SWatch_DW->was_StopwatchMgmt = SWatch_IN_Running;
            }
            break;

          case SWatch_IN_Running:
            switch (SWatch_DW->sfEvent) {
              case SWatch_event_stopwatchpause:
                SWatch_DW->is_StopwatchMgmt = SWatch_IN_Idle;
                SWatch_DW->was_StopwatchMgmt = SWatch_IN_Idle;
                break;

              case SWatch_event_Tick:
                if (SWatch_DW->Stenths == 9) {
                    SWatch_DW->Stenths = 0U;
                    if (SWatch_DW->Sseconds == 59) {
                        SWatch_DW->Sseconds = 0U;
                        if (SWatch_DW->Sminutes == 59) {
                            SWatch_DW->Sminutes = 0U;
                            if (SWatch_DW->Shours == 23) {
                                SWatch_DW->Shours = 0U;
                            } else {
                                tmp = (int32_T)(SWatch_DW->Shours + 1U);
                                if ((uint32_T)tmp > 255U) {
                                    tmp = 255;
                                }

                                SWatch_DW->Shours = (uint8_T)tmp;
                            }
                        } else {
                            tmp = (int32_T)(SWatch_DW->Sminutes + 1U);
                            if ((uint32_T)tmp > 255U) {
                                tmp = 255;
                            }

                            SWatch_DW->Sminutes = (uint8_T)tmp;
                        }
                    } else {
                        tmp = (int32_T)(SWatch_DW->Sseconds + 1U);
                        if ((uint32_T)tmp > 255U) {
                            tmp = 255;
                        }

                        SWatch_DW->Sseconds = (uint8_T)tmp;
                    }
                } else {
                    tmp = (int32_T)(SWatch_DW->Stenths + 1U);
                    if ((uint32_T)tmp > 255U) {
                        tmp = 255;
                    }

                    SWatch_DW->Stenths = (uint8_T)tmp;
                }

                SWatch_DW->is_StopwatchMgmt = SWatch_IN_Running;
                SWatch_DW->was_StopwatchMgmt = SWatch_IN_Running;
                break;
            }
            break;
        }
    }
}

/* Function for Chart: '<S1>/SWatch2018' */
static void SWatch_Interface(uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
    uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode,
    DW_SWatch_T *SWatch_DW)
{
    int32_T b_previousEvent;
    uint32_T qY;
    switch (SWatch_DW->sfEvent) {
      case SWatch_event_timemode:
        SWatch_DW->is_AlarmSet = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_Interface = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_Stopwatch = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_TimeSet = SWatch_IN_NO_ACTIVE_CHILD;
        if (SWatch_DW->is_Interface != SWatch_IN_TimeDisplay) {
            SWatch_DW->is_Interface = SWatch_IN_TimeDisplay;

            /* Outport: '<Root>/mode' */
            *SWatch_Y_mode = 0U;
        }
        break;

      case SWatch_event_swatchmode:
        SWatch_DW->is_AlarmSet = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_Interface = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_Stopwatch = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_TimeSet = SWatch_IN_NO_ACTIVE_CHILD;
        if (SWatch_DW->is_Interface != SWatch_IN_Stopwatch) {
            SWatch_DW->is_Interface = SWatch_IN_Stopwatch;

            /* Outport: '<Root>/mode' */
            *SWatch_Y_mode = 3U;
        }

        switch (SWatch_DW->was_Stopwatch) {
          case SWatch_IN_Idle:
            SWatch_DW->is_Stopwatch = SWatch_IN_Idle;
            SWatch_DW->was_Stopwatch = SWatch_IN_Idle;
            break;

          case SWatch_IN_Running:
            SWatch_DW->is_Stopwatch = SWatch_IN_Running;
            SWatch_DW->was_Stopwatch = SWatch_IN_Running;
            break;

          default:
            SWatch_DW->is_Stopwatch = SWatch_IN_Idle;
            SWatch_DW->was_Stopwatch = SWatch_IN_Idle;
            break;
        }
        break;

      default:
        switch (SWatch_DW->is_Interface) {
          case SWatch_IN_AlarmSet:
            /* Outport: '<Root>/mode' */
            *SWatch_Y_mode = 2U;
            if (SWatch_DW->sfEvent == SWatch_event_timesetmode) {
                SWatch_DW->is_AlarmSet = SWatch_IN_NO_ACTIVE_CHILD;
                SWatch_DW->is_Interface = SWatch_IN_TimeSet;

                /* Outport: '<Root>/mode' */
                *SWatch_Y_mode = 1U;
                if (SWatch_DW->is_TimeSet != SWatch_IN_SetHours) {
                    SWatch_DW->is_TimeSet = SWatch_IN_SetHours;
                }
            } else {
                /* Outport: '<Root>/hours' */
                *SWatch_Y_hours = SWatch_DW->Ahours;

                /* Outport: '<Root>/minutes' */
                *SWatch_Y_minutes = SWatch_DW->Aminutes;
                switch (SWatch_DW->is_AlarmSet) {
                  case SWatch_IN_SetHours:
                    switch (SWatch_DW->sfEvent) {
                      case SWatch_event_plusbutton:
                        if (SWatch_DW->Ahours == 23) {
                            SWatch_DW->Ahours = 0U;
                            SWatch_DW->is_AlarmSet = SWatch_IN_SetHours;
                        } else {
                            b_previousEvent = (int32_T)(SWatch_DW->Ahours + 1U);
                            if ((uint32_T)b_previousEvent > 255U) {
                                b_previousEvent = 255;
                            }

                            SWatch_DW->Ahours = (uint8_T)b_previousEvent;
                            SWatch_DW->is_AlarmSet = SWatch_IN_SetHours;
                        }
                        break;

                      case SWatch_event_alarmsetmode:
                        SWatch_DW->is_AlarmSet = SWatch_IN_SetMinutes;
                        break;

                      case SWatch_event_minusbutton:
                        if (SWatch_DW->Ahours == 0) {
                            SWatch_DW->Ahours = 23U;
                            SWatch_DW->is_AlarmSet = SWatch_IN_SetHours;
                        } else {
                            qY = SWatch_DW->Ahours - /*MW:OvSatOk*/ 1U;
                            if (qY > SWatch_DW->Ahours) {
                                qY = 0U;
                            }

                            SWatch_DW->Ahours = (uint8_T)qY;
                            SWatch_DW->is_AlarmSet = SWatch_IN_SetHours;
                        }
                        break;
                    }
                    break;

                  case SWatch_IN_SetMinutes:
                    switch (SWatch_DW->sfEvent) {
                      case SWatch_event_plusbutton:
                        if (SWatch_DW->Aminutes == 59) {
                            SWatch_DW->Aminutes = 0U;
                            SWatch_DW->is_AlarmSet = SWatch_IN_SetMinutes;
                        } else {
                            b_previousEvent = (int32_T)(SWatch_DW->Aminutes + 1U);
                            if ((uint32_T)b_previousEvent > 255U) {
                                b_previousEvent = 255;
                            }

                            SWatch_DW->Aminutes = (uint8_T)b_previousEvent;
                            SWatch_DW->is_AlarmSet = SWatch_IN_SetMinutes;
                        }
                        break;

                      case SWatch_event_minusbutton:
                        if (SWatch_DW->Aminutes == 0) {
                            SWatch_DW->Aminutes = 59U;
                            SWatch_DW->is_AlarmSet = SWatch_IN_SetMinutes;
                        } else {
                            qY = SWatch_DW->Aminutes - /*MW:OvSatOk*/ 1U;
                            if (qY > SWatch_DW->Aminutes) {
                                qY = 0U;
                            }

                            SWatch_DW->Aminutes = (uint8_T)qY;
                            SWatch_DW->is_AlarmSet = SWatch_IN_SetMinutes;
                        }
                        break;

                      case SWatch_event_alarmsetmode:
                        SWatch_DW->is_AlarmSet = SWatch_IN_SetHours;
                        break;
                    }
                    break;
                }
            }
            break;

          case SWatch_IN_Stopwatch:
            /* Outport: '<Root>/mode' */
            *SWatch_Y_mode = 3U;
            switch (SWatch_DW->sfEvent) {
              case SWatch_event_timesetmode:
                SWatch_DW->is_Stopwatch = SWatch_IN_NO_ACTIVE_CHILD;
                SWatch_DW->is_Interface = SWatch_IN_TimeSet;

                /* Outport: '<Root>/mode' */
                *SWatch_Y_mode = 1U;
                if (SWatch_DW->is_TimeSet != SWatch_IN_SetHours) {
                    SWatch_DW->is_TimeSet = SWatch_IN_SetHours;
                }
                break;

              case SWatch_event_alarmsetmode:
                SWatch_DW->is_Stopwatch = SWatch_IN_NO_ACTIVE_CHILD;
                SWatch_DW->is_Interface = SWatch_IN_AlarmSet;

                /* Outport: '<Root>/mode' */
                *SWatch_Y_mode = 2U;
                SWatch_DW->is_AlarmSet = SWatch_IN_SetHours;
                break;

              default:
                /* Outport: '<Root>/hours' */
                *SWatch_Y_hours = SWatch_DW->Shours;

                /* Outport: '<Root>/minutes' */
                *SWatch_Y_minutes = SWatch_DW->Sminutes;

                /* Outport: '<Root>/seconds' */
                *SWatch_Y_seconds = SWatch_DW->Sseconds;

                /* Outport: '<Root>/tenths' */
                *SWatch_Y_tenths = SWatch_DW->Stenths;
                if (SWatch_DW->sfEvent == SWatch_event_minusbutton) {
                    b_previousEvent = SWatch_DW->sfEvent;
                    SWatch_DW->sfEvent = SWatch_event_stopwatchreset;
                    if (SWatch_DW->is_active_StopwatchMgmt != 0U) {
                        SWatch_StopwatchMgmt(SWatch_DW);
                    }

                    SWatch_DW->sfEvent = b_previousEvent;
                    SWatch_DW->is_Stopwatch = SWatch_IN_NO_ACTIVE_CHILD;
                    switch (SWatch_DW->was_Stopwatch) {
                      case SWatch_IN_Idle:
                        SWatch_DW->is_Stopwatch = SWatch_IN_Idle;
                        SWatch_DW->was_Stopwatch = SWatch_IN_Idle;
                        break;

                      case SWatch_IN_Running:
                        SWatch_DW->is_Stopwatch = SWatch_IN_Running;
                        SWatch_DW->was_Stopwatch = SWatch_IN_Running;
                        break;

                      default:
                        SWatch_DW->is_Stopwatch = SWatch_IN_Idle;
                        SWatch_DW->was_Stopwatch = SWatch_IN_Idle;
                        break;
                    }
                } else {
                    switch (SWatch_DW->is_Stopwatch) {
                      case SWatch_IN_Idle:
                        if (SWatch_DW->sfEvent == SWatch_event_plusbutton) {
                            b_previousEvent = SWatch_DW->sfEvent;
                            SWatch_DW->sfEvent = SWatch_event_stopwatchstart;
                            if (SWatch_DW->is_active_StopwatchMgmt != 0U) {
                                SWatch_StopwatchMgmt(SWatch_DW);
                            }

                            SWatch_DW->sfEvent = b_previousEvent;
                            SWatch_DW->is_Stopwatch = SWatch_IN_Running;
                            SWatch_DW->was_Stopwatch = SWatch_IN_Running;
                        }
                        break;

                      case SWatch_IN_Running:
                        if (SWatch_DW->sfEvent == SWatch_event_plusbutton) {
                            b_previousEvent = SWatch_DW->sfEvent;
                            SWatch_DW->sfEvent = SWatch_event_stopwatchpause;
                            if (SWatch_DW->is_active_StopwatchMgmt != 0U) {
                                SWatch_StopwatchMgmt(SWatch_DW);
                            }

                            SWatch_DW->sfEvent = b_previousEvent;
                            SWatch_DW->is_Stopwatch = SWatch_IN_Idle;
                            SWatch_DW->was_Stopwatch = SWatch_IN_Idle;
                        }
                        break;
                    }
                }
                break;
            }
            break;

          case SWatch_IN_TimeDisplay:
            /* Outport: '<Root>/mode' */
            *SWatch_Y_mode = 0U;
            switch (SWatch_DW->sfEvent) {
              case SWatch_event_timesetmode:
                SWatch_DW->is_Interface = SWatch_IN_TimeSet;

                /* Outport: '<Root>/mode' */
                *SWatch_Y_mode = 1U;
                if (SWatch_DW->is_TimeSet != SWatch_IN_SetHours) {
                    SWatch_DW->is_TimeSet = SWatch_IN_SetHours;
                }
                break;

              case SWatch_event_alarmsetmode:
                SWatch_DW->is_Interface = SWatch_IN_AlarmSet;

                /* Outport: '<Root>/mode' */
                *SWatch_Y_mode = 2U;
                SWatch_DW->is_AlarmSet = SWatch_IN_SetHours;
                break;

              default:
                /* Outport: '<Root>/hours' */
                *SWatch_Y_hours = SWatch_DW->hours;

                /* Outport: '<Root>/minutes' */
                *SWatch_Y_minutes = SWatch_DW->minutes;

                /* Outport: '<Root>/seconds' */
                *SWatch_Y_seconds = SWatch_DW->seconds;
                break;
            }
            break;

          case SWatch_IN_TimeSet:
            /* Outport: '<Root>/mode' */
            *SWatch_Y_mode = 1U;
            if (SWatch_DW->sfEvent == SWatch_event_alarmsetmode) {
                SWatch_DW->is_TimeSet = SWatch_IN_NO_ACTIVE_CHILD;
                SWatch_DW->is_Interface = SWatch_IN_AlarmSet;

                /* Outport: '<Root>/mode' */
                *SWatch_Y_mode = 2U;
                SWatch_DW->is_AlarmSet = SWatch_IN_SetHours;
            } else {
                /* Outport: '<Root>/hours' */
                *SWatch_Y_hours = SWatch_DW->hours;

                /* Outport: '<Root>/minutes' */
                *SWatch_Y_minutes = SWatch_DW->minutes;
                switch (SWatch_DW->is_TimeSet) {
                  case SWatch_IN_SetHours:
                    switch (SWatch_DW->sfEvent) {
                      case SWatch_event_plusbutton:
                        if (SWatch_DW->hours == 23) {
                            SWatch_DW->hours = 0U;
                            SWatch_DW->is_TimeSet = SWatch_IN_SetHours;
                        } else {
                            b_previousEvent = (int32_T)(SWatch_DW->hours + 1U);
                            if ((uint32_T)b_previousEvent > 255U) {
                                b_previousEvent = 255;
                            }

                            SWatch_DW->hours = (uint8_T)b_previousEvent;
                            SWatch_DW->is_TimeSet = SWatch_IN_SetHours;
                        }
                        break;

                      case SWatch_event_timesetmode:
                        SWatch_DW->is_TimeSet = SWatch_IN_SetMinutes;
                        break;

                      case SWatch_event_minusbutton:
                        if (SWatch_DW->hours == 0) {
                            SWatch_DW->hours = 23U;
                            SWatch_DW->is_TimeSet = SWatch_IN_SetHours;
                        } else {
                            qY = SWatch_DW->hours - /*MW:OvSatOk*/ 1U;
                            if (qY > SWatch_DW->hours) {
                                qY = 0U;
                            }

                            SWatch_DW->hours = (uint8_T)qY;
                            SWatch_DW->is_TimeSet = SWatch_IN_SetHours;
                        }
                        break;
                    }
                    break;

                  case SWatch_IN_SetMinutes:
                    switch (SWatch_DW->sfEvent) {
                      case SWatch_event_plusbutton:
                        if (SWatch_DW->minutes == 59) {
                            SWatch_DW->minutes = 0U;
                            SWatch_DW->is_TimeSet = SWatch_IN_SetMinutes;
                        } else {
                            b_previousEvent = (int32_T)(SWatch_DW->minutes + 1U);
                            if ((uint32_T)b_previousEvent > 255U) {
                                b_previousEvent = 255;
                            }

                            SWatch_DW->minutes = (uint8_T)b_previousEvent;
                            SWatch_DW->is_TimeSet = SWatch_IN_SetMinutes;
                        }
                        break;

                      case SWatch_event_minusbutton:
                        if (SWatch_DW->minutes == 0) {
                            SWatch_DW->minutes = 59U;
                            SWatch_DW->is_TimeSet = SWatch_IN_SetMinutes;
                        } else {
                            qY = SWatch_DW->minutes - /*MW:OvSatOk*/ 1U;
                            if (qY > SWatch_DW->minutes) {
                                qY = 0U;
                            }

                            SWatch_DW->minutes = (uint8_T)qY;
                            SWatch_DW->is_TimeSet = SWatch_IN_SetMinutes;
                        }
                        break;

                      case SWatch_event_timesetmode:
                        SWatch_DW->is_TimeSet = SWatch_IN_SetHours;
                        break;
                    }
                    break;
                }
            }
            break;
        }
        break;
    }
}

/* Function for Chart: '<S1>/SWatch2018' */
static void SWatch_chartstep_c3_SWatch(uint8_T *SWatch_Y_hours, uint8_T
    *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths,
    uint8_T *SWatch_Y_mode, B_SWatch_T *SWatch_B, DW_SWatch_T *SWatch_DW)
{
    int32_T tmp;
    if (SWatch_DW->is_active_Interface != 0U) {
        SWatch_Interface(SWatch_Y_hours, SWatch_Y_minutes, SWatch_Y_seconds,
                         SWatch_Y_tenths, SWatch_Y_mode, SWatch_DW);
    }

    if (!((SWatch_DW->is_active_TimeCount == 0U) || (SWatch_DW->is_TimeCount !=
            SWatch_IN_Count) || (!(SWatch_DW->sfEvent == SWatch_event_Tick)))) {
        if (SWatch_DW->tenths == 9) {
            SWatch_DW->tenths = 0U;
            if (SWatch_DW->seconds == 59) {
                SWatch_DW->seconds = 0U;
                if (SWatch_DW->minutes == 59) {
                    SWatch_DW->minutes = 0U;
                    if (SWatch_DW->hours == 23) {
                        SWatch_DW->hours = 0U;
                    } else {
                        tmp = (int32_T)(SWatch_DW->hours + 1U);
                        if ((uint32_T)tmp > 255U) {
                            tmp = 255;
                        }

                        SWatch_DW->hours = (uint8_T)tmp;
                    }
                } else {
                    tmp = (int32_T)(SWatch_DW->minutes + 1U);
                    if ((uint32_T)tmp > 255U) {
                        tmp = 255;
                    }

                    SWatch_DW->minutes = (uint8_T)tmp;
                }
            } else {
                tmp = (int32_T)(SWatch_DW->seconds + 1U);
                if ((uint32_T)tmp > 255U) {
                    tmp = 255;
                }

                SWatch_DW->seconds = (uint8_T)tmp;
            }
        } else {
            tmp = (int32_T)(SWatch_DW->tenths + 1U);
            if ((uint32_T)tmp > 255U) {
                tmp = 255;
            }

            SWatch_DW->tenths = (uint8_T)tmp;
        }

        SWatch_DW->is_TimeCount = SWatch_IN_Count;
    }

    if (SWatch_DW->is_active_AlarmMgmt != 0U) {
        switch (SWatch_DW->is_AlarmMgmt) {
          case SWatch_IN_Buzzing:
            if ((SWatch_DW->Ahours != SWatch_DW->hours) || (SWatch_DW->Aminutes
                    != SWatch_DW->minutes) || (SWatch_DW->seconds > 5)) {
                SWatch_DW->is_Buzzing = SWatch_IN_NO_ACTIVE_CHILD;
                SWatch_DW->is_AlarmMgmt = SWatch_IN_Silent;
                SWatch_B->buzz = false;
            } else {
                switch (SWatch_DW->is_Buzzing) {
                  case SWatch_IN_BuzzHigh:
                    if ((SWatch_DW->sfEvent == SWatch_event_Tick) &&
                            (SWatch_DW->tenths == 0)) {
                        SWatch_B->buzz = false;
                        SWatch_DW->is_Buzzing = SWatch_IN_BuzzLow;
                    }
                    break;

                  case SWatch_IN_BuzzLow:
                    if ((SWatch_DW->sfEvent == SWatch_event_Tick) &&
                            (SWatch_DW->tenths == 0)) {
                        SWatch_B->buzz = true;
                        SWatch_DW->is_Buzzing = SWatch_IN_BuzzHigh;
                    }
                    break;
                }
            }
            break;

          case SWatch_IN_Silent:
            if ((SWatch_DW->Ahours == SWatch_DW->hours) && (SWatch_DW->Aminutes ==
                 SWatch_DW->minutes) && (SWatch_DW->seconds == 0)) {
                SWatch_DW->is_AlarmMgmt = SWatch_IN_Buzzing;
                SWatch_B->buzz = true;
                SWatch_DW->is_Buzzing = SWatch_IN_BuzzHigh;
            }
            break;
        }
    }

    if (SWatch_DW->is_active_StopwatchMgmt != 0U) {
        SWatch_StopwatchMgmt(SWatch_DW);
    }
}

/* Model step function */
void SWatch_step(RT_MODEL_SWatch_T *const SWatch_M, uint8_T *SWatch_Y_hours,
                 uint8_T *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds, uint8_T
                 *SWatch_Y_tenths, uint8_T *SWatch_Y_mode)
{
    B_SWatch_T *SWatch_B = ((B_SWatch_T *) SWatch_M->blockIO);
    DW_SWatch_T *SWatch_DW = ((DW_SWatch_T *) SWatch_M->dwork);
    PrevZCX_SWatch_T *SWatch_PrevZCX = ((PrevZCX_SWatch_T *)
        SWatch_M->prevZCSigState);
    boolean_T zcEvent[7];
    boolean_T tmp;
    int32_T i;

    /* S-Function (button_read): '<S1>/plus_button' incorporates:
     *  Inport: '<Root>/plusbutton'
     */
    /* S-Function Block: <S1>/plus_button */
    /* Button PLUS */
    SWatch_B->plus_button = IsEvent(PLUS);

    /* S-Function (button_read): '<S1>/minus_button' incorporates:
     *  Inport: '<Root>/minusbutton'
     */
    /* S-Function Block: <S1>/minus_button */
    /* Button MINUS */
    SWatch_B->minus_button = IsEvent(MINUS);

    /* S-Function (button_read): '<S1>/timemode_button' incorporates:
     *  Inport: '<Root>/timemode'
     */
    /* S-Function Block: <S1>/timemode_button */
    /* Button TIMEMODE */
    SWatch_B->timemode_button = IsEvent(TIMEMODE);

    /* S-Function (button_read): '<S1>/timesetmode_button' incorporates:
     *  Inport: '<Root>/timesetmode'
     */
    /* S-Function Block: <S1>/timesetmode_button */
    /* Button TIMESETMODE */
    SWatch_B->timesetmode_button = IsEvent(TIMESETMODE);

    /* S-Function (button_read): '<S1>/alarmsetmode_button' incorporates:
     *  Inport: '<Root>/alarmsetmode'
     */
    /* S-Function Block: <S1>/alarmsetmode_button */
    /* Button ALARMMODE */
    SWatch_B->alarmsetmode_button = IsEvent(ALARMMODE);

    /* S-Function (button_read): '<S1>/swatchmode_button' incorporates:
     *  Inport: '<Root>/swatchmode'
     */
    /* S-Function Block: <S1>/swatchmode_button */
    /* Button SWATCHMODE */
    SWatch_B->swatchmode_button = IsEvent(SWATCHMODE);

    /* Chart: '<S1>/SWatch2018' incorporates:
     *  TriggerPort: '<S3>/input events'
     */
    /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
     *  UnitDelay: '<S2>/Output'
     */
    zcEvent[0] = (((SWatch_DW->Output_DSTATE != 0) !=
                   (SWatch_PrevZCX->SWatch2018_Trig_ZCE[0] == POS_ZCSIG)) &&
                  (SWatch_PrevZCX->SWatch2018_Trig_ZCE[0] != UNINITIALIZED_ZCSIG));
    zcEvent[1] = (((SWatch_PrevZCX->SWatch2018_Trig_ZCE[1] == POS_ZCSIG) !=
                   (int32_T)SWatch_B->plus_button) &&
                  (SWatch_PrevZCX->SWatch2018_Trig_ZCE[1] != UNINITIALIZED_ZCSIG));
    zcEvent[2] = (((SWatch_PrevZCX->SWatch2018_Trig_ZCE[2] == POS_ZCSIG) !=
                   (int32_T)SWatch_B->minus_button) &&
                  (SWatch_PrevZCX->SWatch2018_Trig_ZCE[2] != UNINITIALIZED_ZCSIG));
    zcEvent[3] = (((SWatch_PrevZCX->SWatch2018_Trig_ZCE[3] == POS_ZCSIG) !=
                   (int32_T)SWatch_B->timemode_button) &&
                  (SWatch_PrevZCX->SWatch2018_Trig_ZCE[3] != UNINITIALIZED_ZCSIG));
    zcEvent[4] = (((SWatch_PrevZCX->SWatch2018_Trig_ZCE[4] == POS_ZCSIG) !=
                   (int32_T)SWatch_B->timesetmode_button) &&
                  (SWatch_PrevZCX->SWatch2018_Trig_ZCE[4] != UNINITIALIZED_ZCSIG));
    zcEvent[5] = (((SWatch_PrevZCX->SWatch2018_Trig_ZCE[5] == POS_ZCSIG) !=
                   (int32_T)SWatch_B->alarmsetmode_button) &&
                  (SWatch_PrevZCX->SWatch2018_Trig_ZCE[5] != UNINITIALIZED_ZCSIG));
    zcEvent[6] = (((SWatch_PrevZCX->SWatch2018_Trig_ZCE[6] == POS_ZCSIG) !=
                   (int32_T)SWatch_B->swatchmode_button) &&
                  (SWatch_PrevZCX->SWatch2018_Trig_ZCE[6] != UNINITIALIZED_ZCSIG));
    tmp = false;
    for (i = 0; i < 7; i++) {
        tmp = (tmp || zcEvent[i]);
    }

    if (tmp) {
        /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
         *  UnitDelay: '<S2>/Output'
         */
        if ((int8_T)(zcEvent[0] ? SWatch_DW->Output_DSTATE != 0 ? RISING_ZCEVENT
                     : FALLING_ZCEVENT : NO_ZCEVENT) != 0) {
            SWatch_DW->sfEvent = SWatch_event_Tick;
            SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
                SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_B,
                SWatch_DW);
        }

        if ((int8_T)(zcEvent[1] ? SWatch_B->plus_button ? RISING_ZCEVENT :
                     FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
            SWatch_DW->sfEvent = SWatch_event_plusbutton;
            SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
                SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_B,
                SWatch_DW);
        }

        if ((int8_T)(zcEvent[2] ? SWatch_B->minus_button ? RISING_ZCEVENT :
                     FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
            SWatch_DW->sfEvent = SWatch_event_minusbutton;
            SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
                SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_B,
                SWatch_DW);
        }

        if ((int8_T)(zcEvent[3] ? SWatch_B->timemode_button ? RISING_ZCEVENT :
                     FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
            SWatch_DW->sfEvent = SWatch_event_timemode;
            SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
                SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_B,
                SWatch_DW);
        }

        if ((int8_T)(zcEvent[4] ? SWatch_B->timesetmode_button ? RISING_ZCEVENT :
                     FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
            SWatch_DW->sfEvent = SWatch_event_timesetmode;
            SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
                SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_B,
                SWatch_DW);
        }

        if ((int8_T)(zcEvent[5] ? SWatch_B->alarmsetmode_button ? RISING_ZCEVENT
                     : FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
            SWatch_DW->sfEvent = SWatch_event_alarmsetmode;
            SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
                SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_B,
                SWatch_DW);
        }

        if ((int8_T)(zcEvent[6] ? SWatch_B->swatchmode_button ? RISING_ZCEVENT :
                     FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
            SWatch_DW->sfEvent = SWatch_event_swatchmode;
            SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
                SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_B,
                SWatch_DW);
        }
    }

    /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
     *  UnitDelay: '<S2>/Output'
     */
    SWatch_PrevZCX->SWatch2018_Trig_ZCE[0] = (ZCSigState)
        (SWatch_DW->Output_DSTATE != 0);
    SWatch_PrevZCX->SWatch2018_Trig_ZCE[1] = SWatch_B->plus_button;
    SWatch_PrevZCX->SWatch2018_Trig_ZCE[2] = SWatch_B->minus_button;
    SWatch_PrevZCX->SWatch2018_Trig_ZCE[3] = SWatch_B->timemode_button;
    SWatch_PrevZCX->SWatch2018_Trig_ZCE[4] = SWatch_B->timesetmode_button;
    SWatch_PrevZCX->SWatch2018_Trig_ZCE[5] = SWatch_B->alarmsetmode_button;
    SWatch_PrevZCX->SWatch2018_Trig_ZCE[6] = SWatch_B->swatchmode_button;

    /* S-Function (buzzer): '<S1>/buzzer' */
    /* S-Function Block: <S1>/buzzer */
    /* Buzzer  */
    if (SWatch_B->buzz == 0)
        Buzzer_mute();
    else
        Buzzer_unmute();

    /* Sum: '<S4>/FixPt Sum1' incorporates:
     *  Constant: '<S4>/FixPt Constant'
     *  UnitDelay: '<S2>/Output'
     */
    SWatch_DW->Output_DSTATE++;

    /* Switch: '<S5>/FixPt Switch' incorporates:
     *  Constant: '<S5>/Constant'
     *  UnitDelay: '<S2>/Output'
     */
    if (SWatch_DW->Output_DSTATE > 1) {
        SWatch_DW->Output_DSTATE = 0U;
    }

    /* End of Switch: '<S5>/FixPt Switch' */
}

/* Model initialize function */
void SWatch_initialize(RT_MODEL_SWatch_T *const SWatch_M, boolean_T
                       *SWatch_U_plusbutton, boolean_T *SWatch_U_minusbutton,
                       boolean_T *SWatch_U_timemode, boolean_T
                       *SWatch_U_timesetmode, boolean_T *SWatch_U_alarmsetmode,
                       boolean_T *SWatch_U_swatchmode, uint8_T *SWatch_Y_hours,
                       uint8_T *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds,
                       uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode)
{
    B_SWatch_T *SWatch_B = ((B_SWatch_T *) SWatch_M->blockIO);
    DW_SWatch_T *SWatch_DW = ((DW_SWatch_T *) SWatch_M->dwork);
    PrevZCX_SWatch_T *SWatch_PrevZCX = ((PrevZCX_SWatch_T *)
        SWatch_M->prevZCSigState);

    {
        int32_T i;

        /* Start for S-Function (buzzer): '<S1>/buzzer' */
        Buzzer_init();
        for (i = 0; i < 7; i++) {
            SWatch_PrevZCX->SWatch2018_Trig_ZCE[i] = UNINITIALIZED_ZCSIG;
        }

        /* SystemInitialize for Chart: '<S1>/SWatch2018' */
        SWatch_DW->is_active_AlarmMgmt = 0U;
        SWatch_DW->is_AlarmMgmt = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_Buzzing = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_active_Interface = 0U;
        SWatch_DW->is_Interface = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_AlarmSet = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_Stopwatch = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->was_Stopwatch = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_TimeSet = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_active_StopwatchMgmt = 0U;
        SWatch_DW->is_StopwatchMgmt = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->was_StopwatchMgmt = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_active_TimeCount = 0U;
        SWatch_DW->is_TimeCount = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->sfEvent = SWatch_CALL_EVENT;

        /* Chart: '<S1>/SWatch2018' */
        if (SWatch_DW->is_active_Interface != 1U) {
            SWatch_DW->is_active_Interface = 1U;
            SWatch_DW->seconds = 0U;
            SWatch_DW->minutes = 0U;
            SWatch_DW->hours = 0U;
            SWatch_DW->Ahours = 0U;
            SWatch_DW->Aminutes = 0U;
        }

        if (SWatch_DW->is_Interface != SWatch_IN_TimeDisplay) {
            SWatch_DW->is_Interface = SWatch_IN_TimeDisplay;

            /* Outport: '<Root>/mode' */
            *SWatch_Y_mode = 0U;
        }

        SWatch_DW->is_active_TimeCount = 1U;

        /* Outport: '<Root>/tenths' incorporates:
         *  Chart: '<S1>/SWatch2018'
         *  Chart: '<S1>/SWatch2018'
         */
        *SWatch_Y_tenths = 0U;

        /* Chart: '<S1>/SWatch2018' */
        SWatch_DW->tenths = 0U;
        SWatch_DW->is_TimeCount = SWatch_IN_Count;
        if (SWatch_DW->is_active_AlarmMgmt != 1U) {
            SWatch_DW->is_active_AlarmMgmt = 1U;
        }

        if (SWatch_DW->is_AlarmMgmt != SWatch_IN_Silent) {
            SWatch_DW->is_AlarmMgmt = SWatch_IN_Silent;
            SWatch_B->buzz = false;
        }

        if (SWatch_DW->is_active_StopwatchMgmt != 1U) {
            SWatch_DW->is_active_StopwatchMgmt = 1U;
            SWatch_DW->Stenths = 0U;
            SWatch_DW->Sseconds = 0U;
            SWatch_DW->Sminutes = 0U;
            SWatch_DW->Shours = 0U;
        }

        switch (SWatch_DW->was_StopwatchMgmt) {
          case SWatch_IN_Idle:
            SWatch_DW->is_StopwatchMgmt = SWatch_IN_Idle;
            SWatch_DW->was_StopwatchMgmt = SWatch_IN_Idle;
            break;

          case SWatch_IN_Running:
            SWatch_DW->is_StopwatchMgmt = SWatch_IN_Running;
            SWatch_DW->was_StopwatchMgmt = SWatch_IN_Running;
            break;

          default:
            SWatch_DW->is_StopwatchMgmt = SWatch_IN_Idle;
            SWatch_DW->was_StopwatchMgmt = SWatch_IN_Idle;
            break;
        }
    }
}

/* Model data allocation function */
RT_MODEL_SWatch_T *SWatch(boolean_T *SWatch_U_plusbutton, boolean_T
    *SWatch_U_minusbutton, boolean_T *SWatch_U_timemode, boolean_T
    *SWatch_U_timesetmode, boolean_T *SWatch_U_alarmsetmode, boolean_T
    *SWatch_U_swatchmode, uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
    uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode)
{
    RT_MODEL_SWatch_T *SWatch_M;
    SWatch_M = (RT_MODEL_SWatch_T *) malloc(sizeof(RT_MODEL_SWatch_T));
    if (SWatch_M == NULL) {
        return NULL;
    }

    (void) memset((char *)SWatch_M, 0,
                  sizeof(RT_MODEL_SWatch_T));

    /* block I/O */
    {
        B_SWatch_T *b = (B_SWatch_T *) malloc(sizeof(B_SWatch_T));
        rt_VALIDATE_MEMORY(SWatch_M,b);
        SWatch_M->blockIO = (b);
    }

    /* states (dwork) */
    {
        DW_SWatch_T *dwork = (DW_SWatch_T *) malloc(sizeof(DW_SWatch_T));
        rt_VALIDATE_MEMORY(SWatch_M,dwork);
        SWatch_M->dwork = (dwork);
    }

    /* previous zero-crossing states */
    {
        PrevZCX_SWatch_T *zc = (PrevZCX_SWatch_T *) malloc(sizeof
            (PrevZCX_SWatch_T));
        rt_VALIDATE_MEMORY(SWatch_M,zc);
        SWatch_M->prevZCSigState = (zc);
    }

    {
        B_SWatch_T *SWatch_B = ((B_SWatch_T *) SWatch_M->blockIO);
        DW_SWatch_T *SWatch_DW = ((DW_SWatch_T *) SWatch_M->dwork);
        PrevZCX_SWatch_T *SWatch_PrevZCX = ((PrevZCX_SWatch_T *)
            SWatch_M->prevZCSigState);

        /* block I/O */
        (void) memset(((void *) SWatch_B), 0,
                      sizeof(B_SWatch_T));

        /* states (dwork) */
        (void) memset((void *)SWatch_DW, 0,
                      sizeof(DW_SWatch_T));

        /* external inputs */
        *SWatch_U_plusbutton = false;
        *SWatch_U_minusbutton = false;
        *SWatch_U_timemode = false;
        *SWatch_U_timesetmode = false;
        *SWatch_U_alarmsetmode = false;
        *SWatch_U_swatchmode = false;

        /* external outputs */
        (*SWatch_Y_hours) = 0U;
        (*SWatch_Y_minutes) = 0U;
        (*SWatch_Y_seconds) = 0U;
        (*SWatch_Y_tenths) = 0U;
        (*SWatch_Y_mode) = 0U;

        /* previous zero-crossing states */
        {
        }
    }

    return SWatch_M;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
