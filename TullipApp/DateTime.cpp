#include <sstream>
#include "DateTime.h"

// Date Class
// 00000000 00000000 00000000 00000000
// \_____________________/\____/\____/
//           Year          Month  Day
Date::Date(unsigned short day, unsigned short month, unsigned int year)
{
	date_ = 0;

	set_day(day);
	set_month((Month)(month - 1));
	set_year(year);
}

void Date::set_day(unsigned short day)
{
	if (day > 31 || day == 0)
	{
		throw DateTimeError(DAY_RANGE);
	}
	date_ = (date_ & 0xFFFFFFC0) | day;
}

unsigned short Date::get_day() const
{
	return date_ & 0x3F;
}

void Date::set_month(Month month)
{
	if ((unsigned int)month > 12 || (unsigned int)month == 0)
	{
		throw DateTimeError(MONTH_RANGE);
	}
	date_ = (date_ & 0xFFFFF83F) | ((unsigned int)month << 6);
}

Month Date::get_month() const
{
	return (Month)((date_ & 0x7C0) >> 6);
}

void Date::set_year(unsigned int year)
{
	if (year > 2097151 || year == 0)
	{
		throw DateTimeError(YEAR_RANGE);
	}
	date_ = (date_ & 0x000007FF) | (year << 11);
}

unsigned int Date::get_year() const
{
	return (date_ & 0xFFFFF800) >> 11;
}

std::string Date::get_date_string() const
{
	std::string date = std::to_string(get_day()) + "/" + std::to_string((int)get_month()) + "/" + std::to_string(get_year());
	if (get_day() < 10)
	{
		date = "0" + date;
	}
	if ((int)get_month() < 10)
	{
		date = date.substr(0, 3) + "0" + date.substr(3);
	}
	if (get_year() < 10)
	{
		date = date.substr(0, 6) + "0" + date.substr(6);
	}
	if (get_year() < 100)
	{
		date = date.substr(0, 7) + "0" + date.substr(7);
	}
	if (get_year() < 1000)
	{
		date = date.substr(0, 8) + "0" + date.substr(8);
	}
	return date;
}

void Date::print_short(std::ostream& stream) const { stream << get_date_string() << std::endl; }

void Date::print_long(std::ostream& stream) const
{
	std::string output = get_date_string();

	replace_all_occurrences(output, "/", ". ");

	stream << output << std::endl;
}

WeekDays Date::get_weekday_from_date(const Date& date)
{
	unsigned int d = date.get_day();
	unsigned int m = (unsigned int)date.get_month();
	unsigned int y = date.get_year();
	if (m < 3) { m += 12;  y -= 1; }
	int K = y % 100;
	int J = y / 100;
	int  result = (d + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 - 2 * J) % 7;
	if (result < 0) result += 7;

	return (WeekDays)result;
}

std::ostream& operator<<(std::ostream& stream, const Date& date)
{
	date.print_short(stream);
	return stream;
}

// Time Class
// 00000000 00000000 00000000 00000000
// \______/ \______/ \______/ \______/
//	 Zone	  Hour     Mins     Secs
// Zone Bit 1 = +/-, Rest is amount of 15 mins interval difference from UTC-0

// Protected members
bool Time::update_time(int intervals_of_fifteen)
{
	int minutes = (intervals_of_fifteen * 4) % 60 + get_minutes();
	int hours = 0;
	if (minutes > 59)
	{
		minutes -= 60;
		hours += 1;
	}
	set_minutes(minutes);
	
	hours += (intervals_of_fifteen * 4) / 60 + get_hours();

	bool overflow = false;
	if (hours > 23)
	{
		hours -= 24;
		overflow = true;
	}
	set_hours(hours);
	
	return overflow;
}

// Public members
Time::Time(unsigned short hours, unsigned short minutes, unsigned short seconds)
{
	time_ = 0;
	update_zone(false);
	set_seconds(seconds);
	set_minutes(minutes);
	set_hours(hours);
}

void Time::set_seconds(unsigned short seconds)
{
	if (seconds > 59)
	{
		throw DateTimeError(SECONDS_RANGE);
	}
	time_ = (time_ & 0xFFFFFF00) | seconds;
}

