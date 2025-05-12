/**
 * @file Person.h
 * @brief Defines the Person class and its derived classes: Child, Parent, and Employee.
 * @details This file contains the declarations of the Person class, which serves as a base class,
 *          and its derived classes that extend its functionality for specific use cases.
*/

#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <optional>
#include "DateTime.h"
#include "Data_Helper_Types.h"
#include "Helper_Functions.h"

/**
 * @class Person
 * @brief Represents a generic person.
 * @details The Person class serves as a base class for other types of people, such as parents, children, and employees.
 *          It provides basic attributes like name and surname, along with getter and setter methods.
*/
class Person
{
protected:
	std::string name_;   ///< The first name of the person.
	std::string surname_; ///< The last name of the person.

public:
	/**
	 * @brief Default constructor.
	 * @details Initializes a Person object with default values.
	*/
	Person() = default;

	/**
	 * @brief Constructs a Person with the given name and surname.
	 * @details Initializes a Person object with the specified name and surname.
	 * @param name The first name of the person.
	 * @param surname The last name of the person.
	*/
	Person(const std::string& name, const std::string& surname);

	/**
	 * @brief Constructs a Person with the given name and surname (rvalue).
	 * @details Initializes a Person object with the specified name and surname (rvalue).
	 * @param name The first name of the person (rvalue).
	 * @param surname The last name of the person (rvalue).
	 */
	Person(std::string&& name, std::string&& surname);

	// Rule of 5
	Person(const Person& person) = default;
	Person(Person&& person) noexcept = default;
	Person& operator=(const Person& person) = default;
	Person& operator=(Person&& person) noexcept = default;

	/**
	 * @brief Equality operator.
	 * @details Compares two Person objects for equality based on their name and surname.
	 * @param person The Person object to compare with.
	 * @retval true If the name and surname are equal.
	 * @retval false Otherwise.
	 */
	inline bool operator==(const Person& person) const { return name_ == person.name_ && surname_ == person.surname_; }

	/**
	 * @brief Inequality operator.
	 * @details Compares two Person objects for inequality.
	 * @param person The Person object to compare with.
	 * @retval true If the name or surname are not equal.
	 * @retval false Otherwise.
	 */
	inline bool operator!=(const Person& person) const { return !(*this == person); }

	/**
	 * @brief Gets the first name of the person.
	 * @return A constant reference to the first name.
	 */
	inline const std::string& get_name() const { return name_; }

	/**
	 * @brief Sets the first name of the person.
	 * @param name The new first name (rvalue).
	 */
	inline void set_name(std::string&& name) { name_ = std::forward<std::string>(name); }

	/**
	 * @brief Gets the last name of the person.
	 * @return A constant reference to the last name.
	 */
	inline const std::string& get_surname() const { return surname_; }

	/**
	 * @brief Sets the last name of the person.
	 * @param surname The new last name (rvalue).
	 */
	inline void set_surname(std::string&& surname) { surname_ = std::forward<std::string>(surname); }

	/**
	 * @brief Destructor.
	 * @details Cleans up resources used by the Person object.
	 */
	virtual ~Person() = default;

	/**
	 * @brief Outputs the Person object to a stream.
	 * @param stream The output stream.
	 * @param person The Person object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Person& person);
};

class Parent; // Forward declaration

/**
 * @class Child
 * @brief Represents a child.
 * @details The Child class extends the Person class and adds attributes like birth date and references to parents.
 * @see Person
 */
class Child : public Person
{
protected:
	Date birth_date_; ///< The birth date of the child.
	Parent* dad_;     ///< Pointer to the father (optional).
	Parent* mom_;     ///< Pointer to the mother (optional).

public:
	/**
	 * @brief Default constructor.
	 * @details Initializes a Child object with default values.
	 */
	Child() = default;

	/**
	 * @brief Constructs a Child with the given attributes.
	 * @param name The first name of the child.
	 * @param surname The last name of the child.
	 * @param birth_date The birth date of the child.
	 * @param dad Pointer to the father (optional).
	 * @param mom Pointer to the mother (optional).
	 */
	Child(const std::string& name, const std::string& surname, const Date& birth_date, Parent* dad = nullptr, Parent* mom = nullptr);

	/**
	 * @brief Constructs a Child with the given attributes (rvalue).
	 * @param name The first name of the child (rvalue).
	 * @param surname The last name of the child (rvalue).
	 * @param birth_date The birth date of the child (rvalue).
	 * @param dad Pointer to the father (optional).
	 * @param mom Pointer to the mother (optional).
	 */
	Child(std::string&& name, std::string&& surname, Date&& birth_date, Parent* dad = nullptr, Parent* mom = nullptr);

