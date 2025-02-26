#ifndef DATETIME_H_
#define DATETIME_H_ 
#include <iostream>


enum class Month
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
	December
};

enum class WeekDays
{
	Monday,
	Tuesday,
	Wednesday, 
	Thursday,
	Friday,
	Saturday,
	Sunday
};

class Date
{
protected:
	unsigned int date_;
	// 00000000 00000000 00000000 00000000
	// \_____________________/\____/\____/
	//           Year          Month  Day
public:
	Date(unsigned short day, unsigned short month, unsigned int year);
	Date(const Date& date);
	void SetDay(unsigned short day);
	unsigned short GetDay();
	void SetMonth(Month month);
	Month GetMonth();
	void SetYear(unsigned int year);
	unsigned int GetYear();

	void PrintLong(const std::ostream& stream);
	void PrintShort(const std::ostream& stream);
	inline std::ostream& operator<<(std::ostream& stream);

	static WeekDays DateToWeekDay(const Date& date);
};

class Time
{
protected:
	unsigned int time_;
// 00000000 00000000 00000000 00000000
//          \______/ \______/ \______/
//			  Hour     Mins     Secs
public:
	Time(unsigned short hours, unsigned short mins, unsigned short secs);
	Time(const Time& time);
	void SetSeconds(unsigned short secs);
	unsigned short GetSeconds();
	void SetMinutes(unsigned short mins);
	unsigned short GetMinutes();
	void SetHours(unsigned short years);
	unsigned short GetHours();

	void PrintLong(const std::ostream& stream);
	void PrintShort(const std::ostream& stream);
	inline std::ostream& operator<<(std::ostream& stream);



};

class DateTime : public Date, public Time
{
public:
	DateTime(unsigned short day, unsigned short month, unsigned int year, unsigned short hours, unsigned short mins, unsigned short secs);
	DateTime(const DateTime& date_time);
	DateTime(const Date& date, const Time& time);
	void PrintLong(const std::ostream& stream);
	void PrintShort(const std::ostream& stream);
	inline std::ostream& operator<<(std::ostream& stream);
};


#endif
