/*
 * Event.h
 *
 *  Created on: 22/ott/2015
 *      Author: admim
 */

#ifndef EVENT_H_
#define EVENT_H_

#define TIMEMODE_EV 	0x01
#define TIMESETMODE_EV 	0x02
#define ALARMMODE_EV 	0x04
#define SWATCHMODE_EV 	0x08
#define PLUS_EV      	0x10
#define MINUS_EV    	0x20

typedef unsigned char Event;

typedef unsigned char Events;
extern Events evts;

#define SetEvent(Event) (evts |= Event)
#define ClearEvent(Event) (evts &= !Event)
#define ClearEvents() (evts = 0)
#define IsEvent(Event) ((unsigned char)(evts & Event))

#endif /* EVENT_H_ */
