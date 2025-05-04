/**
 * @file DataBase.h
 * @brief Defines the `Database` class for managing lessons, parents, children, and employees.
 * @details This file contains the declaration of the `Database` class, which provides functionality
 *          for storing, filtering, sorting, and exporting/importing data related to lessons, parents,
 *          children, and employees.
 */

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

 /**
  * @class Database
  * @brief Manages data related to lessons, parents, children, and employees.
  * @details The `Database` class provides methods for adding, removing, filtering, sorting, and importing/exporting
  *          data related to lessons, parents, children, and employees.
  */
class Database
{
private:
	std::vector<std::unique_ptr<Lesson>> lessons_; ///< List of lessons.
	std::vector<std::unique_ptr<Parent>> parents_; ///< List of parents.
	std::vector<std::unique_ptr<Child>> children_; ///< List of children.
	std::vector<std::unique_ptr<Employee>> employees_; ///< List of employees.

	std::multimap<std::string, Child*> child_by_name; ///< Map of children by name.
	std::multimap<std::string, Child*> child_by_surname; ///< Map of children by surname.
	std::multimap<Date, Child*> child_by_birth_date; ///< Map of children by birth date.

	std::multimap<std::string, Parent*> parent_by_name; ///< Map of parents by name.
	std::multimap<std::string, Parent*> parent_by_surname; ///< Map of parents by surname.
	std::multimap<std::string, Parent*> parent_by_email; ///< Map of parents by email.

	std::multimap<std::string, Employee*> employee_by_name; ///< Map of employees by name.
	std::multimap<std::string, Employee*> employee_by_surname; ///< Map of employees by surname.

	std::multimap<DateTime, Lesson*> lesson_by_datetime; ///< Map of lessons by date and time.

	/**
	 * @brief Imports lessons from a CSV file.
	 * @param stream The input stream to read from. Defaults to `std::cin`.
	 */
	void import_Lessons_from_csv_file(std::istream& stream = std::cin);

	/**
	 * @brief Imports parents from a CSV file.
	 * @param stream The input stream to read from. Defaults to `std::cin`.
	 */
	void import_Parents_from_csv_file(std::istream& stream = std::cin);

	/**
	 * @brief Imports children from a CSV file.
	 * @param stream The input stream to read from. Defaults to `std::cin`.
	 */
	void import_Children_from_csv_file(std::istream& stream = std::cin);

	/**
	 * @brief Imports employees from a CSV file.
	 * @param stream The input stream to read from. Defaults to `std::cin`.
	 */
	void import_Employees_from_csv_file(std::istream& stream = std::cin);

	/**
	 * @brief Exports lessons to a CSV file.
	 * @param stream The output stream to write to. Defaults to `std::cout`.
	 */
	void export_Lessons_to_csv_file(std::ostream& stream = std::cout) const;

	/**
	 * @brief Exports parents to a CSV file.
	 * @param stream The output stream to write to. Defaults to `std::cout`.
	 */
	void export_Parents_to_csv_file(std::ostream& stream = std::cout) const;

	/**
	 * @brief Exports children to a CSV file.
	 * @param stream The output stream to write to. Defaults to `std::cout`.
	 */
	void export_Children_to_csv_file(std::ostream& stream = std::cout) const;

	/**
	 * @brief Exports employees to a CSV file.
	 * @param stream The output stream to write to. Defaults to `std::cout`.
	 */
	void export_Employees_to_csv_file(std::ostream& stream = std::cout) const;

	/**
	 * @brief Removes an entry from a multimap.
	 * @tparam Key The type of the key in the multimap.
	 * @tparam Value The type of the value in the multimap.
	 * @param map The multimap to remove from.
	 * @param key The key to search for.
	 * @param value The value to remove.
	 */
	template <typename Key, typename Value>
	void remove_from_map(std::multimap<Key, Value*>& map, const Key& key, const Value* value);

