#include "DataBase_Parser_Functions.h"

void CSV_Parser::parse_lesson_employees(std::string& employees_str, Lesson& lesson, Database& database)
{
	std::istringstream employees_stream(employees_str);
	std::string employee_name;
	while (std::getline(employees_stream, employee_name, ','))
	{
		auto employee = database.get_employee_by_name_surname(employee_name);
		if (employee)
		{
			lesson.add_employee(employee);
		}
	}
}

void CSV_Parser::parse_lesson_children(std::string& children_str, Lesson& lesson, Database& database)
{
	std::istringstream children_stream(children_str);
	std::string child_entry;
	while (std::getline(children_stream, child_entry, ','))
	{
		auto child_name_surname = child_entry.substr(child_entry.find('[') + 1, child_entry.find(','));
		auto child_date_payed_str = child_entry.substr(child_entry.find(',') + 1, child_entry.find(']'));
		auto child = database.get_child_by_name_surname(child_name_surname);

		if (child)
		{
			lesson.add_child(child);
		}

		if (child_date_payed_str != "No Payment")
		{
			Date child_date_payed = Date(child_date_payed_str);
			lesson.set_child_payment_date(child, child_date_payed);
		}
	}
}

void CSV_Parser::parse_lesson_attendance(std::string& attendance_str, Lesson& lesson, Database& database)
{
	std::istringstream attendance_stream(attendance_str);
	std::string single_attendance_str, attendance_date_str, attendance_children_str;
	while (std::getline(attendance_stream, single_attendance_str, ','))
	{
		attendance_date_str = single_attendance_str.substr(0, single_attendance_str.find(':'));
		Date attendance_date = Date(attendance_date_str);

		attendance_children_str = single_attendance_str.substr(single_attendance_str.find('[') + 1, single_attendance_str.find(']'));

		std::vector<Child*> attendance_children;
		std::istringstream attendance_children_stream(attendance_children_str);
		std::string attendance_child_name;

		while (std::getline(attendance_children_stream, attendance_child_name, ','))
		{
			auto child = database.get_child_by_name_surname(attendance_child_name);
			if (child)
			{
				attendance_children.push_back(child);
			}
		}
		lesson.set_attendance(attendance_date, attendance_children);
	}
	database.add_lesson(lesson);
}

void CSV_Parser::parse_lesson(std::string& line, Database& database)
{
	std::cout << "Parsing lesson: " << line << std::endl;
	std::istringstream iss(line);
	std::string datetime_str, address_str, employees_str, children_str, attendance_str;
	std::getline(iss, datetime_str, ',');
	std::getline(iss, address_str, ',');

	std::getline(iss, employees_str, '}');
	employees_str = employees_str.substr(employees_str.find('{') + 1);

	std::getline(iss, children_str, '}');
	children_str = children_str.substr(children_str.find('{') + 1);

	std::getline(iss, attendance_str);
	attendance_str = attendance_str.substr(attendance_str.find('{') + 1);

	DateTime datetime = DateTime(datetime_str);
	Address address = Address(address_str);
	Lesson lesson(datetime, address);

	parse_lesson_employees(employees_str, lesson, database);
	parse_lesson_children(children_str, lesson, database);
	parse_lesson_attendance(attendance_str, lesson, database);
}

void CSV_Parser::parse_child(const std::string& line, Database& database)
{
	std::istringstream iss(line);
	std::string name, surname, birth_date_str, dad_name_surname, mom_name_surname;
	std::getline(iss, name, ',');
	std::getline(iss, surname, ',');
	std::getline(iss, birth_date_str, ',');
	std::getline(iss, dad_name_surname, ',');
	std::getline(iss, mom_name_surname, ',');
	Date birth_date = Date(birth_date_str);

	auto child = database.add_child(Child(name, surname, birth_date));

	if (dad_name_surname != "No Father")
	{
		auto dad = database.get_parent_by_name_surname(dad_name_surname);
		if (dad)
		{
			child->set_dad(dad);
			dad->add_child(child);
		}
		else
		{
			throw std::runtime_error("Father not found in database");
		}
	}

	if (mom_name_surname != "No Mother")
	{
		auto mom = database.get_parent_by_name_surname(mom_name_surname);
		if (mom)
		{
			child->set_mom(mom);
			mom->add_child(child);
		}
		else
		{
			throw std::runtime_error("Mother not found in database");
		}
	}
}

void CSV_Parser::parse_parent(const std::string& line, Database& database)
{
	std::istringstream iss(line);
	std::string name, surname, is_mother_str, email_str;
	std::getline(iss, name, ',');
	std::getline(iss, surname, ',');
	std::getline(iss, is_mother_str, ',');
	std::getline(iss, email_str, ',');
	bool is_mother = (is_mother_str == "Mother");
	database.add_parent(Parent(name, surname, is_mother, email_str));
}

void CSV_Parser::parse_employee(const std::string& line, Database& database)
{
	std::cout << "Parsing employee: " << line << std::endl;
	std::istringstream iss(line);
	std::string name, surname, email_str, phone_str;
	std::getline(iss, name, ',');
	std::getline(iss, surname, ',');
	std::getline(iss, email_str, ',');
	std::getline(iss, phone_str);
	database.add_employee(Employee(name, surname, email_str, phone_str));
}