	// Rule of 5
	Child(const Child& child) = default;
	Child(Child&& child) noexcept = default;
	Child& operator=(const Child& child) = default;
	Child& operator=(Child&& child) noexcept = default;

	/**
	 * @brief Equality operator.
	 * @details Compares two Child objects for equality based on their attributes.
	 * @param child The Child object to compare with.
	 * @retval true If all attributes are equal.
	 * @retval false Otherwise.
	 */
	inline bool operator==(const Child& child) const { return Person::operator==(child) && birth_date_ == child.birth_date_; }

	/**
	 * @brief Inequality operator.
	 * @details Compares two Child objects for inequality.
	 * @param child The Child object to compare with.
	 * @retval true If any attribute is not equal.
	 * @retval false Otherwise.
	 */
	inline bool operator!=(const Child& child) const { return !(*this == child); }

	/**
	 * @brief Gets the age of the child.
	 * @return The age of the child in years.
	 */
	inline int get_age() const { return (Date::get_current_date() - birth_date_).get_year(); }

	/**
	 * @brief Gets the birth date of the child.
	 * @return A constant reference to the birth date.
	 */
	inline const Date& get_birth_date() const { return birth_date_; }

	/**
	 * @brief Sets the birth date of the child.
	 * @param birth_date The new birth date (rvalue).
	 */
	inline void set_birth_date(Date&& birth_date) { birth_date_ = std::forward<Date>(birth_date); }

	/**
	 * @brief Gets the father of the child.
	 * @return A pointer to the father.
	 */
	inline Parent* get_dad() const { return dad_; }

	/**
	 * @brief Sets the father of the child.
	 * @param dad A pointer to the new father.
	 */
	inline void set_dad(Parent* dad) { dad_ = dad; }

	/**
	 * @brief Gets the mother of the child.
	 * @return A pointer to the mother.
	 */
	inline Parent* get_mom() const { return mom_; }

	/**
	 * @brief Sets the mother of the child.
	 * @param mom A pointer to the new mother.
	 */
	inline void set_mom(Parent* mom) { mom_ = mom; }

	/**
	 * @brief Destructor.
	 * @details Cleans up resources used by the Child object.
	 */
	~Child() = default;

	/**
	 * @brief Outputs the Child object to a stream.
	 * @param stream The output stream.
	 * @param child The Child object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Child& child);
};

/**
 * @class Parent
 * @brief Represents a parent.
 * @details The Parent class extends the Person class and adds attributes like email and a list of children.
 * @see Person
 */
class Parent : public Person
{
protected:
	bool is_mother_;            ///< Indicates if the parent is a mother (true) or a father (false).
	Email email_;                 ///< The email address of the parent.
	std::vector<Child*> children_; ///< A list of pointers to the parent's children.

public:
	/**
	 * @brief Default constructor.
	 * @details Initializes a Parent object with default values.
	 */
	Parent() = default;

	/**
	 * @brief Constructs a Parent with the given attributes.
	 * @param name The first name of the parent.
	 * @param surname The last name of the parent.
	 * @param email The email address of the parent (optional).
	 */
	Parent(const std::string& name, const std::string& surname, bool is_mother, const std::string& email = "");

	/**
	 * @brief Constructs a Parent with the given attributes (rvalue).
	 * @param name The first name of the parent (rvalue).
	 * @param surname The last name of the parent (rvalue).
	 * @param email The email address of the parent (optional, rvalue).
	 */
	Parent(std::string&& name, std::string&& surname, bool is_mother, std::string&& email = "");

	// Rule of 5
	Parent(const Parent& parent) = default;
	Parent(Parent&& parent) noexcept = default;
	Parent& operator=(const Parent& parent) = default;
	Parent& operator=(Parent&& parent) noexcept = default;

	/**
	 * @brief Equality operator.
	 * @details Compares two Parent objects for equality based on their attributes.
	 * @param parent The Parent object to compare with.
	 * @retval true If all attributes are equal.
	 * @retval false Otherwise.
	 */
	inline bool operator==(const Parent& parent) const { return Person::operator==(parent) && email_ == parent.email_; }

	/**
	 * @brief Inequality operator.
	 * @details Compares two Parent objects for inequality.
	 * @param parent The Parent object to compare with.
	 * @retval true If any attribute is not equal.
	 * @retval false Otherwise.
	 */
	inline bool operator!=(const Parent& parent) const { return !(*this == parent); }

	/**
	 * @brief Gets the email address of the parent.
	 * @return A constant reference to the email address.
	 */
	inline const Email& get_email() const { return email_; }

	/**
	 * @brief Sets the email address of the parent.
	 * @param email The new email address (rvalue).
	 */
	inline void set_email(std::string&& email) { email_ = Email(std::forward<std::string>(email)); }

