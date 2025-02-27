#ifndef DATETIME_EXCEPTIONS_H_
#define DATETIME_EXCEPTIONS_H_

#include <string>
#include <iostream>



class DateTimeError
{
private:
	const std::string message;
public:
	inline DateTimeError(std::string message);
	inline DateTimeError(std::string&& message);
	inline const std::string& Message() const;
	inline void Print(const std::ostream& stream = std::cout) const;
	inline const std::ostream& operator<<(const std::ostream& stream) const;
	inline ~DateTimeError();
};






#endif