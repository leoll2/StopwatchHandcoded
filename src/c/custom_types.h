#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#include "ee.h"

typedef unsigned char bool;
#define false		0
#define true		1

typedef EE_UINT8	uint8_t;
typedef EE_UINT16 	uint16_t;

typedef enum {
	TIMEMODE,
	TIMESETMODE,
	ALARMMODE,
	SWATCHMODE
} Mode;

typedef enum {
	SETHOURS,
	SETMINUTES
} TimeSetMode;

typedef enum {
	ASETHOURS,
	ASETMINUTES
} AlarmSetMode;

#endif
