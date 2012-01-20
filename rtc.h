// SkordalOS Real-Time Clock Driver
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef RTC_H
#define RTC_H

#include "types.h"
#include "tps65950.h"

#include "asm/functions.h"

// Some bitfield values for the RTC registers:
#define RTC_RUNNING	(1 << 1)

// Day values:
#define RTC_MONDAY	0
#define RTC_TUESDAY	1
#define RTC_WEDNESSDAY	2
#define RTC_THURSDAY	3
#define RTC_FRIDAY	4
#define RTC_SATURDAY	5
#define RTC_SUNDAY	6

// Month values:
#define RTC_JANUARY	1
#define RTC_FEBRUARY	2
#define RTC_MARCH	3
#define RTC_APRIL	4
#define RTC_MAY		5
#define RTC_JUNE	6
#define RTC_JULY	7
#define RTC_AUGUST	8
#define RTC_SEPTEMBER	9
#define RTC_OCTOBER	10
#define RTC_NOVEMBER	11
#define RTC_DECEMBER	12

typedef struct {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint8_t year;
	uint8_t day_of_week;
} rtc_time_t;

// Initializes the RTC:
void rtc_init();

// Gets the current time from the RTC:
void rtc_get_time(rtc_time_t * time);

// Sets the current time of the RTC:
void rtc_set_time(const rtc_time_t * time);

#endif

