#ifndef DATABASE_H_
#define DATABASE_H_

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Lesson.h"
#include "Person.h"
#include "Datetime.h"

class Database
{
private:
	std::vector<std::unique_ptr<Lesson>> lessons_;
	std::vector<std::unique_ptr<Parent>> parents_;
	std::vector<std::unique_ptr<Child>> children_;
	std::vector<std::unique_ptr<Employee>> employees_;

	std::multimap<std::string, Child*> child_by_name;
	std::multimap<std::string, Child*> child_by_surname;
	std::multimap<Date, Child*> child_by_birth_date;

	std::multimap<std::string, Parent*> parent_by_name;
	std::multimap<std::string, Parent*> parent_by_surname;
	std::multimap<std::string, Parent*> parent_by_email;
	std::multimap<std::string, Parent*> parent_by_phone;

	std::multimap<std::string, Employee*> employee_by_name;
	std::multimap<std::string, Employee*> employee_by_surname;
	
	std::multimap<std::string, Lesson*> lesson_by_date;

public:
	Database() = default;

	Database(const Database& db) = default;
	Database(Database&& db) noexcept = default;

	Database& operator=(const Database& db) = default;
	Database& operator=(Database&& db) noexcept = default;

	void add_lesson(const Lesson& lesson);
	void remove_lesson(const Lesson& lesson);

	void sort_lessons_by_date();
	void sort_lessons_by_time();
	void sort_lessons_by_address();

	void find_lesson_by_date(const Date& date) const;
	void find_lesson_by_time(const Time& time) const;
	void find_lesson_by_address(const std::string& address) const;
	void find_lesson_by_child(const Child& child) const;

	void add_parent(const Parent& parent);
	void remove_parent(const Parent& parent);

	void sort_parents_by_name();
	void sort_parents_by_surname();

	void find_parent_by_name(const std::string& name) const;
	void find_parent_by_surname(const std::string& surname) const;
	void find_parent_by_email(const std::string& email) const;
	void find_parent_by_phone(const std::string& phone) const;

	void add_child(const Child& child);
	void remove_child(const Child& child);

	void sort_children_by_name();
	void sort_children_by_surname();

	void find_child_by_name(const std::string& name) const;
	void find_child_by_surname(const std::string& surname) const;
	void find_child_by_birth_date(const Date& birth_date) const;
	void find_child_by_parent(const Parent& parent) const;

	void add_employee(const Employee& employee);
	void remove_employee(const Employee& employee);

	void sort_employees_by_name();
	void sort_employees_by_surname();

	void find_employee_by_name(const std::string& name) const;
	void find_employee_by_surname(const std::string& surname) const;

	void import_from_csv_file(const std::string& filename);
	void export_to_csv_file(const std::string& filename) const;

	~Database() = default;
}


#endif // !DATABASE_H_

