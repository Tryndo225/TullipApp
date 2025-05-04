#include <sstream>
#include "DateTime.h"

// Enum classes
std::string month_to_string(Months month)
{
	return months_array[static_cast<int>(month)];
}
std::ostream& operator<<(std::ostream& stream, const Months& month)
{
	stream << month_to_string(month) << std::endl;
	return stream;
}

std::string weekday_to_string(WeekDays weekday)
{
	return weekdays_array[static_cast<int>(weekday)];
}

std::ostream& operator<<(std::ostream& stream, const WeekDays& weekday)
{
	stream << weekday_to_string(weekday) << std::endl;
	return stream;
}

// Date Class
// 00000000 00000000 00000000 00000000
// \_____________________/\____/\____/
//           Year          Month  Day
Date::Date(unsigned int date) : date_(date) {}

Date::Date(const std::string& date_string)
{
	std::istringstream date_stream(date_string);
	std::string day, month, year;
	std::getline(date_stream, day, '/');
	std::getline(date_stream, month, '/');
	std::getline(date_stream, year);

	unsigned short short_day = static_cast<unsigned short>(std::stoul(day));
	unsigned short short_month = static_cast<unsigned short>(std::stoul(month));
	unsigned int int_year = static_cast<unsigned int>(std::stoul(year));

	date_ = 0;
	set_day(short_day);
	set_month((Months)(short_month - 1));
	set_year(int_year);
}

