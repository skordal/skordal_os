// SkordalOS Real-Time Clock Driver
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "rtc.h"

// Initializes the RTC:
void rtc_init()
{
	debug_print_string("Initializing RTC:");
	debug_print_newline();

	// Check if the RTC is running:
	uint8_t rtc_status = tps65950_read_reg(TPS65950_RTC_STATUS_REG);
	if(rtc_status & RTC_RUNNING)
	{
		debug_print_string("\tRTC is running.");
	} else {
		debug_print_string("\tSetting RTC: ");

		// Set the RTC to start it:
		tps65950_write_reg(TPS65950_SECONDS_REG, 0);
		tps65950_write_reg(TPS65950_MINUTES_REG, 0);
		tps65950_write_reg(TPS65950_HOURS_REG, 0);
		tps65950_write_reg(TPS65950_DAYS_REG, 1);
		tps65950_write_reg(TPS65950_MONTHS_REG, RTC_JANUARY);
		tps65950_write_reg(TPS65950_YEARS_REG, 0);

		debug_print_string("ok");
	}

	debug_print_newline();
}

// Gets the time from the RTC:
void rtc_get_time(rtc_time_t * retval)
{
	retval->second = bcd2bin(tps65950_read_reg(TPS65950_SECONDS_REG));
	retval->minute = bcd2bin(tps65950_read_reg(TPS65950_MINUTES_REG));
	retval->hour = bcd2bin(tps65950_read_reg(TPS65950_HOURS_REG));
	retval->day = bcd2bin(tps65950_read_reg(TPS65950_DAYS_REG));
	retval->month = bcd2bin(tps65950_read_reg(TPS65950_MONTHS_REG));
	retval->year = bcd2bin(tps65950_read_reg(TPS65950_YEARS_REG));
	retval->day_of_week = bcd2bin(tps65950_read_reg(TPS65950_WEEKS_REG));
}

