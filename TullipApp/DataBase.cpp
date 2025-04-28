#include "DataBase.h"
#include "Helper_Functions.h"

#include <algorithm>

void Database::import_Lessons_from_csv_file(std::istream& stream)
{
	// Implementation for importing lessons from a CSV file
}

void Database::import_Parents_from_csv_file(std::istream& stream)
{
	// Implementation for importing parents from a CSV file
}

void Database::import_Children_from_csv_file(std::istream& stream)
{
	// Implementation for importing children from a CSV file
}

void Database::import_Employees_from_csv_file(std::istream& stream)
{
	// Implementation for importing employees from a CSV file
}

void Database::export_Lessons_to_csv_file(std::ostream& stream) const
{
	// Implementation for exporting lessons to a CSV file
}

void Database::export_Parents_to_csv_file(std::ostream& stream) const
{
	// Implementation for exporting parents to a CSV file
}

void Database::export_Children_to_csv_file(std::ostream& stream) const
{
	// Implementation for exporting children to a CSV file
}

void Database::export_Employees_to_csv_file(std::ostream& stream) const
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

std::vector<Lesson*> Database::filter_lesson_by_day(const std::string& day, std::optional <std::vector<Lesson*>> lessons) const
{
	if (lessons)
	{
		return filter(lessons.value(), [day](Lesson& lesson)
			{
				return weekday_to_string(Date::get_weekday_from_date(lesson.get_date())) == day;
			});
	}
	else
	{
		return filter(lessons_, [day](Lesson& lesson)
			{
				return weekday_to_string(Date::get_weekday_from_date(lesson.get_date())) == day;
			});
	}
}

std::vector<Lesson*> Database::filter_lesson_by_address(const std::string& address, std::optional <std::vector<Lesson*>> lessons) const
{
	if (lessons)
	{
		return filter(lessons.value(), [address](Lesson& lesson)
			{
				return (lesson).get_address() == address;
			});
	}
	else
	{
		return filter(lessons_, [address](Lesson& lesson)
			{
				return lesson.get_address() == address;
			});
	}
}

std::vector<Lesson*> Database::filter_lesson_by_child_name(const std::string& name, std::optional <std::vector<Lesson*>> lessons) const
{
	auto children = filter_child_by_name(name);
	if (lessons)
	{
		return filter(lessons.value(), [children](Lesson& lesson)
			{
				return contains_any_from_vector(lesson.get_children(), children);
			});
	}
	else
	{
		return filter(lessons_, [children](Lesson lesson)
			{
				return contains_any_from_vector(lesson.get_children(), children);
			});
	}
}

std::vector<Lesson*> Database::filter_lesson_by_child_surname(const std::string& surname, std::optional <std::vector<Lesson*>> lessons) const
{
	auto children = filter_child_by_surname(surname);
	if (lessons)
	{
		return filter(lessons.value(), [children](Lesson& lesson)
			{
				return contains_any_from_vector(lesson.get_children(), children);
			});
	}
	else
	{
		return filter(lessons_, [children](Lesson lesson)
			{
				return contains_any_from_vector(lesson.get_children(), children);
			});
	}
}

void Database::add_parent(const Parent& parent)
{
	parents_.emplace_back(std::make_unique<Parent>(parent));
	parent_by_name.insert({ parent.get_name(), parents_.back().get() });
	parent_by_surname.insert({ parent.get_surname(), parents_.back().get() });
	parent_by_email.insert({ parent.get_email().get_email(), parents_.back().get() });
}

void Database::remove_parent(const Parent* parent)
{
	remove_all(parents_, *parent);

	auto it = parent_by_name.find(parent->get_name());
	while (it != parent_by_name.end() && it->second != parent) it++;

	if (it != parent_by_name.end())
	{
		parent_by_name.erase(it);
	}
}

std::multimap<std::string, Parent*> Database::sort_parents_by_name()
{
	return parent_by_name;
}

std::multimap<std::string, Parent*> Database::sort_parents_by_surname()
{
	return parent_by_surname;
}

