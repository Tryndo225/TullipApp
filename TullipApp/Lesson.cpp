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

const std::vector<std::pair<Child*, bool>> Lesson::get_attendance(const Date& date)
{
	std::vector<std::pair<Child*, bool>> attendance_list;
	auto it = attendance_.find(date);
	if (it != attendance_.end())
	{
		for (const auto& child : children_)
		{
			bool present = std::find(it->second.begin(), it->second.end(), child.first) != it->second.end();
			attendance_list.emplace_back(child.first, present);
		}
	}
	else
	{
		for (const auto& child : children_)
		{
			attendance_list.emplace_back(child.first, false);
		}
	}
	return attendance_list;
}

void Lesson::set_absent(const Date& date, Child* child)
{
	auto it = attendance_.find(date);
	if (it != attendance_.end())
	{
		remove_all(it->second, child);
	}
}