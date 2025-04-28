#ifndef DATABASE_H_
#define DATABASE_H_

#include <vector>
#include <map>
#include <string>
#include <fstream>
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

	std::multimap<std::string, Employee*> employee_by_name;
	std::multimap<std::string, Employee*> employee_by_surname;

	std::multimap<DateTime, Lesson*> lesson_by_datetime;

	void import_Lessons_from_csv_file(std::istream& stream = std::cin);
	void import_Parents_from_csv_file(std::istream& stream = std::cin);
	void import_Children_from_csv_file(std::istream& stream = std::cin);
	void import_Employees_from_csv_file(std::istream& stream = std::cin);

	void export_Lessons_to_csv_file(std::ostream& stream = std::cout) const;
	void export_Parents_to_csv_file(std::ostream& stream = std::cout) const;
	void export_Children_to_csv_file(std::ostream& stream = std::cout) const;
	void export_Employees_to_csv_file(std::ostream& stream = std::cout) const;

public:
	Database() = default;

	Database(const Database& db) = default;
	Database(Database&& db) noexcept = default;

	Database& operator=(const Database& db) = default;
	Database& operator=(Database&& db) noexcept = default;

	void add_lesson(const Lesson& lesson);
	void remove_lesson(const Lesson* lesson);

	std::multimap<DateTime, Lesson*>& sort_lessons_by_datetime();

	std::vector<Lesson*> filter_lesson_by_day(const std::string& day, std::optional<std::vector<Lesson*>> lessons = std::nullopt) const;
	std::vector<Lesson*> filter_lesson_by_address(const std::string& address, std::optional<std::vector<Lesson*>> lessons = std::nullopt) const;
	std::vector<Lesson*> filter_lesson_by_child_name(const std::string& name, std::optional<std::vector<Lesson*>> lessons = std::nullopt) const;
	std::vector<Lesson*> filter_lesson_by_child_surname(const std::string& surname, std::optional<std::vector<Lesson*>> lessons = std::nullopt) const;

	void add_parent(const Parent& parent);
	void remove_parent(const Parent* parent);

	std::multimap<std::string, Parent*> sort_parents_by_name();
	std::multimap<std::string, Parent*> sort_parents_by_surname();

	std::vector<Parent*> filter_parent_by_name(const std::string& name, std::optional<std::vector<Parent*>> parents = std::nullopt) const;
	std::vector<Parent*> filter_parent_by_surname(const std::string& surname, std::optional<std::vector<Parent*>> parents = std::nullopt) const;
	std::vector<Parent*> filter_parent_by_email(const std::string& email, std::optional<std::vector<Parent*>> parents = std::nullopt) const;

	void add_child(const Child& child);
	void remove_child(const Child* child);

	std::multimap<std::string, Child*> sort_children_by_name();
	std::multimap<std::string, Child*> sort_children_by_surname();
	std::multimap<Date, Child*> sort_children_by_birth_date();

	std::vector<Child*> filter_child_by_name(const std::string& name, std::optional<std::vector<Child*>> parents = std::nullopt) const;
	std::vector<Child*> filter_child_by_surname(const std::string& surname, std::optional<std::vector<Child*>> parents = std::nullopt) const;
	std::vector<Child*> filter_child_by_age(const int age, std::optional<std::vector<Child*>> parents = std::nullopt) const;
	std::vector<Child*> filter_child_by_parent_name(const std::string& parent_name, std::optional<std::vector<Child*>> children = std::nullopt) const;
	std::vector<Child*> filter_child_by_parent_surname(const std::string& parent_surname, std::optional <std::vector<Child*>> children = std::nullopt) const;

	void add_employee(const Employee& employee);
	void remove_employee(const Employee* employee);

	std::multimap<std::string, Employee*> sort_employees_by_name();
	std::multimap<std::string, Employee*> sort_employees_by_surname();

	std::vector<Employee*> filter_employee_by_name(const std::string& name, std::optional<std::vector<Employee*>> employees) const;
	std::vector<Employee*> filter_employee_by_surname(const std::string& surname, std::optional<std::vector<Employee*>> employees) const;

	void import_from_stream(std::istream& stream = std::cin);
	void import_from_csv_file(const std::string& filename);
	void export_to_stream(std::ostream& stream = std::cout) const;
	void export_to_csv_file(const std::string& filename) const;

	void clear();
	~Database() = default;
};

#endif // !DATABASE_H_