	/**
	 * @brief Searches for closest match of name + surname to reference string in a vector of pointers.
	 * @tparam T The type of the elements in the vector (must be derived from person).
	 * @param vector The vector to search in.
	 * @param reference The reference string to search for.
	 */
	template <typename T>
	void search_lavenstein_name_surname(std::vector<T*>& vector, const std::string& reference_name, const std::string& reference_surname) const;

public:
	/**
	 * @brief Default constructor.
	 */
	Database() = default;

	// Rule of 5
	Database(const Database& db) = default;
	Database(Database&& db) noexcept = default;
	Database& operator=(const Database& db) = default;
	Database& operator=(Database&& db) noexcept = default;

	/**
	 * @brief Adds a lesson to the database.
	 * @param lesson The lesson to add.
	 */
	Lesson* add_lesson(const Lesson& lesson);

	/**
	 * @brief Removes a lesson from the database.
	 * @param lesson A pointer to the lesson to remove.
	 */
	void remove_lesson(const Lesson* lesson);

	/**
	 * @brief Sorts lessons by date and time.
	 * @return A reference to the multimap of lessons sorted by date and time.
	 */
	std::multimap<DateTime, Lesson*>& sort_lessons_by_datetime();

	/**
	 * @brief Filters lessons by day.
	 * @param day The day to filter by.
	 * @param lessons An optional vector of lessons to filter. Defaults to all lessons.
	 * @return A vector of pointers to lessons matching the filter.
	 */
	std::vector<Lesson*> filter_lesson_by_day(const std::string& day, std::optional<std::vector<Lesson*>> lessons = std::nullopt) const;

	/**
	 * @brief Filters lessons by address.
	 * @param address The address to filter by.
	 * @param lessons An optional vector of lessons to filter. Defaults to all lessons.
	 * @return A vector of pointers to lessons matching the filter.
	 */
	std::vector<Lesson*> filter_lesson_by_address(const std::string& address, std::optional<std::vector<Lesson*>> lessons = std::nullopt) const;

	/**
	 * @brief Filters lessons by a child's name.
	 * @param name The child's name to filter by.
	 * @param lessons An optional vector of lessons to filter. Defaults to all lessons.
	 * @return A vector of pointers to lessons matching the filter.
	 */
	std::vector<Lesson*> filter_lesson_by_child_name(const std::string& name, std::optional<std::vector<Lesson*>> lessons = std::nullopt) const;

	/**
	 * @brief Filters lessons by a child's surname.
	 * @param surname The child's surname to filter by.
	 * @param lessons An optional vector of lessons to filter. Defaults to all lessons.
	 * @return A vector of pointers to lessons matching the filter.
	 */
	std::vector<Lesson*> filter_lesson_by_child_surname(const std::string& surname, std::optional<std::vector<Lesson*>> lessons = std::nullopt) const;

	/**
	 * @brief Adds a parent to the database.
	 * @param parent The parent to add.
	 */
	Parent* add_parent(const Parent& parent);

	/**
	 * @brief Removes a parent's information from the maps.
	 * @param parent A pointer to the parent to update.
	 */
	void update_parent_start(Parent* parent);

	/**
	 * @brief Adds a parent's information to the maps.
	 * @param parent A pointer to the parent to update.
	 */
	void update_parent_end(Parent* parent);

	/**
	 * @brief Gets a parent by name and surname.
	 * @param name_surname The name and surname of the parent to find.
	 * @return A pointer to the parent if found, otherwise `nullptr`.
	 */
	Parent* get_parent_by_name_surname(const std::string& name_surname) const;

	/**
	 * @brief Removes a parent from the database.
	 * @param parent A pointer to the parent to remove.
	 */
	void remove_parent(const Parent* parent);

	/**
	 * @brief Searches for parents by a reference string based on lavenstein distance from their name + surname.
	 * @param reference The reference string to search for.
	 * @return A vector of pointers to parents matching the reference.
	 */
	std::vector<Parent*> search_parents(const std::string& reference_name, const std::string& reference_surname) const;

	/**
	 * @brief Sorts parents by name.
	 * @return A multimap of parents sorted by name.
	 */
	std::multimap<std::string, Parent*> sort_parents_by_name();

