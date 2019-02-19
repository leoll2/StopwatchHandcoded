#include <stdio.h>

#include "fonts.h"
#include "pictures.h"
#include "stm32f4_discovery_lcd.h"
#include "widget_config.h"

ButtonIcon buttontime = {
		icontime_on, icontime_off, TIMEMODE_EV
};

ButtonIcon buttontimeset = {
		icontimeset_on, icontimeset_off, TIMESETMODE_EV
};

ButtonIcon buttonalarm = {
		iconalarm_on, iconalarm_off, ALARMMODE_EV
};

ButtonIcon buttonswatch = {
		iconswatch_on, iconswatch_off, SWATCHMODE_EV
};

ButtonIcon buttonplus = {
		0, 0, PLUS_EV
};

ButtonIcon buttonminus = {
		0, 0, MINUS_EV
};

Text txt = {
		&Font32x48, White
};

Image backg = {
	ImageBuffer
};

const Widget MyWatchScr[NUMWIDGETS] = {
		{0, 0, 320, 240, BACKGROUND, (void *)&backg},
		{30, 188, 39, 43, BUTTONICON, (void *)&buttontime},
		{98, 188, 39, 43, BUTTONICON, (void *)&buttontimeset},
		{169, 188, 38, 43, BUTTONICON, (void *)&buttonalarm},
		{244, 188, 35, 43, BUTTONICON, (void *)&buttonswatch},
		{270, 30, 40, 40, BUTTONICON, (void *)&buttonplus},
		{270, 105, 40, 40, BUTTONICON, (void *)&buttonminus},
		{29, 70, 40, 40, TEXT, (void *)&txt},
		{99, 70, 40, 40, TEXT, (void *)&txt},
		{168, 70, 40, 40, TEXT, (void *)&txt},
		{243, 70, 40, 40, TEXT, (void *)&txt},
		{80, 70, 40, 40, TEXT, (void *)&txt},
		{149, 70, 40, 40, TEXT, (void *)&txt},
};

