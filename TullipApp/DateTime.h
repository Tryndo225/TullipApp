#ifndef DATETIME_H_
#define DATETIME_H_ 
#include <iostream>
#include <string>


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
	std::string GetDate();

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
// \______/ \______/ \______/ \______/
//	 Zone	  Hour     Mins     Secs
// Zone Bit 1 = +/-, Rest is amount of 15 mins intervals
public:
	Time(unsigned short hours, unsigned short mins, unsigned short secs);
	Time(const Time& time);
	void SetSeconds(unsigned short secs);
	unsigned short GetSeconds();
	void SetMinutes(unsigned short mins);
	unsigned short GetMinutes();
	void SetHours(unsigned short years);
	unsigned short GetHours();
	void SetZone();
	std::string GetZone();

	std::string GetTime();

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
	std::string GetDateTime();
	
	void PrintLong(const std::ostream& stream);
	void PrintShort(const std::ostream& stream);
	inline std::ostream& operator<<(std::ostream& stream);
};


#endif