	/**
	 * @brief Checks if the parent is a mother.
	 * @return true if the parent is a mother, false if the parent is a father.
	 */
	inline bool is_mother() const { return is_mother_; }
	/**
	 * @brief Checks if the parent is a father.
	 * @return true if the parent is a father, false if the parent is a mother.
	 */
	inline bool is_father() const { return !is_mother_; }

	/**
	 * @brief Sets the parent as a mother.
	 * @details This method sets the is_mother_ attribute to true.
	 */
	inline void set_as_mother() { is_mother_ = true; }

	/**
	 * @brief Sets the parent as a father.
	 * @details This method sets the is_mother_ attribute to false.
	 */
	inline void set_as_father() { is_mother_ = false; }

	/**
	 * @brief Gets the list of children.
	 * @return A constant reference to the list of children.
	 */
	inline const std::vector<Child*>& get_children() const { return children_; }

	/**
	 * @brief Adds a child to the parent's list of children.
	 * @param child A pointer to the child to add.
	 */
	inline void add_child(Child* child) { children_.push_back(child); }

	/**
	 * @brief Removes a child from the parent's list of children.
	 * @param child A pointer to the child to remove.
	 */
	inline void remove_child(Child* child) { remove_all(children_, child); }

	/**
	 * @brief Destructor.
	 * @details Cleans up resources used by the Parent object.
	 */
	~Parent() = default;

	/**
	 * @brief Outputs the Parent object to a stream.
	 * @param stream The output stream.
	 * @param parent The Parent object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Parent& parent);
};

/**
 * @class Employee
 * @brief Represents an employee.
 * @details The Employee class extends the Person class and adds attributes like email, phone, and hours worked.
 * @see Person
 */
class Employee : public Person
{
protected:
	Email email_;     ///< The email address of the employee.
	Phone phone_;     ///< The phone number of the employee.
	int hours_worked_; ///< The number of hours worked by the employee.

public:
	/**
	 * @brief Default constructor.
	 * @details Initializes an Employee object with default values.
	 */
	Employee() = default;

	/**
	 * @brief Constructs an Employee with the given attributes.
	 * @param name The first name of the employee.
	 * @param surname The last name of the employee.
	 * @param email The email address of the employee (optional).
	 * @param phone The phone number of the employee (optional).
	 */
	Employee(const std::string& name, const std::string& surname, const std::string& email = "", const std::string& phone = "");

	/**
	 * @brief Constructs an Employee with the given attributes (rvalue).
	 * @param name The first name of the employee (rvalue).
	 * @param surname The last name of the employee (rvalue).
	 * @param email The email address of the employee (optional, rvalue).
	 * @param phone The phone number of the employee (optional, rvalue).
	 */
	Employee(std::string&& name, std::string&& surname, std::string&& email = "", std::string&& phone = "");

	// Rule of 5
	Employee(const Employee& employee) = default;
	Employee(Employee&& employee) noexcept = default;
	Employee& operator=(const Employee& employee) = default;
	Employee& operator=(Employee&& employee) noexcept = default;

	/**
	 * @brief Gets the email address of the employee.
	 * @return A constant reference to the email address.
	 */
	inline const Email& get_email() const { return email_; }

	/**
	 * @brief Sets the email address of the employee.
	 * @param email The new email address (rvalue).
	 */
	inline void set_email(std::string&& email) { email_ = Email(std::forward<std::string>(email)); }

	/**
	 * @brief Gets the phone number of the employee.
	 * @return A constant reference to the phone number.
	 */
	inline const Phone& get_phone() const { return phone_; }

	/**
	 * @brief Sets the phone number of the employee.
	 * @param phone The new phone number (rvalue).
	 */
	inline void set_phone(std::string&& phone) { phone_ = Phone(std::forward<std::string>(phone)); }

	/**
	 * @brief Increments the number of hours worked by the employee.
	 * @details This method is used to track the number of hours worked.
	 */
	inline void add_working_hour() { ++hours_worked_; }

	/**
	 * @brief Gets the number of hours worked by the employee.
	 * @return The number of hours worked.
	 */
	inline int get_hours_worked() const { return hours_worked_; }

	/**
	 * @brief Sets the number of hours worked by the employee.
	 * @param hours_worked The new number of hours worked.
	 */
	inline void set_hours_worked(int hours_worked) { hours_worked_ = hours_worked; }

	/**
	 * @brief Resets the number of hours worked by the employee to zero.
	 * @details This method is used to clear the hours worked.
	 */
	inline void erase_hours_worked() { hours_worked_ = 0; }

	/**
	 * @brief Destructor.
	 * @details Cleans up resources used by the Employee object.
	 */
	~Employee() = default;

	/**
	 * @brief Outputs the Employee object to a stream.
	 * @param stream The output stream.
	 * @param employee The Employee object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Employee& employee);
};

#endif // !PERSON_H_
