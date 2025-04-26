#include "DataBase.h"
#include "Helper_Functions.h"

#include <algorithm>

void Database::import_Lessons_from_csv_file(const std::string& filename)
{
	// Implementation for importing lessons from a CSV file
}

void Database::import_Parents_from_csv_file(const std::string& filename)
{
	// Implementation for importing parents from a CSV file
}

void Database::import_Children_from_csv_file(const std::string& filename)
{
	// Implementation for importing children from a CSV file
}

void Database::import_Employees_from_csv_file(const std::string& filename)
{
	// Implementation for importing employees from a CSV file
}

void Database::export_Lessons_to_csv_file(const std::string& filename) const
{
	// Implementation for exporting lessons to a CSV file
}

void Database::export_Parents_to_csv_file(const std::string& filename) const
{
	// Implementation for exporting parents to a CSV file
}

void Database::export_Children_to_csv_file(const std::string& filename) const
{
	// Implementation for exporting children to a CSV file
}

void Database::export_Employees_to_csv_file(const std::string& filename) const
{
	// Implementation for exporting employees to a CSV file
}

void Database::add_lesson(const Lesson& lesson)
{
	lessons_.emplace_back(std::make_unique<Lesson>(lesson));
	lesson_by_datetime.insert({ lesson.get_datetime(), lessons_.back().get() });
}

void Database::remove_lesson(const Lesson* lesson)
{
	remove_all(lessons_, *lesson);

	auto it = lesson_by_datetime.find(lesson->get_datetime());
	while (it != lesson_by_datetime.end() && it->second != lesson) it++;

	if (it != lesson_by_datetime.end())
	{
		lesson_by_datetime.erase(it);
	}
}

std::multimap<DateTime, Lesson*>& Database::sort_lessons_by_datetime()
{
	return lesson_by_datetime;
}

std::vector<Lesson> Database::filter_lesson_by_day(const std::string& day, std::optional <std::vector<Lesson>> lessons) const
{
	if (lessons)
	{
		return filter(lessons.value(), [day](Lesson lesson)
			{
				return weekday_to_string(Date::get_weekday_from_date(lesson.get_date())) == day;
			});
	}
	else
	{
		return filter(lessons_, [day](Lesson lesson)
			{
				return weekday_to_string(Date::get_weekday_from_date(lesson.get_date())) == day;
			});
	}
}