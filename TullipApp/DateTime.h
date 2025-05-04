/**
 * @file DateTime.h
 * @brief Defines classes and utilities for working with dates, times, and combined date-time values.
 * @details This file contains the `Date`, `Time`, and `DateTime` classes, as well as supporting enums and functions
 *          for handling and manipulating date and time values.
 */

#ifndef DATETIME_H_
#define DATETIME_H_

#include "Helper_Functions.h"
#include "DateTime_Exceptions.h"
#include <iostream>
#include <string>

 /**
  * @brief Array of month names.
  * @details Provides string representations of the months of the year.
  */
inline const char* months_array[] =
{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

/**
 * @enum Months
 * @brief Represents the months of the year.
 */
enum class Months
{
	January,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	Semptember,
	October,
	November,
	December,
	End ///< Marks the end of the enumeration.
};

/**
 * @brief Converts a `Months` enum value to its string representation.
 * @param month The `Months` enum value to convert.
 * @return A string representation of the month.
 */
std::string month_to_string(Months month);

/**
 * @brief Outputs a `Months` enum value to a stream.
 * @param stream The output stream.
 * @param month The `Months` enum value to output.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& stream, const Months& month);

/**
 * @brief Converts a string representation of a month to its corresponding `Months` enum value.
 * @param month_string The string representation of the month.
 * @return The corresponding `Months` enum value.
 * @throws DateTimeError if the month string is invalid.
 */
Months string_to_month(const std::string& month_string);

/**
 * @brief Array of weekday names.
 * @details Provides string representations of the days of the week.
 */
inline const char* weekdays_array[] =
{
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday"
};

/**
 * @enum WeekDays
 * @brief Represents the days of the week.
 */
enum class WeekDays
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
	End ///< Marks the end of the enumeration.
};

/**
 * @brief Converts a `WeekDays` enum value to its string representation.
 * @param weekday The `WeekDays` enum value to convert.
 * @return A string representation of the weekday.
 */
std::string weekday_to_string(WeekDays weekday);

/**
 * @brief Outputs a `WeekDays` enum value to a stream.
 * @param stream The output stream.
 * @param weekday The `WeekDays` enum value to output.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& stream, const WeekDays& weekday);

/**
 * @brief Converts a string representation of a weekday to its corresponding `WeekDays` enum value.
 * @param weekday_string The string representation of the weekday.
 * @return The corresponding `WeekDays` enum value.
 * @throws DateTimeError if the weekday string is invalid.
 */
WeekDays string_to_weekday(const std::string& weekday_string);

/**
 * @class Date
 * @brief Represents a date (day, month, year).
 * @details The `Date` class provides functionality for managing and manipulating date values.
 */
class Date
{
protected:
	/**
	 * @brief Encoded date value.
	 * @details The date is stored as a 32-bit integer with the following structure:
	 *          - Bits 0-5: Day
	 *          - Bits 6-10: Month
	 *          - Bits 11-31: Year
	 *			- 00000000 00000000 00000000 00000000
	 *			- \_____________________/\____/\____/
	 *			-		  Year            Month  Day
	 */
	unsigned int date_;

public:
	/**
	 * @brief Default constructor.
	 */
	Date() = default;

	/**
	 * @brief Constructs a `Date` from an encoded date value.
	 * @param date The encoded date value.
	 */
	Date(unsigned int date);

	/**
	 * @brief Constructs a `Date` from a string representation of the date.
	 * @param date_string The string representation of the date in the format "DD/MM/YYYY".
	 * @throws DateTimeError if the date string is invalid.
	 */
	Date(const std::string& date_string);

	/**
	 * @brief Constructs a `Date` from day, month, and year values.
	 * @param day The day of the month.
	 * @param month The month of the year.
	 * @param year The year.
	 */
	Date(unsigned short day, unsigned short month, unsigned int year);

	// Rule of 5
	Date(const Date& date) = default;
	Date(Date&& date) noexcept = default;
	Date& operator=(const Date& date) = default;
	Date& operator=(Date&& date) noexcept = default;