std::vector<Parent*> Database::filter_parent_by_name(const std::string& name, std::optional <std::vector<Parent*>> parents) const
{
	if (parents)
	{
		return filter(parents.value(), [name](Parent& parent)
			{
				return parent.get_name() == name;
			});
	}
	else
	{
		return filter_multimap_by_keys(parent_by_name, [name](const std::string& key)
			{
				return key == name;
			});
	}
}

std::vector<Parent*> Database::filter_parent_by_surname(const std::string& surname, std::optional <std::vector<Parent*>> parents) const
{
	if (parents)
	{
		return filter(parents.value(), [surname](Parent& parent)
			{
				return parent.get_surname() == surname;
			});
	}
	else
	{
		return filter_multimap_by_keys(parent_by_surname, [surname](const std::string& key)
			{
				return key == surname;
			});
	}
}

std::vector<Parent*> Database::filter_parent_by_email(const std::string& email, std::optional <std::vector<Parent*>> parents) const
{
	if (parents)
	{
		return filter(parents.value(), [email](Parent& parent)
			{
				return parent.get_email().get_email() == email;
			});
	}
	else
	{
		return filter(parents_, [email](Parent& parent)
			{
				return parent.get_email().get_email() == email;
			});
	}
}

void Database::add_child(const Child& child)
{
	children_.emplace_back(std::make_unique<Child>(child));
	child_by_name.insert({ child.get_name(), children_.back().get() });
	child_by_surname.insert({ child.get_surname(), children_.back().get() });
	child_by_birth_date.insert({ child.get_birth_date(), children_.back().get() });
}

void Database::remove_child(const Child* child)
{
	remove_all(children_, *child);
	auto it = child_by_name.find(child->get_name());
	while (it != child_by_name.end() && it->second != child) it++;
	if (it != child_by_name.end())
	{
		child_by_name.erase(it);
	}
}

std::multimap<std::string, Child*> Database::sort_children_by_name()
{
	return child_by_name;
}

std::multimap<std::string, Child*> Database::sort_children_by_surname()
{
	return child_by_surname;
}

std::multimap<Date, Child*> Database::sort_children_by_birth_date()
{
	return child_by_birth_date;
}

std::vector<Child*> Database::filter_child_by_name(const std::string& name, std::optional <std::vector<Child*>> children) const
{
	if (children)
	{
		return filter(children.value(), [name](Child& child)
			{
				return child.get_name() == name;
			});
	}
	else
	{
		return filter_multimap_by_keys(child_by_name, [name](const std::string& key)
			{
				return key == name;
			});
	}
}

std::vector<Child*> Database::filter_child_by_surname(const std::string& surname, std::optional <std::vector<Child*>> children) const
{
	if (children)
	{
		return filter(children.value(), [surname](Child& child)
			{
				return child.get_surname() == surname;
			});
	}
	else
	{
		return filter_multimap_by_keys(child_by_name, [surname](const std::string& key)
			{
				return key == surname;
			});
	}
}

std::vector<Child*> Database::filter_child_by_age(const int age, std::optional <std::vector<Child*>> children) const
{
	if (children)
	{
		return filter(children.value(), [age](Child& child)
			{
				return child.get_age() == age;
			});
	}
	else
	{
		Date current_date = Date::get_current_date();
		return filter_multimap_by_keys(child_by_birth_date, [age, current_date](const Date& key)
			{
				return (current_date - key).get_year() == age;
			});
	}
}

std::vector<Child*> Database::filter_child_by_parent_name(const std::string& parent_name, std::optional <std::vector<Child*>> children) const
{
	if (children)
	{
		return filter(children.value(), [parent_name](Child& child)
			{
				if (child.get_dad() != nullptr && child.get_dad()->get_name() == parent_name)
				{
					return true;
				}
				else if (child.get_mom() != nullptr && child.get_mom()->get_name() == parent_name)
				{
					return true;
				}
				return false;
			});
	}
	else
	{
		return filter(children_, [parent_name](Child& child)
			{
				if (child.get_dad() != nullptr && child.get_dad()->get_name() == parent_name)
				{
					return true;
				}
				else if (child.get_mom() != nullptr && child.get_mom()->get_name() == parent_name)
				{
					return true;
				}
				return false;
			});
	}
}

