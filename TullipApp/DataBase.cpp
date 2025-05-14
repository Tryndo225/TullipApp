#include "DataBase.h"
#include "Helper_Functions.h"
#include "DataBase_Parser_Functions.h"
#include <algorithm>

void Database::import_Lessons_from_csv_file(std::istream& stream)
{
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.empty() || line[0] == '#' || line == "Lessons:") continue;
		if (line == "Employees:" || line == "Parents:" || line == "Children:") break;

		CSV_Parser::parse_lesson(line, *this);
	}
}

void Database::import_Parents_from_csv_file(std::istream& stream)
{
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.empty() || line[0] == '#' || line == "Parents:") continue;
		if (line == "Employees:" || line == "Lessons:" || line == "Children:") break;

		CSV_Parser::parse_parent(line, *this);
	}
}

void Database::import_Children_from_csv_file(std::istream& stream)
{
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.empty() || line[0] == '#' || line == "Children:") continue;
		if (line == "Employees:" || line == "Lessons:" || line == "Parents:") break;

		CSV_Parser::parse_child(line, *this);
	}
}

void Database::import_Employees_from_csv_file(std::istream& stream)
{
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.empty() || line[0] == '#' || line == "Employees:") continue;
		if (line == "Lessons:" || line == "Parents:" || line == "Children:") break;

		CSV_Parser::parse_employee(line, *this);
	}
}

void Database::export_Lessons_to_csv_file(std::ostream& stream) const
{
	stream << "Lessons:" << std::endl;
	for (const auto& lesson : lessons_)
	{
		stream << *lesson << std::endl;
	}
}

void Database::export_Parents_to_csv_file(std::ostream& stream) const
{
	stream << "Parents:" << std::endl;
	for (const auto& parent : parents_)
	{
		stream << *parent << std::endl;
	}
}

void Database::export_Children_to_csv_file(std::ostream& stream) const
{
	stream << "Children:" << std::endl;
	for (const auto& child : children_)
	{
		stream << *child << std::endl;
	}
}

void Database::export_Employees_to_csv_file(std::ostream& stream) const
{
	stream << "Employees:" << std::endl;
	for (const auto& employee : employees_)
	{
		stream << *employee << std::endl;
	}
}

template <typename Key, typename Value>
void Database::remove_from_map(std::multimap<Key, Value*>& map, const Key& key, const Value* value)
{
	auto range = map.equal_range(key);  // returns [first, last) with matching keys
	for (auto it = range.first; it != range.second; ++it)
	{
		if (it->second == value)
		{
			map.erase(it);
			break;
		}
	}
}

template <typename T>
void Database::search_lavenstein_name_surname(std::vector<T*>& vector, const std::string& reference_name, const std::string& reference_surname) const
{
	static_assert(std::is_base_of<Person, T>::value, "T must be derived from Person");

	std::unordered_map<std::string, size_t> distance;
	std::sort(vector.begin(), vector.end(), [&distance, &reference_name, &reference_surname](const auto& a, const auto& b) {
		auto a_key = a->get_name() + " " + a->get_surname();

		if (distance.find(a_key) == distance.end())
		{
			distance[a_key] = search_lavenstein_name_surname_helper(a->get_name(), a->get_surname(), reference_name, reference_surname);
		}

		auto b_key = b->get_name() + " " + b->get_surname();

		if (distance.find(b_key) == distance.end())
		{
			distance[b_key] = search_lavenstein_name_surname_helper(b->get_name(), b->get_surname(), reference_name, reference_surname);
		}
		return distance[a_key] < distance[b_key];
		});
}

Lesson* Database::add_lesson(const Lesson& lesson)
{
	lessons_.emplace_back(std::make_unique<Lesson>(lesson));
	lesson_by_schedule.insert({ lesson.get_schedule(), lessons_.back().get() });
	return lessons_.back().get();
}

void Database::update_lesson_start(Lesson* lesson)
{
	remove_from_map(lesson_by_schedule, lesson->get_schedule(), lesson);
}

void Database::update_lesson_end(Lesson* lesson)
{
	lesson_by_schedule.insert({ lesson->get_schedule(), lesson });
}

void Database::remove_lesson(const Lesson* lesson)
{
	remove_all(lessons_, *lesson);

	auto it = lesson_by_schedule.find(lesson->get_schedule());
	while (it != lesson_by_schedule.end() && it->second != lesson) it++;

	if (it != lesson_by_schedule.end())
	{
		lesson_by_schedule.erase(it);
	}
}