	/**
	 * @brief Sets the day of the date.
	 * @param day The new day value.
	 */
	void set_day(unsigned short day);

	/**
	 * @brief Gets the day of the date.
	 * @return The day value.
	 */
	unsigned short get_day() const;

	/**
	 * @brief Sets the month of the date.
	 * @param month The new month value.
	 */
	void set_month(Months month);

	/**
	 * @brief Gets the month of the date.
	 * @return The month value.
	 */
	Months get_month() const;

	/**
	 * @brief Sets the year of the date.
	 * @param year The new year value.
	 */
	void set_year(unsigned int year);

	/**
	 * @brief Gets the year of the date.
	 * @return The year value.
	 */
	unsigned int get_year() const;

	/**
	 * @brief Gets the date as a string.
	 * @return A string representation of the date.
	 */
	std::string get_date_string() const;

	/**
	 * @brief Prints the date in a long format.
	 * @param stream The output stream.
	 */
	void print_long(std::ostream& stream) const;

	/**
	 * @brief Prints the date in a short format.
	 * @param stream The output stream.
	 */
	inline void print_short(std::ostream& stream) const;

	/**
	* @brief Compares two dates for equality.
	* @param date The date to compare with.
	* @return true if the dates are equal, false otherwise.
	*/
	bool operator==(const Date& date) const;

	/**
	 * @brief Compares two dates for inequality.
	 * @param date The date to compare with.
	 * @return true if the dates are not equal, false otherwise.
	 */
	bool operator!=(const Date& date) const;

	/**
	 * @brief Compares two dates for ordering.
	 * @param date The date to compare with.
	 * @return true if this date is less than the given date, false otherwise.
	 */
	bool operator<(const Date& date) const;

	/**
	 * @brief Compares two dates for ordering.
	 * @param date The date to compare with.
	 * @return true if this date is greater than the given date, false otherwise.
	 */
	bool operator>(const Date& date) const;

	/**
	 * @brief Compares two dates for ordering.
	 * @param date The date to compare with.
	 * @return true if this date is less than or equal to the given date, false otherwise.
	 */
	bool operator<=(const Date& date) const;

	/**
	 * @brief Compares two dates for ordering.
	 * @param date The date to compare with.
	 * @return true if this date is greater than or equal to the given date, false otherwise.
	 */
	bool operator>=(const Date& date) const;

	/**
	 * @brief Subtracts two dates.
	 * @details This operator calculates the difference between two dates.
	 * @param date The date to subtract.
	 * @return The difference as a `Date` object.
	 */
	Date operator-(const Date& date) const;

	/**
	 * @brief Outputs the date to a stream.
	 * @param stream The output stream.
	 * @param date The `Date` object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Date& date);

	/**
	 * @brief Gets the weekday for a given date.
	 * @param date The `Date` object.
	 * @return The corresponding `WeekDays` value.
	 */
	static WeekDays get_weekday_from_date(const Date& date);

	/**
	 * @brief Gets the current date.
	 * @return A `Date` object representing the current date.
	 */
	static Date get_current_date();

	/**
	 * @brief Destructor.
	 */
	~Date() = default;
};

/**
 * @class Time
 * @brief Represents a time (hours, minutes, seconds, and time zone).
 * @details The `Time` class provides functionality for managing and manipulating time values.
 */
class Time
{
protected:
	/**
	 * @brief Encoded time value.
	 * @details The time is stored as a 32-bit integer with the following structure:
	 *          - Bits 0-7: Seconds
	 *          - Bits 8-15: Minutes
	 *          - Bits 16-23: Hours
	 *          - Bits 24-31: Time zone
	 *			- 00000000 00000000 00000000 00000000
	 *			- \______/ \______/ \______/ \______/
	 *			-   Zone	 Hour     Mins     Secs
	 *			- Zone Bit 1 = +/-, Rest is amount of 15 mins interval difference from UTC-0
	 */
	unsigned int time_;