	/**
	 * @brief Sorts parents by surname.
	 * @return A multimap of parents sorted by surname.
	 */
	std::multimap<std::string, Parent*> sort_parents_by_surname();

	/**
	 * @brief Sorts parents by email.
	 * @return A multimap of parents sorted by email.
	 */
	std::multimap<std::string, Parent*> sort_parents_by_email();

	/**
	 * @brief Filters parents by name.
	 * @param name The name to filter by.
	 * @param parents An optional vector of parents to filter. Defaults to all parents.
	 * @return A vector of pointers to parents matching the filter.
	 */
	std::vector<Parent*> filter_parent_by_name(const std::string& name, std::optional<std::vector<Parent*>> parents = std::nullopt) const;

	/**
	 * @brief Filters parents by surname.
	 * @param surname The surname to filter by.
	 * @param parents An optional vector of parents to filter. Defaults to all parents.
	 * @return A vector of pointers to parents matching the filter.
	 */
	std::vector<Parent*> filter_parent_by_surname(const std::string& surname, std::optional<std::vector<Parent*>> parents = std::nullopt) const;

	/**
	 * @brief Filters parents by email.
	 * @param email The email to filter by.
	 * @param parents An optional vector of parents to filter. Defaults to all parents.
	 * @return A vector of pointers to parents matching the filter.
	 */
	std::vector<Parent*> filter_parent_by_email(const std::string& email, std::optional<std::vector<Parent*>> parents = std::nullopt) const;

	/**
	 * @brief Adds a child to the database.
	 * @param child The child to add.
	 */
	Child* add_child(const Child& child);

	/**
	 * @brief Removes a child's information from the maps.
	 * @param child A pointer to the child to update.
	 */
	void update_child_start(Child* child);

	/**
	 * @brief Adds a child's information to the maps.
	 * @param child A pointer to the child to update.
	 */
	void update_child_end(Child* child);

	/**
	 * @brief Gets a child by name and surname.
	 * @param name_surname The name and surname of the child to find.
	 * @return A pointer to the child if found, otherwise `nullptr`.
	 */
	Child* get_child_by_name_surname(const std::string& name_surname) const;

	/**
	 * @brief Removes a child from the database.
	 * @param child A pointer to the child to remove.
	 */
	void remove_child(Child* child);

	/**
	 * @brief Searches for children by a reference string based on lavenstein distance from their name + surname.
	 * @param reference The reference string to search for.
	 * @return A vector of pointers to children matching the reference.
	 */
	std::vector<Child*> search_children(const std::string& reference_name, const std::string& reference_surname) const;

	/**
	 * @brief Sorts children by name.
	 * @return A multimap of children sorted by name.
	 */
	std::multimap<std::string, Child*> sort_children_by_name();

	/**
	 * @brief Sorts children by surname.
	 * @return A multimap of children sorted by surname.
	 */
	std::multimap<std::string, Child*> sort_children_by_surname();

	/**
	 * @brief Sorts children by birth date.
	 * @return A multimap of children sorted by birth date.
	 */
	std::multimap<Date, Child*> sort_children_by_birth_date();

	/**
	 * @brief Filters children by name.
	 * @param name The name to filter by.
	 * @param parents An optional vector of children to filter. Defaults to all children.
	 * @return A vector of pointers to children matching the filter.
	 */
	std::vector<Child*> filter_child_by_name(const std::string& name, std::optional<std::vector<Child*>> parents = std::nullopt) const;

	/**
	 * @brief Filters children by surname.
	 * @param surname The surname to filter by.
	 * @param parents An optional vector of children to filter. Defaults to all children.
	 * @return A vector of pointers to children matching the filter.
	 */
	std::vector<Child*> filter_child_by_surname(const std::string& surname, std::optional<std::vector<Child*>> parents = std::nullopt) const;

	/**
	 * @brief Filters children by age.
	 * @param age The age to filter by.
	 * @param parents An optional vector of children to filter. Defaults to all children.
	 * @return A vector of pointers to children matching the filter.
	 */
	std::vector<Child*> filter_child_by_age(const int age, std::optional<std::vector<Child*>> parents = std::nullopt) const;

