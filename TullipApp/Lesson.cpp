#include "Lesson.h"

Lesson::Lesson(const DateTime& datetime, const Address& address, const std::map<Child*, std::optional<Date>>& children)
	: datetime_(datetime), address_(address), children_(children) {
}

Lesson::Lesson(DateTime&& datetime, std::string&& address, std::map<Child*, std::optional<Date>>&& children)
	: datetime_(datetime), address_(address), children_(std::move(children)) {
}

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