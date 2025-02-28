#ifndef DATETIME_EXCEPTIONS_H_
#define DATETIME_EXCEPTIONS_H_

#include <string>
#include <iostream>



class DateTimeException
{
private:
	const std::string message_;
public:
	inline DateTimeException(std::string message);
	inline DateTimeException(std::string&& message);
	inline virtual const std::string& Message() const;
	inline virtual void Print(std::ostream& stream = std::cout) const;
	inline friend std::ostream& operator<<(std::ostream& stream, DateTimeException);
	inline ~DateTimeException();
};

class IncorrectIntInput
{
protected:
	const int input_;
public:
	inline IncorrectIntInput(int input);
	inline virtual std::string Message() const = 0;
	inline virtual void Print(std::ostream& stream = std::cout) const { stream << Message(); }
	inline friend std::ostream& operator<<(std::ostream& stream, DateTimeException);
	inline ~IncorrectIntInput();
};

class IncorrectHoursFormat : public IncorrectIntInput
{
public:
	using IncorrectIntInput::IncorrectIntInput;
	inline virtual std::string Message() const override;
};

class IncorrectMinutesFormat : public IncorrectIntInput
{
public:
	using IncorrectIntInput::IncorrectIntInput;
	inline virtual std::string Message() const override;
};

class IncorrectSecondsFormat : public IncorrectIntInput
{
public:
	using IncorrectIntInput::IncorrectIntInput;
	inline virtual std::string Message() const override;
};

class IncorrectDayFormat : public IncorrectIntInput
{
public:
	using IncorrectIntInput::IncorrectIntInput;
	inline virtual std::string Message() const override;
};

class IncorrectMonthFormat : public IncorrectIntInput
{
public:
	using IncorrectIntInput::IncorrectIntInput;
	inline virtual std::string Message() const override;
};

class IncorrectYearFormat : public IncorrectIntInput
{
public:
	using IncorrectIntInput::IncorrectIntInput;
	inline virtual std::string Message() const override;
};

#endif