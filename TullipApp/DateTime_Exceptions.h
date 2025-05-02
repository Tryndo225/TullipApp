/**
 * @file DateTime_Exceptions.h
 * @brief Defines error messages and the `DateTimeError` exception class for date and time operations.
 * @details This file contains constants for error messages related to invalid date and time values,
 *          as well as the `DateTimeError` class for handling exceptions in date and time operations.
 */

#ifndef DATETIME_EXCEPTIONS_H_
#define DATETIME_EXCEPTIONS_H_

#include <string>
#include <iostream>
#include <exception>

 /**
  * @brief Error message for invalid day values.
  * @details This constant represents the error message for days that are out of the allowed range (1-31).
  */
inline const char* DAY_RANGE = "Day is out of allowed range (1-31)";

/**
 * @brief Error message for invalid month values.
 * @details This constant represents the error message for months that are out of the allowed range (1-12).
 */
inline const char* MONTH_RANGE = "Month is out of allowed range (1-12)";

/**
 * @brief Error message for invalid year values.
 * @details This constant represents the error message for years that are out of the allowed range (1-2097151).
 */
inline const char* YEAR_RANGE = "Year is out of allowed range (1-2097151)";

/**
 * @brief Error message for invalid seconds values.
 * @details This constant represents the error message for seconds that are out of the allowed range (0-59).
 */
inline const char* SECONDS_RANGE = "Seconds is out of allowed range (0-59)";

/**
 * @brief Error message for invalid minutes values.
 * @details This constant represents the error message for minutes that are out of the allowed range (0-59).
 */
inline const char* MINUTES_RANGE = "Minutes is out of allowed range (0-59)";

/**
 * @brief Error message for invalid hours values.
 * @details This constant represents the error message for hours that are out of the allowed range (0-23).
 */
inline const char* HOURS_RANGE = "Hours is out of allowed range (0-23)";

/**
 * @brief Error message for invalid time zone values.
 * @details This constant represents the error message for time zones that are out of the allowed range (UTC-12 to UTC+14).
 */
inline const char* TIMEZONE_RANGE = "Time zone is out of allowed range (UTC-12 to UTC+14)";

/**
 * @class DateTimeError
 * @brief Exception class for DateTime-related errors.
 * @details The `DateTimeError` class is used to represent errors that occur when working with date and time values.
 *          It extends the standard `std::exception` class and provides additional functionality for error handling.
 */
class DateTimeError : public std::exception
{
private:
	const char* message_; ///< The error message associated with the exception.

public:
	/**
	 * @brief Constructs a `DateTimeError` with the given error message.
	 * @param message The error message to associate with the exception.
	 */
	explicit DateTimeError(const char* message);

	/**
	 * @brief Default copy constructor.
	 * @details Creates a copy of an existing `DateTimeError` object.
	 * @param error The `DateTimeError` object to copy.
	 */
	DateTimeError(const DateTimeError& error) = default;

	/**
	 * @brief Default move constructor.
	 * @details Moves an existing `DateTimeError` object.
	 * @param error The `DateTimeError` object to move.
	 */
	DateTimeError(DateTimeError&& error) = default;

	/**
	 * @brief Gets the error message associated with the exception.
	 * @return A constant reference to the error message as a `std::string`.
	 */
	inline const std::string& message() const;

	/**
	 * @brief Gets the error message as a C-style string.
	 * @details Overrides the `what()` method from `std::exception` to provide the error message.
	 * @return A pointer to the error message as a C-style string.
	 */
	inline const char* what() const noexcept override;

	/**
	 * @brief Prints the error message to the specified output stream.
	 * @param stream The output stream to print to. Defaults to `std::cout`.
	 */
	inline void print(std::ostream& stream = std::cout) const;

	/**
	 * @brief Outputs the error message to a stream.
	 * @details This friend function allows the `DateTimeError` object to be output directly to a stream.
	 * @param stream The output stream.
	 * @param error The `DateTimeError` object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const DateTimeError& error);

	/**
	 * @brief Default destructor.
	 * @details Cleans up resources used by the `DateTimeError` object.
	 */
	inline ~DateTimeError() = default;
};

#endif // DATETIME_EXCEPTIONS_H_
