#ifndef DATETIME_H_
#define DATETIME_H_
#include "Helper_Functions.h"
#include "DateTime_Exceptions.h"
#include <iostream>
#include <string>

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
	End
};

std::string month_to_string(Months month);
std::ostream& operator<<(std::ostream& stream, const Months& month);

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

enum class WeekDays
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
	End
};

std::string weekday_to_string(WeekDays weekday);
std::ostream& operator<<(std::ostream& stream, const WeekDays& weekday);

//enum class TimeZones
//{
//	UTC_Minus12,
//	UTC_Minus11,
//	UTC_Minus10,
//	UTC_Minus9_30,
//	UTC_Minus9,
//	UTC_Minus8,
//	UTC_Minus7,
//	UTC_Minus6,
//	UTC_Minus5,
//	UTC_Minus4_30,
//	UTC_Minus4,
//	UTC_Minus3_30,
//	UTC_Minus3,
//	UTC_Minus2_30,
//	UTC_Minus2,
//	UTC_Minus1,
//	UTC_0,
//	UTC_Plus1,
//	UTC_Plus2,
//	UTC_Plus3,
//	UTC_Plus3_30,
//	UTC_Plus4,
//	UTC_Plus4_30,
//	UTC_Plus5,
//	UTC_Plus5_30,
//	UTC_Plus5_45,
//	UTC_Plus6,
//	UTC_Plus6_30,
//	UTC_Plus7,
//	UTC_Plus8,
//	UTC_Plus9,
//	UTC_Plus9_30,
//	UTC_Plus10,
//	UTC_Plus10_30,
//	UTC_Plus11,
//	UTC_Plus11_30,
//	UTC_Plus12,
//	UTC_Plus12_45,
//	UTC_Plus13,
//	UTC_Plus14
//};

class Date
{
protected:
	// 00000000 00000000 00000000 00000000
	// \_____________________/\____/\____/
	//           Year          Month  Day
	unsigned int date_;

public:
	Date() = default;
	Date(unsigned int date);
	Date(unsigned short day, unsigned short month, unsigned int year);
	Date(const Date& date) = default;
	Date(Date&& date) noexcept = default;

	Date& operator=(const Date& date) = default;
	Date& operator=(Date&& date) noexcept = default;

	void set_day(unsigned short day);
	unsigned short get_day() const;

	void set_month(Months month);
	Months get_month() const;

	void set_year(unsigned int year);
	unsigned int get_year() const;

	std::string get_date_string() const;

	void print_long(std::ostream& stream) const;
	inline void print_short(std::ostream& stream) const;

	bool operator==(const Date& date) const;
	bool operator!=(const Date& date) const;
	bool operator<(const Date& date) const;
	bool operator>(const Date& date) const;
	bool operator<=(const Date& date) const;
	bool operator>=(const Date& date) const;

	Date operator-(const Date& date) const;

	friend std::ostream& operator<<(std::ostream& stream, const Date& date);

	static WeekDays get_weekday_from_date(const Date& date);

	static Date get_current_date();

	~Date() = default;
};

class Time
{
protected:
	unsigned int time_;
	// 00000000 00000000 00000000 00000000
	// \______/ \______/ \______/ \______/
	//	 Zone	  Hour     Mins     Secs
	// Zone Bit 1 = +/-, Rest is amount of 15 mins interval difference from UTC-0

	bool update_time(int intervals_of_fifteen);
public:
	Time() = default;
	Time(unsigned int time);
	Time(unsigned short hours, unsigned short minutes, unsigned short seconds);
	Time(const Time& time) = default;
	Time(Time&& time) noexcept = default;

	Time& operator=(const Time& time) = default;
	Time& operator=(Time&& time) noexcept = default;

	void set_seconds(unsigned short seconds);
	unsigned short get_seconds() const;

	void set_minutes(unsigned short minutes);
	unsigned short get_minutes() const;

	void set_hours(unsigned short hours);
	unsigned short get_hours() const;

	void set_zone(unsigned short zone);
	std::string get_zone_string() const;
	void update_zone(bool should_update_time = true);

	std::string get_time_string() const;

	void print_long(std::ostream& stream) const;
	void print_short(std::ostream& stream) const;

	bool operator==(const Time& time) const;
	bool operator!=(const Time& time) const;
	bool operator<(const Time& time) const;
	bool operator>(const Time& time) const;
	bool operator<=(const Time& time) const;
	bool operator>=(const Time& time) const;

	friend std::ostream& operator<<(std::ostream& stream, const Time& time);

	static Time get_current_time();

	~Time() = default;
};

class DateTime : public Date, public Time
{
public:
	DateTime() = default;
	DateTime(unsigned short day, unsigned short month, unsigned int year, unsigned short hours, unsigned short mins, unsigned short secs);
	DateTime(const DateTime& date_time) = default;
	DateTime(DateTime&& date_time) = default;
	DateTime(const Date& date, const Time& time);

	DateTime& operator=(const DateTime& date_time) = default;
	DateTime& operator=(DateTime&& date_time) = default;

	void set_date(const Date& date);
	inline Date get_date() const { return Date(date_); }

	void set_time(const Time& time);
	inline Time get_time() const { return Time(time_); }

	std::string get_date_time_string() const;

	void print_long(std::ostream& stream) const;
	void print_short(std::ostream& stream) const;

	bool operator==(const DateTime& date_time) const;
	bool operator!=(const DateTime& date_time) const;
	bool operator<(const DateTime& date_time) const;
	bool operator>(const DateTime& date_time) const;
	bool operator<=(const DateTime& date_time) const;
	bool operator>=(const DateTime& date_time) const;

	friend std::ostream& operator<<(std::ostream& stream, const DateTime& dateTime);

	static DateTime get_current_datetime();

	~DateTime() = default;
};

#endif