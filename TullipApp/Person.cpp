#include "Person.h"

// Person class implementation
// Constructor implementations
Person::Person(const std::string& name, const std::string& surname) : name_(name), surname_(surname) {}
Person::Person(std::string&& name, std::string&& surname) : name_(std::move(name)), surname_(std::move(surname)) {}

// Parent class implementation
// Constructor implementations
Parent::Parent(const std::string& name, const std::string& surname, const std::string& email) : Person(name, surname), email_(email), children_(std::vector<Child*>()) {}
Parent::Parent(std::string&& name, std::string&& surname, std::string&& email) : Person(std::move(name), std::move(surname)), email_(std::move(email)), children_(std::vector<Child*>()) {}

// Child class implementation
// Constructor implementations
Child::Child(const std::string& name, const std::string& surname, const Date& birth_date, Parent* dad, Parent* mom)
	: Person(name, surname), birth_date_(birth_date), dad_(dad), mom_(mom) {
}
Child::Child(std::string&& name, std::string&& surname, Date&& birth_date, Parent* dad, Parent* mom)
	: Person(std::move(name), std::move(surname)), birth_date_(std::move(birth_date)), dad_(dad), mom_(mom) {
}

// Employee class implementation
// Constructor implementations
Employee::Employee(const std::string& name, const std::string& surname, const std::string& email, const std::string& phone)
	: Person(name, surname), email_(email), phone_(phone), hours_worked_(0) {
}

Employee::Employee(std::string&& name, std::string&& surname, std::string&& email, std::string&& phone)
	: Person(std::move(name), std::move(surname)), email_(std::move(email_)), phone_(std::move(phone)), hours_worked_(0) {
}