std::vector<Child*> Database::filter_child_by_parent_surname(const std::string& parent_surname, std::optional <std::vector<Child*>> children) const
{
	if (children)
	{
		return filter(children.value(), [parent_surname](Child& child)
			{
				if (child.get_dad() != nullptr && child.get_dad()->get_surname() == parent_surname)
				{
					return true;
				}
				else if (child.get_mom() != nullptr && child.get_mom()->get_surname() == parent_surname)
				{
					return true;
				}
				return false;
			});
	}
	else
	{
		return filter(children_, [parent_surname](Child& child)
			{
				if (child.get_dad() != nullptr && child.get_dad()->get_surname() == parent_surname)
				{
					return true;
				}
				else if (child.get_mom() != nullptr && child.get_mom()->get_surname() == parent_surname)
				{
					return true;
				}
				return false;
			});
	}
}

void Database::add_employee(const Employee& employee)
{
	employees_.emplace_back(std::make_unique<Employee>(employee));
	employee_by_name.insert({ employee.get_name(), employees_.back().get() });
	employee_by_surname.insert({ employee.get_surname(), employees_.back().get() });
}

void Database::remove_employee(const Employee* employee)
{
	remove_all(employees_, *employee);
	auto it = employee_by_name.find(employee->get_name());
	while (it != employee_by_name.end() && it->second != employee) it++;
	if (it != employee_by_name.end())
	{
		employee_by_name.erase(it);
	}
}

std::multimap<std::string, Employee*> Database::sort_employees_by_name()
{
	return employee_by_name;
}

std::multimap<std::string, Employee*> Database::sort_employees_by_surname()
{
	return employee_by_surname;
}

std::vector<Employee*> Database::filter_employee_by_name(const std::string& name, std::optional<std::vector<Employee*>> employees) const
{
	if (employees)
	{
		return filter(employees.value(), [name](Employee& employee)
			{
				return employee.get_name() == name;
			});
	}
	else
	{
		return filter_multimap_by_keys(employee_by_name, [name](const std::string& key)
			{
				return key == name;
			});
	}
}

std::vector<Employee*> Database::filter_employee_by_surname(const std::string& surname, std::optional<std::vector<Employee*>> employees) const
{
	if (employees)
	{
		return filter(employees.value(), [surname](Employee& employee)
			{
				return employee.get_surname() == surname;
			});
	}
	else
	{
		return filter_multimap_by_keys(employee_by_surname, [surname](const std::string& key)
			{
				return key == surname;
			});
	}
}

void Database::import_from_stream(std::istream& stream)
{
	import_Children_from_csv_file(stream);
	import_Parents_from_csv_file(stream);
	import_Employees_from_csv_file(stream);
	import_Lessons_from_csv_file(stream);
}

void Database::import_from_csv_file(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file: " + filename);
	}
	import_from_stream(file);
}

void Database::export_to_stream(std::ostream& stream) const
{
	export_Children_to_csv_file(stream);
	export_Parents_to_csv_file(stream);
	export_Employees_to_csv_file(stream);
	export_Lessons_to_csv_file(stream);
}

void Database::export_to_csv_file(const std::string& filename) const
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file: " + filename);
	}
	export_to_stream(file);
}

void Database::clear()
{
	lessons_.clear();
	parents_.clear();
	children_.clear();
	employees_.clear();
	child_by_name.clear();
	child_by_surname.clear();
	child_by_birth_date.clear();
	parent_by_name.clear();
	parent_by_surname.clear();
	parent_by_email.clear();
	employee_by_name.clear();
	employee_by_surname.clear();
	lesson_by_datetime.clear();
}