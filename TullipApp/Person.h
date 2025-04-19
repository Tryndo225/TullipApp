#ifndef PERSON_H_  
#define PERSON_H_  
#include <string>
#include <utility>
#include <vector>

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

class Child : public Person
{
};

#endif