	/**
	 * @brief Updates the time based on intervals of 15 minutes.
	 * @param intervals_of_fifteen The number of 15-minute intervals to adjust.
	 * @return true if the update was successful, false otherwise.
	 */
	bool update_time(int intervals_of_fifteen);

public:
	/**
	 * @brief Default constructor.
	 */
	Time() = default;

	/**
	 * @brief Constructs a `Time` from an encoded time value.
	 * @param time The encoded time value.
	 */
	Time(unsigned int time);

	/**
	 * @brief Constructs a `Time` from a string representation of the time.
	 * @param time_string The string representation of the time in the format "HH:MM:SS".
	 * @throws DateTimeError if the time string is invalid.
	 */
	Time(const std::string& time_string);

	/**
	 * @brief Constructs a `Time` from hours, minutes, and seconds.
	 * @param hours The hour value.
	 * @param minutes The minute value.
	 * @param seconds The second value.
	 */
	Time(unsigned short hours, unsigned short minutes, unsigned short seconds);

	// Rule of 5
	Time(const Time& time) = default;
	Time(Time&& time) noexcept = default;
	Time& operator=(const Time& time) = default;
	Time& operator=(Time&& time) noexcept = default;

	/**
	 * @brief Sets the seconds of the time.
	 * @param seconds The new seconds value.
	 */
	void set_seconds(unsigned short seconds);

	/**
	 * @brief Gets the seconds of the time.
	 * @return The seconds value.
	 */
	unsigned short get_seconds() const;

	/**
	 * @brief Sets the minutes of the time.
	 * @param minutes The new minutes value.
	 */
	void set_minutes(unsigned short minutes);

	/**
	 * @brief Gets the minutes of the time.
	 * @return The minutes value.
	 */
	unsigned short get_minutes() const;

	/**
	 * @brief Sets the hours of the time.
	 * @param hours The new hours value.
	 */
	void set_hours(unsigned short hours);

	/**
	 * @brief Gets the hours of the time.
	 * @return The hours value.
	 */
	unsigned short get_hours() const;

	/**
	 * @brief Sets the time zone.
	 * @param zone The new time zone value.
	 */
	void set_zone(unsigned short zone);

	/**
	 * @brief Gets the time zone as a string.
	 * @return A string representation of the time zone.
	 */
	std::string get_zone_string() const;

	/**
	 * @brief Updates the time zone.
	 * @param should_update_time Whether to adjust the time based on the new time zone.
	 */
	void update_zone(bool should_update_time = true);

	/**
	 * @brief Gets the time as a string.
	 * @return A string representation of the time.
	 */
	std::string get_time_string() const;

	/**
	 * @brief Prints the time in a long format.
	 * @param stream The output stream.
	 */
	void print_long(std::ostream& stream) const;

	/**
	 * @brief Prints the time in a short format.
	 * @param stream The output stream.
	 */
	void print_short(std::ostream& stream) const;

	/**
	 * @brief Compares two times for equality.
	 * @param time The time to compare with.
	 * @return true if the times are equal, false otherwise.
	 */
	bool operator==(const Time& time) const;

	/**
	 * @brief Compares two times for inequality.
	 * @param time The time to compare with.
	 * @return true if the times are not equal, false otherwise.
	 */
	bool operator!=(const Time& time) const;

	/**
	 * @brief Compares two times for ordering.
	 * @param time The time to compare with.
	 * @return true if this time is less than the given time, false otherwise.
	 */
	bool operator<(const Time& time) const;

	/**
	 * @brief Compares two times for ordering.
	 * @param time The time to compare with.
	 * @return true if this time is greater than the given time, false otherwise.
	 */
	bool operator>(const Time& time) const;

	/**
	 * @brief Compares two times for ordering.
	 * @param time The time to compare with.
	 * @return true if this time is less than or equal to the given time, false otherwise.
	 */
	bool operator<=(const Time& time) const;

	/**
	 * @brief Compares two times for ordering.
	 * @param time The time to compare with.
	 * @return true if this time is greater than or equal to the given time, false otherwise.
	 */
	bool operator>=(const Time& time) const;

