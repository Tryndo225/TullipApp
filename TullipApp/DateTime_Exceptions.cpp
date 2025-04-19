#include "DateTime_Exceptions.h"

DateTimeError::DateTimeError(const char* message) : message_(message) {}

const std::string& DateTimeError::message() const
{
	return message_;
}

const char* DateTimeError::what() const noexcept
{
	return message_;
}

void DateTimeError::print(std::ostream& stream) const
{
	stream << message_ << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const DateTimeError& error)
{
	error.print(stream);
	return stream;
}