#include "Lesson.h"

Lesson::Lesson(const Date& date, const Time& time, const Address& address, const std::map<Child*, std::optional<Date>>& children)
	: date_(date), time_(time), address_(address), children_(children) {}

Lesson::Lesson(Date&& date, Time&& time, std::string&& address, std::map<Child*, std::optional<Date>>&& children)
	: date_(date), time_(time), address_(address), children_(std::move(children)) {}

const std::vector<Child*> Lesson::get_children() const
{
	std::vector<Child*> child_list;
	for (const auto& pair : children_)
	{
		child_list.push_back(pair.first);
	}
	return child_list;
}

const std::vector<Child*> Lesson::get_children_payment(bool payed) const
{
	std::vector<Child*> child_list;
	Date current_date = Date::get_current_date();
	for (const auto& pair : children_)
	{
		if ((pair.second <= current_date) == payed)
		{
			child_list.push_back(pair.first);
		}
	}
	return child_list;
}