	/**
	 * @brief Outputs the time to a stream.
	 * @param stream The output stream.
	 * @param time The `Time` object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Time& time);

	/**
	 * @brief Gets the current time.
	 * @return A `Time` object representing the current time.
	 */
	static Time get_current_time();

	/**
	 * @brief Destructor.
	 */
	~Time() = default;
};

/**
 * @class DateTime
 * @brief Represents a combined date and time.
 * @details The `DateTime` class combines the functionality of the `Date` and `Time` classes.
 */
class DateTime : public Date, public Time
{
public:
	/**
	 * @brief Default constructor.
	 */
	DateTime() = default;

	/**
	 * @brief Constructs a `DateTime` from an encoded date and time value.
	 * @param date_time The encoded date and time value.
	 */
	DateTime(const std::string& date_time_string);

	/**
	 * @brief Constructs a `DateTime` from day, month, year, hours, minutes, and seconds.
	 * @param day The day of the month.
	 * @param month The month of the year.
	 * @param year The year.
	 * @param hours The hour value.
	 * @param mins The minute value.
	 * @param secs The second value.
	 */
	DateTime(unsigned short day, unsigned short month, unsigned int year, unsigned short hours, unsigned short mins, unsigned short secs);

	/**
	 * @brief Constructs a `DateTime` from a `Date` and a `Time`.
	 * @param date The `Date` value.
	 * @param time The `Time` value.
	 */
	DateTime(Date date, Time time);

	// Rule of 5
	DateTime(const DateTime& date_time) = default;
	DateTime(DateTime&& date_time) = default;
	DateTime& operator=(const DateTime& date_time) = default;
	DateTime& operator=(DateTime&& date_time) = default;

	/**
	 * @brief Sets the date component of the `DateTime`.
	 * @param date The new `Date` value.
	 */
	void set_date(Date date);

	/**
	 * @brief Gets the date component of the `DateTime`.
	 * @return The `Date` value.
	 */
	inline Date get_date() const { return Date(date_); }

	/**
	 * @brief Sets the time component of the `DateTime`.
	 * @param time The new `Time` value.
	 */
	void set_time(Time time);

	/**
	 * @brief Gets the time component of the `DateTime`.
	 * @return The `Time` value.
	 */
	inline Time get_time() const { return Time(time_); }

	/**
	 * @brief Gets the combined date and time as a string.
	 * @return A string representation of the date and time.
	 */
	std::string get_date_time_string() const;

	/**
	 * @brief Prints the date and time in a long format.
	 * @param stream The output stream.
	 */
	void print_long(std::ostream& stream) const;

	/**
	 * @brief Prints the date and time in a short format.
	 * @param stream The output stream.
	 */
	void print_short(std::ostream& stream) const;

	/**
	 * @brief Compares two `DateTime` objects for equality.
	 * @param date_time The `DateTime` object to compare with.
	 * @return true if the `DateTime` objects are equal, false otherwise.
	 */
	bool operator==(const DateTime& date_time) const;

	/**
	 * @brief Compares two `DateTime` objects for inequality.
	 * @param date_time The `DateTime` object to compare with.
	 * @return true if the `DateTime` objects are not equal, false otherwise.
	 */
	bool operator!=(const DateTime& date_time) const;

	/**
	 * @brief Compares two `DateTime` objects for ordering.
	 * @param date_time The `DateTime` object to compare with.
	 * @return true if this `DateTime` is less than the given `DateTime`, false otherwise.
	 */
	bool operator<(const DateTime& date_time) const;

	/**
	 * @brief Compares two `DateTime` objects for ordering.
	 * @param date_time The `DateTime` object to compare with.
	 * @return true if this `DateTime` is greater than the given `DateTime`, false otherwise.
	 */
	bool operator>(const DateTime& date_time) const;

	/**
	 * @brief Compares two `DateTime` objects for ordering.
	 * @param date_time The `DateTime` object to compare with.
	 * @return true if this `DateTime` is less than or equal to the given `DateTime`, false otherwise.
	 */
	bool operator<=(const DateTime& date_time) const;