std::vector<Lesson*> Database::search_lessons_by_child_name_surname(const std::string& reference_name, const std::string& reference_surname) const
{
	auto likely_child = search_children(reference_name, reference_surname)[0];
	return filter_lesson_by_child_name(likely_child->get_name(), filter_lesson_by_child_surname(likely_child->get_surname()));
}

std::vector<Lesson*> Database::sort_lessons_by_time() const
{
	std::vector<Lesson*> lessons;
	for (const auto& lesson : lessons_)
	{
		lessons.push_back(lesson.get());
	}
	std::sort(lessons.begin(), lessons.end(), [](Lesson* a, Lesson* b) { return a->get_schedule() < b->get_schedule(); });
	return lessons;
}

std::vector<Lesson*> Database::sort_lessons_by_day() const
{
	std::vector<Lesson*> lessons;
	for (const auto& lesson : lessons_)
	{
		lessons.push_back(lesson.get());
	}
	std::sort(lessons.begin(), lessons.end(), [](Lesson* a, Lesson* b) { return a->get_day() < b->get_day(); });
	return lessons;
}

std::multimap<Schedule, Lesson*>& Database::sort_lessons_by_schedule()
{
	return lesson_by_schedule;
}

std::vector<Lesson*> Database::filter_lesson_by_day(const std::string& day, std::optional <std::vector<Lesson*>> lessons) const
{
	if (lessons)
	{
		return filter(lessons.value(), [day](Lesson& lesson)
			{
				return weekday_to_string(lesson.get_day()) == day;
			});
	}
	else
	{
		return filter(lessons_, [day](Lesson& lesson)
			{
				return weekday_to_string(lesson.get_day()) == day;
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

Parent* Database::get_parent_by_name_surname(const std::string& name_surname) const
{
	auto name = name_surname.substr(0, name_surname.find(' '));
	auto surname = name_surname.substr(name_surname.find(' ') + 1);

	auto filetered = filter_parent_by_name(name, filter_parent_by_surname(surname));

	if (filetered.size() == 1)
	{
		return filetered[0];
	}
	else if (filetered.size() > 1)
	{
		throw std::runtime_error("Multiple parents found with the same name and surname.");
	}
	else
	{
		return nullptr;
	}
}

Parent* Database::add_parent(const Parent& parent)
{
	parents_.emplace_back(std::make_unique<Parent>(parent));
	parent_by_name.insert({ parent.get_name(), parents_.back().get() });
	parent_by_surname.insert({ parent.get_surname(), parents_.back().get() });
	parent_by_email.insert({ parent.get_email().get_email(), parents_.back().get() });
	return parents_.back().get();
}

void Database::update_parent_start(Parent* parent)
{
	remove_from_map(parent_by_name, parent->get_name(), parent);
	remove_from_map(parent_by_surname, parent->get_surname(), parent);
	remove_from_map(parent_by_email, parent->get_email().get_email(), parent);
}

void Database::update_parent_end(Parent* parent)
{
	parent_by_name.insert({ parent->get_name(), parent });
	parent_by_surname.insert({ parent->get_surname(), parent });
	parent_by_email.insert({ parent->get_email().get_email(), parent });
}

void Database::remove_parent(const Parent* parent)
{
	for (auto& child : parent->get_children())
	{
		if (child->get_mom() == parent)
		{
			child->set_mom(nullptr);
		}
		else if (child->get_dad() == parent)
		{
			child->set_dad(nullptr);
		}
	}

	remove_from_map(parent_by_name, parent->get_name(), parent);
	remove_from_map(parent_by_surname, parent->get_surname(), parent);
	remove_from_map(parent_by_email, parent->get_email().get_email(), parent);
	remove_all(parents_, *parent);
}

std::vector<Parent*> Database::search_parents(const std::string& reference_name, const std::string& reference_surname) const
{
	std::vector<Parent*> parents;
	for (const auto& parent : parents_)
	{
		parents.push_back(parent.get());
	}

	search_lavenstein_name_surname(parents, reference_name, reference_surname);

	return parents;
}

std::multimap<std::string, Parent*> Database::sort_parents_by_name()
{
	return parent_by_name;
}

std::multimap<std::string, Parent*> Database::sort_parents_by_surname()
{
	return parent_by_surname;
}

std::multimap<std::string, Parent*> Database::sort_parents_by_email()
{
	return parent_by_email;
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

Child* Database::get_child_by_name_surname(const std::string& name_surname) const
{
	auto name = name_surname.substr(0, name_surname.find(' '));
	auto surname = name_surname.substr(name_surname.find(' ') + 1);

	auto filtered_surname = filter_child_by_surname(surname);

	auto filtered = filter_child_by_name(name, filter_child_by_surname(surname));

	if (filtered.size() == 1)
	{
		return filtered[0];
	}
	else if (filtered.size() > 1)
	{
		throw std::runtime_error("Multiple children found with the same name and surname.");
	}
	else
	{
		return nullptr;
	}
}

Child* Database::add_child(const Child& child)
{
	children_.emplace_back(std::make_unique<Child>(child));
	child_by_name.insert({ child.get_name(), children_.back().get() });
	child_by_surname.insert({ child.get_surname(), children_.back().get() });
	child_by_birth_date.insert({ child.get_birth_date(), children_.back().get() });
	return children_.back().get();
}

void Database::update_child_start(Child* child)
{
	remove_from_map(child_by_name, child->get_name(), child);
	remove_from_map(child_by_surname, child->get_surname(), child);
	remove_from_map(child_by_birth_date, child->get_birth_date(), child);
}

void Database::update_child_end(Child* child)
{
	child_by_name.insert({ child->get_name(), child });
	child_by_surname.insert({ child->get_surname(), child });
	child_by_birth_date.insert({ child->get_birth_date(), child });
}

void Database::remove_child(Child* child)
{
	if (child->get_mom() != nullptr)
	{
		child->get_mom()->remove_child(child);
	}
	if (child->get_dad() != nullptr)
	{
		child->get_dad()->remove_child(child);
	}

	for (auto& lesson : lessons_)
	{
		lesson->remove_child(child);
	}

	remove_from_map(child_by_name, child->get_name(), child);
	remove_from_map(child_by_surname, child->get_surname(), child);
	remove_from_map(child_by_birth_date, child->get_birth_date(), child);
	remove_all(children_, *child);
}

std::vector<Child*> Database::search_children(const std::string& reference_name, const std::string& reference_surname) const
{
	std::vector<Child*> children;
	for (const auto& child : children_)
	{
		children.push_back(child.get());
	}
	search_lavenstein_name_surname(children, reference_name, reference_surname);
	return children;
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
		return filter_multimap_by_keys(child_by_surname, [surname](const std::string& key)
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

Employee* Database::add_employee(const Employee& employee)
{
	employees_.emplace_back(std::make_unique<Employee>(employee));
	employee_by_name.insert({ employee.get_name(), employees_.back().get() });
	employee_by_surname.insert({ employee.get_surname(), employees_.back().get() });
	return employees_.back().get();
}

void Database::update_employee_start(Employee* employee)
{
	remove_from_map(employee_by_name, employee->get_name(), employee);
	remove_from_map(employee_by_surname, employee->get_surname(), employee);
}

void Database::update_employee_end(Employee* employee)
{
	employee_by_name.insert({ employee->get_name(), employee });
	employee_by_surname.insert({ employee->get_surname(), employee });
}

Employee* Database::get_employee_by_name_surname(const std::string& name_surname) const
{
	auto name = name_surname.substr(0, name_surname.find(' '));
	auto surname = name_surname.substr(name_surname.find(' ') + 1);
	auto filetered = filter_employee_by_name(name, filter_employee_by_surname(surname));
	if (filetered.size() == 1)
	{
		return filetered[0];
	}
	else if (filetered.size() > 1)
	{
		throw std::runtime_error("Multiple employees found with the same name and surname.");
	}
	else
	{
		return nullptr;
	}
}

void Database::remove_employee(Employee* employee)
{
	for (auto& lesson : lessons_)
	{
		lesson->remove_employee(employee);
	}

	remove_from_map(employee_by_name, employee->get_name(), employee);
	remove_from_map(employee_by_surname, employee->get_surname(), employee);
	remove_all(employees_, *employee);
}

std::vector<Employee*> Database::search_employees(const std::string& reference_name, const std::string& reference_surname) const
{
	std::vector<Employee*> employees;
	for (const auto& employee : employees_)
	{
		employees.push_back(employee.get());
	}
	search_lavenstein_name_surname(employees, reference_name, reference_surname);
	return employees;
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
	import_Parents_from_csv_file(stream);
	import_Children_from_csv_file(stream);
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
	export_Parents_to_csv_file(stream);
	export_Children_to_csv_file(stream);
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
	lesson_by_schedule.clear();
}