	/**
	 * @brief Filters children by a parent's name.
	 * @param parent_name The parent's name to filter by.
	 * @param children An optional vector of children to filter. Defaults to all children.
	 * @return A vector of pointers to children matching the filter.
	 */
	std::vector<Child*> filter_child_by_parent_name(const std::string& parent_name, std::optional<std::vector<Child*>> children = std::nullopt) const;

	/**
	 * @brief Filters children by a parent's surname.
	 * @param parent_surname The parent's surname to filter by.
	 * @param children An optional vector of children to filter. Defaults to all children.
	 * @return A vector of pointers to children matching the filter.
	 */
	std::vector<Child*> filter_child_by_parent_surname(const std::string& parent_surname, std::optional<std::vector<Child*>> children = std::nullopt) const;

	/**
	 * @brief Adds an employee to the database.
	 * @param employee The employee to add.
	 */
	Employee* add_employee(const Employee& employee);

	/**
	 * @brief Removes an employee's information from the maps.
	 * @param employee A pointer to the employee to update.
	 */
	void update_employee_start(Employee* employee);

	/**
	 * @brief Adds an employee's information to the maps.
	 * @param employee A pointer to the employee to update.
	 */
	void update_employee_end(Employee* employee);

	/**
	 * @brief Gets an employee by name and surname.
	 * @param name_surname The name and surname of the employee to find.
	 * @return A pointer to the employee if found, otherwise `nullptr`.
	 */
	Employee* get_employee_by_name_surname(const std::string& name_surname) const;

	/**
	 * @brief Removes an employee from the database.
	 * @param employee A pointer to the employee to remove.
	 */
	void remove_employee(Employee* employee);

	/**
	 * @brief Searches for employees by a reference string based on lavenstein distance from their name + surname.
	 * @param reference The reference string to search for.
	 * @return A vector of pointers to employees matching the reference.
	 */
	std::vector<Employee*> search_employees(const std::string& reference_name, const std::string& reference_surname) const;

	/**
	 * @brief Sorts employees by name.
	 * @return A multimap of employees sorted by name.
	 */
	std::multimap<std::string, Employee*> sort_employees_by_name();

	/**
	 * @brief Sorts employees by surname.
	 * @return A multimap of employees sorted by surname.
	 */
	std::multimap<std::string, Employee*> sort_employees_by_surname();

	/**
	 * @brief Filters employees by name.
	 * @param name The name to filter by.
	 * @param employees An optional vector of employees to filter. Defaults to all employees.
	 * @return A vector of pointers to employees matching the filter.
	 */
	std::vector<Employee*> filter_employee_by_name(const std::string& name, std::optional<std::vector<Employee*>> employees = std::nullopt) const;

	/**
	 * @brief Filters employees by surname.
	 * @param surname The surname to filter by.
	 * @param employees An optional vector of employees to filter. Defaults to all employees.
	 * @return A vector of pointers to employees matching the filter.
	 */
	std::vector<Employee*> filter_employee_by_surname(const std::string& surname, std::optional<std::vector<Employee*>> employees = std::nullopt) const;

	/**
	 * @brief Imports data from a stream.
	 * @param stream The input stream to read from. Defaults to `std::cin`.
	 */
	void import_from_stream(std::istream& stream = std::cin);

	/**
	 * @brief Imports data from a CSV file.
	 * @param filename The name of the CSV file to read from.
	 */
	void import_from_csv_file(const std::string& filename);

	/**
	 * @brief Exports data to a stream.
	 * @param stream The output stream to write to. Defaults to `std::cout`.
	 */
	void export_to_stream(std::ostream& stream = std::cout) const;

	/**
	 * @brief Exports data to a CSV file.
	 * @param filename The name of the CSV file to write to.
	 */
	void export_to_csv_file(const std::string& filename) const;

	/**
	 * @brief Clears all data from the database.
	 */
	void clear();

	/**
	 * @brief Destructor.
	 */
	~Database() = default;
};

#endif // !DATABASE_H_
