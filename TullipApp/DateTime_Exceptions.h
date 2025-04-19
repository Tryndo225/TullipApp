#ifndef DATETIME_EXCEPTIONS_H_
#define DATETIME_EXCEPTIONS_H_

#include <string>
#include <iostream>
#include <exception>

inline const char* DAY_RANGE = "Day is out of allowed range (1-31)";
inline const char* MONTH_RANGE = "Month is out of allowed range (1-12)";
inline const char* YEAR_RANGE = "Year is out of allowed range (1-2097151)";

inline const char* SECONDS_RANGE = "Seconds is out of allowed range (0-59)";
inline const char* MINUTES_RANGE = "Minutes is out of allowed range (0-59)";
inline const char* HOURS_RANGE = "Hours is out of allowed range (0-23)";
inline const char* TIMEZONE_RANGE = "Time zone is out of allowed range (UTC-12 to UTC+14)";

class DateTimeError : public std::exception
{
private:
	const char* message_;
public:
	explicit DateTimeError(const char* message);
	DateTimeError(const DateTimeError& error) = default;
	DateTimeError(DateTimeError&& error) = default;

	inline const std::string& message() const;
	inline const char* what() const noexcept override;
	inline void print(std::ostream& stream = std::cout) const;
	friend std::ostream& operator<<(std::ostream& stream, const DateTimeError& error);
	inline ~DateTimeError() = default;
};

#endif