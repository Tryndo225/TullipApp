#ifndef PERSON_H_
#define PERSON_H_
#include <string>
#include <utility>
#include <vector>
#include <optional>
#include "DateTime.h"
#include "Data_Helper_Types.h"
#include "Helper_Functions.h"

class Person
{
protected:
	std::string name_;
	std::string surname_;

public:
	Person() = default;
	Person(const std::string& name, const std::string& surname);
	Person(std::string&& name, std::string&& surname);

	Person(const Person& person) = default;
	Person(Person&& person) noexcept = default;

	Person& operator=(const Person& person) = default;
	Person& operator=(Person&& person) noexcept = default;

	inline const std::string& get_name() const { return name_; }
	inline void set_name(std::string&& name) { name_ = std::forward<std::string>(name); }

	inline const std::string& get_surname() const { return surname_; }
	inline void set_surname(std::string&& surname) { surname_ = std::forward<std::string>(surname); }

	~Person() = default;
};
class Parent; // Forward declaration

class Child : public Person
{
protected:
	Date birth_date_;
	Parent* dad_;
	Parent* mom_;

public:
	Child() = default;
	Child(const std::string& name, const std::string& surname, const Date& birth_date, Parent* dad = nullptr, Parent* mom = nullptr);
	Child(std::string&& name, std::string&& surname, Date&& birth_date, Parent* dad = nullptr, Parent* mom = nullptr);

	Child(const Child& child) = default;
	Child(Child&& child) noexcept = default;

	Child& operator=(const Child& child) = default;
	Child& operator=(Child&& child) noexcept = default;

	inline const Date& get_birth_date() const { return birth_date_; }
	inline void set_birth_date(Date&& birth_date) { birth_date_ = std::forward<Date>(birth_date); }

	inline Parent* get_dad() const { return dad_; }
	inline void set_dad(Parent* dad) { dad_ = dad; }

	inline Parent* get_mom() const { return mom_; }
	inline void set_mom(Parent* mom) { mom_ = mom; }

	~Child() = default;
};

class Parent : public Person
{
protected:
	Email email_;
	std::vector<Child*> children_;

public:
	Parent() = default;
	Parent(const std::string& name, const std::string& surname, const std::string& email = "");
	Parent(std::string&& name, std::string&& surname, std::string&& email = "");

	Parent(const Parent& parent) = default;
	Parent(Parent&& parent) noexcept = default;

	Parent& operator=(const Parent& parent) = default;
	Parent& operator=(Parent&& parent) noexcept = default;

	inline const Email& get_email() const { return email_; }
	inline void set_email(std::string&& email) { email_ = Email(std::forward<std::string>(email)); }

	inline const std::vector<Child*>& get_children() const { return children_; }
	inline void add_child(Child* child) { children_.push_back(child); }
	inline void remove_child(Child* child) { remove_all(children_, child); }

	~Parent() = default;
};

class Employee : public Person
{
protected:
	Email email_;
	Phone phone_;
	int hours_worked_;

public:
	Employee() = default;
	Employee(const std::string& name, const std::string& surname, const std::string& email = "", const std::string& phone = "");
	Employee(std::string&& name, std::string&& surname, std::string&& email = "", std::string&& phone = "");

	Employee(const Employee& employee) = default;
	Employee(Employee&& employee) noexcept = default;

	Employee& operator=(const Employee& employee) = default;
	Employee& operator=(Employee&& employee) noexcept = default;

	inline const Email& get_email() const { return email_; }
	inline void set_email(std::string&& email) { email_ = Email(std::forward<std::string>(email)); }

	inline const Phone& get_phone() const { return phone_; }
	inline void set_phone(std::string&& phone) { phone_ = Phone(std::forward<std::string>(phone)); }

	inline int get_hours_worked() const { return hours_worked_; }
	inline void set_hours_worked(int hours_worked) { hours_worked_ = hours_worked; }

	~Employee() = default;
};

#endif