	/**
	 * @brief Compares two `DateTime` objects for ordering.
	 * @param date_time The `DateTime` object to compare with.
	 * @return true if this `DateTime` is greater than or equal to the given `DateTime`, false otherwise.
	 */
	bool operator>=(const DateTime& date_time) const;

	/**
	 * @brief Outputs the `DateTime` to a stream.
	 * @param stream The output stream.
	 * @param dateTime The `DateTime` object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const DateTime& dateTime);

	/**
	 * @brief Gets the current date and time.
	 * @return A `DateTime` object representing the current date and time.
	 */
	static DateTime get_current_datetime();

	/**
	 * @brief Destructor.
	 */
	~DateTime() = default;
};

class Schedule : public Time
{
private:
	WeekDays day_;
public:
	/**
	 * @brief Default constructor.
	 */
	Schedule() = default;

	/**
	 * @brief Constructs a `Schedule` from a `Time` and a `WeekDays` value.
	 * @param time The `Time` value.
	 * @param day The `WeekDays` value.
	 */
	Schedule(WeekDays day, Time time);

	/**
	 * @brief Constructs a `Schedule` from an encoded time.
	 * @details Constructs a `Schedule` from an encoded time value and a `WeekDays` value.
	 * @param time The encoded time value.
	 */
	Schedule(const std::string& schedule_string);

	// Rule of 5
	Schedule(const Schedule& schedule) = default;
	Schedule(Schedule&& schedule) = default;
	Schedule& operator=(const Schedule& schedule) = default;
	Schedule& operator=(Schedule&& schedule) = default;

	/**
	 * @brief Gets the day of the week of the schedule.
	 */
	WeekDays get_day() const { return day_; }

	/**
	 * @brief Sets the day of the week of the schedule.
	 * @param day The new `WeekDays` value.
	 */
	void set_day(WeekDays day) { day_ = day; }

	/**
	 * @brief Gets the time of the schedule.
	 * @return The `Time` value.
	 */
	inline Time get_time() const { return Time(time_); }

	/**
	 * @brief Sets the time of the schedule.
	 * @param time The new `Time` value.
	 */
	void set_time(Time time);

	/**
	* @brief Compares two `Schedule` objects for equality.
	* @param schedule The `Schedule` object to compare with.
	* @return true if the `Schedule` objects are equal, false otherwise.
	*/
	bool operator==(const Schedule& schedule) const;

	/**
	 * @brief Compares two `Schedule` objects for inequality.
	 * @param schedule The `Schedule` object to compare with.
	 * @return true if the `Schedule` objects are not equal, false otherwise.
	 */
	bool operator!=(const Schedule& schedule) const;

	/**
	 * @brief Compares two `Schedule` objects for ordering.
	 * @param schedule The `Schedule` object to compare with.
	 * @return true if this `Schedule` is less than the given `Schedule`, false otherwise.
	 */
	bool operator<(const Schedule& schedule) const;

	/**
	 * @brief Compares two `Schedule` objects for ordering.
	 * @param schedule The `Schedule` object to compare with.
	 * @return true if this `Schedule` is greater than the given `Schedule`, false otherwise.
	 */
	bool operator>(const Schedule& schedule) const;

	/**
	 * @brief Compares two `Schedule` objects for ordering.
	 * @param schedule The `Schedule` object to compare with.
	 * @return true if this `Schedule` is less than or equal to the given `Schedule`, false otherwise.
	 */
	bool operator<=(const Schedule& schedule) const;

	/**
	 * @brief Compares two `Schedule` objects for ordering.
	 * @param schedule The `Schedule` object to compare with.
	 * @return true if this `Schedule` is greater than or equal to the given `Schedule`, false otherwise.
	 */
	bool operator>=(const Schedule& schedule) const;

	/**
	 * @brief Destructor.
	 */
	~Schedule() = default;

	/**
	 * @brief Outputs the `Schedule` to a stream.
	 * @param stream The output stream.
	 * @param schedule The `Schedule` object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Schedule& schedule);
};

#endif // !DATETIME_H_