unsigned short Time::get_seconds() const
{
	return time_ & 0xFF;
}

void Time::set_minutes(unsigned short minutes)
{
	if (minutes > 59)
	{
		throw DateTimeError(MINUTES_RANGE);
	}
	time_ = (time_ & 0xFFFF00FF) | (minutes << 8);
}

unsigned short Time::get_minutes() const
{
	return (time_ & 0xFF00) >> 8;
}

void Time::set_hours(unsigned short hours)
{
	if (hours > 23)
	{
		throw DateTimeError(HOURS_RANGE);
	}
	time_ = (time_ & 0xFF00FFFF) | ((unsigned int)hours << 16);
}

unsigned short Time::get_hours() const
{
	return (time_ & 0xFF0000) >> 16;
}

void Time::set_zone(unsigned short zone)
{
	if (zone > 14 || zone < -12)
	{
		throw DateTimeError(TIMEZONE_RANGE);
	}
	time_ = (time_ & 0x00FFFFFF) | ((unsigned int)zone << 24);
}

std::string Time::get_zone_string() const
{
	unsigned short offset = (time_ & 0xFF000000) >> 24;
	std::string zone = "UTC_";

	if (offset > 127)
	{
		offset -= 128;
		zone += "Minus";
	}
	else
	{
		zone += "Plus";
	}

	zone += std::to_string(offset / 4) + "_" + std::to_string((offset % 4) * 15);

	return zone;
}

void Time::update_zone(bool should_update_time)
{
	std::time_t t = std::time(nullptr);

	std::tm local_tm;
	if (localtime_s(&local_tm, &t) != 0)
	{
		throw std::runtime_error("Failed to get local time.");
	}

	std::tm  gmt_tm;
	if (gmtime_s(&gmt_tm, &t) != 0)
	{
		throw std::runtime_error("Failed to get local time.");
	}


	auto local_tt = std::mktime(&local_tm);
	auto   gmt_tt = std::mktime(&gmt_tm);

	int offset_seconds = static_cast<int>(std::difftime(local_tt, gmt_tt));
	int offset_minutes = offset_seconds / 60;
	std::int8_t offset = offset_minutes / 15;

	std::int8_t past_offset = (time_ & 0xFF000000) >> 24;

	if (should_update_time)
	{
		int offset_difference = offset - past_offset;

		update_time(offset_difference);
	}

	set_zone(offset);
}

std::string Time::get_time_string() const
{
	std::string time = std::to_string(get_hours()) + ":" + std::to_string(get_minutes()) + ":" + std::to_string(get_seconds());
	if (get_hours() < 10)
	{
		time = "0" + time;
	}
	if (get_minutes() < 10)
	{
		time = time.substr(0, 3) + "0" + time.substr(3);
	}
	if (get_seconds() < 10)
	{
		time = time.substr(0, 6) + "0" + time.substr(6);
	}
	return time;
}

void Time::print_short(std::ostream& stream) const
{
	stream << get_time_string() << std::endl;
}

void Time::print_long(std::ostream& stream) const
{
	std::string output = get_time_string() + " " + get_zone_string();
}

std::ostream& operator<<(std::ostream& stream, const Time& time)
{
	time.print_short(stream);
	return stream;
}


// DateTime Class

DateTime::DateTime(unsigned short day, unsigned short month, unsigned int year, 
	unsigned short hours, unsigned short minutes, unsigned short seconds)
	: Date(day, month, year), Time(hours, minutes, seconds) {}

DateTime::DateTime(const Date& date, const Time& time) : Date(date), Time(time) {}

std::string DateTime::get_date_time_string() const
{
	std::string dateTime = get_date_string() + " " + get_time_string();
	return dateTime;
}

void DateTime::print_short(std::ostream& stream) const  
{  
   std::ostringstream oss;
   this->Date::print_short(oss);
   this->Time::print_short(oss);
   stream << oss.str();
}

void DateTime::print_long(std::ostream& stream) const
{
	std::ostringstream oss;
	this->Date::print_long(oss);
	this->Time::print_long(oss);
	stream << oss.str();
}

std::ostream& operator<<(std::ostream& stream, const DateTime& dateTime)
{
	dateTime.print_short(stream);
	return stream;
}