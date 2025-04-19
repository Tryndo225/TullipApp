#ifndef PERSON_H_  
#define PERSON_H_  
#include <string>
#include <utility>
#include <vector>
#include "DateTime.h"
#include "Person_Helper_Types.h"

class Person
{
protected:
	std::string name_;
	std::string surname_;

public:
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
	Child(const std::string& name, const std::string& surname, const Date& birth_date, Parent* dad, Parent* mom);
	Child(std::string&& name, std::string&& surname, Date&& birth_date, Parent* dad, Parent* mom);

	Child(const Child& child) = default;
	Child(Child&& child) noexcept = default;

	Child& operator=(const Child& child) = default;
	Child& operator=(Child&& child) noexcept = default;

	inline const Date& get_birth_date() const { return birth_date_; }
	inline void set_birth_date(Date&& birth_date) { birth_date_ = std::forward<Date>(birth_date); }
	~Child() = default;
};

class Parent : public Person
{
protected:
	Email email_;
	std::vector<Child> children_;

public:
	Parent(const std::string& name, const std::string& surname, const std::string& email);
	Parent(std::string&& name, std::string&& surname, std::string&& email);

	Parent(const Parent& parent) = default;
	Parent(Parent&& parent) noexcept = default;

	Parent& operator=(const Parent& parent) = default;
	Parent& operator=(Parent&& parent) noexcept = default;

	inline const Email& get_email() const { return email_; }
	inline void set_email(std::string&& email) { email_ = Email(std::forward<std::string>(email)); }
	inline const std::vector<Child>& get_children() const { return children_; }
	inline void add_child(Child&& child) { children_.push_back(std::move(child)); }
	~Parent() = default;
};


#endif