Date::Date(unsigned short day, unsigned short month, unsigned int year)
{
	date_ = 0;

	set_day(day);
	set_month((Months)(month - 1));
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

void Date::set_month(Months month_enum)
{
	unsigned int month = (unsigned int)month_enum + 1; // Adjust for zero-based index
	if (month > 12 || month == 0)
	{
		throw DateTimeError(MONTH_RANGE);
	}
	date_ = (date_ & 0xFFFFF83F) | ((unsigned int)month << 6);
}

Months Date::get_month() const
{
	return (Months)((date_ & 0x7C0) >> 6);
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

void Date::print_short(std::ostream& stream) const { stream << get_date_string(); }

void Date::print_long(std::ostream& stream) const
{
	std::string output = get_date_string();

	replace_all_occurrences(output, "/", ". ");

	stream << output;
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

	// Adjust result to match the WeekDays enum
	result = (result + 5) % 7;

	return (WeekDays)result;
}

Date Date::get_current_date()
{
	std::time_t t = std::time(nullptr);
	std::tm local_tm;
	if (localtime_s(&local_tm, &t) != 0)
	{
		throw std::runtime_error("Failed to get local time.");
	}
	return Date(local_tm.tm_mday, local_tm.tm_mon + 1, local_tm.tm_year + 1900);
}

// Operator implementations
bool Date::operator==(const Date& date) const
{
	return (date_ == date.date_);
}

bool Date::operator!=(const Date& date) const
{
	return (date_ != date.date_);
}

bool Date::operator>(const Date& date) const
{
	return (date_ > date.date_);
}

bool Date::operator<(const Date& date) const
{
	return (date_ < date.date_);
}

bool Date::operator<=(const Date& date) const
{
	return (date_ <= date.date_);
}

bool Date::operator>=(const Date& date) const
{
	return (date_ >= date.date_);
}

std::ostream& operator<<(std::ostream& stream, const Date& date)
{
	date.print_short(stream);
	return stream;
}

Date Date::operator-(const Date& date) const
{
	return Date(date_ - date.date_);
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
Time::Time(unsigned int time) : time_(time) {}

Time::Time(const std::string& time_string)
{
	std::istringstream time_stream(time_string);
	std::string hours, minutes, seconds;
	std::getline(time_stream, hours, ':');
	std::getline(time_stream, minutes, ':');
	std::getline(time_stream, seconds);
	unsigned short short_hours = static_cast<unsigned short>(std::stoul(hours));
	unsigned short short_minutes = static_cast<unsigned short>(std::stoul(minutes));
	unsigned short short_seconds = static_cast<unsigned short>(std::stoul(seconds));
	time_ = 0;
	update_zone(false);
	set_seconds(short_seconds);
	set_minutes(short_minutes);
	set_hours(short_hours);
}

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

	zone += "_" + std::to_string(offset / 4);

	if (offset % 4 != 0)
	{
		zone += ":" + std::to_string(offset % 4 * 15);
	}

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
	stream << get_time_string();
}

void Time::print_long(std::ostream& stream) const
{
	stream << get_time_string() + " " + get_zone_string();
}

Time Time::get_current_time()
{
	std::time_t t = std::time(nullptr);
	std::tm local_tm;
	if (localtime_s(&local_tm, &t) != 0)
	{
		throw std::runtime_error("Failed to get local time.");
	}

	if (local_tm.tm_sec > 59)
	{
		local_tm.tm_sec -= 60;
		local_tm.tm_min += 1;
	}

	return Time(local_tm.tm_hour, local_tm.tm_min, local_tm.tm_sec);
}

// Operator implementations
bool Time::operator==(const Time& time) const
{
	Time copy_1 = *this;
	Time copy_2 = time;

	copy_1.update_zone(true);
	copy_2.update_zone(true);

	return (copy_1.time_ == copy_2.time_);
}
bool Time::operator!=(const Time& time) const
{
	return !(*this == time);
}
bool Time::operator>(const Time& time) const
{
	Time copy_1 = *this;
	Time copy_2 = time;
	copy_1.update_zone(true);
	copy_2.update_zone(true);
	return (copy_1.time_ > copy_2.time_);
}
bool Time::operator<(const Time& time) const
{
	Time copy_1 = *this;
	Time copy_2 = time;
	copy_1.update_zone(true);
	copy_2.update_zone(true);
	return (copy_1.time_ < copy_2.time_);
}
bool Time::operator<=(const Time& time) const
{
	Time copy_1 = *this;
	Time copy_2 = time;
	copy_1.update_zone(true);
	copy_2.update_zone(true);
	return (copy_1.time_ <= copy_2.time_);
}
bool Time::operator>=(const Time& time) const
{
	Time copy_1 = *this;
	Time copy_2 = time;
	copy_1.update_zone(true);
	copy_2.update_zone(true);
	return (copy_1.time_ >= copy_2.time_);
}

std::ostream& operator<<(std::ostream& stream, const Time& time)
{
	time.print_short(stream);
	return stream;
}

// DateTime Class
DateTime::DateTime(unsigned short day, unsigned short month, unsigned int year,
	unsigned short hours, unsigned short minutes, unsigned short seconds)
	: Date(day, month, year), Time(hours, minutes, seconds) {
}

DateTime::DateTime(const std::string& date_time_string)
{
	std::istringstream date_time_stream(date_time_string);
	std::string date_string, time_string;
	std::getline(date_time_stream, date_string, ' ');
	std::getline(date_time_stream, time_string);
	Date date(date_string);
	Time time(time_string);
	*this = DateTime(std::move(date), std::move(time));
}

DateTime::DateTime(const Date& date, const Time& time) : Date(date), Time(time) {}

void DateTime::set_date(const Date& date)
{
	*this = DateTime(date, get_time());
}

void DateTime::set_time(const Time& time)
{
	*this = DateTime(get_date(), time);
}

std::string DateTime::get_date_time_string() const
{
	std::string dateTime = get_date_string() + " " + get_time_string();
	return dateTime;
}

void DateTime::print_short(std::ostream& stream) const
{
	std::ostringstream oss;
	this->Date::print_short(oss);
	oss << " ";
	this->Time::print_short(oss);
	stream << oss.str();
}

void DateTime::print_long(std::ostream& stream) const
{
	std::ostringstream oss;
	this->Date::print_long(oss);
	oss << " ";
	this->Time::print_long(oss);
	stream << oss.str();
}

DateTime DateTime::get_current_datetime()
{
	Date date = Date::get_current_date();
	Time time = Time::get_current_time();
	return DateTime(std::move(date), std::move(time));
}

// Operator implementations
bool DateTime::operator==(const DateTime& date_time) const
{
	return (date_ == date_time.date_ && time_ == date_time.time_);
}
bool DateTime::operator!=(const DateTime& date_time) const
{
	return !(*this == date_time);
}
bool DateTime::operator>(const DateTime& date_time) const
{
	return (date_ > date_time.date_ || (date_ == date_time.date_ && time_ > date_time.time_));
}
bool DateTime::operator<(const DateTime& date_time) const
{
	return (date_ < date_time.date_ || (date_ == date_time.date_ && time_ < date_time.time_));
}
bool DateTime::operator<=(const DateTime& date_time) const
{
	return (date_ <= date_time.date_ || (date_ == date_time.date_ && time_ <= date_time.time_));
}
bool DateTime::operator>=(const DateTime& date_time) const
{
	return (date_ >= date_time.date_ || (date_ == date_time.date_ && time_ >= date_time.time_));
}

std::ostream& operator<<(std::ostream& stream, const DateTime& dateTime)
{
	dateTime.print_short(stream);
	return stream;
}