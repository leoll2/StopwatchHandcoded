#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

typedef unsigned char bool;
#define false		0
#define true		1

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
