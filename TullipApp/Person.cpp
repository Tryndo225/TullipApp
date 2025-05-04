#include "Person.h"

// Person class implementation
// Constructor implementations
Person::Person(const std::string& name, const std::string& surname) : name_(name), surname_(surname) {}
Person::Person(std::string&& name, std::string&& surname) : name_(std::move(name)), surname_(std::move(surname)) {}

std::ostream& operator<<(std::ostream& stream, const Person& person)
{
	stream << person.name_ << "," << person.surname_ << std::endl;
	return stream;
}

// Parent class implementation
// Constructor implementations
Parent::Parent(const std::string& name, const std::string& surname, bool is_mother, const std::string& email) : Person(name, surname), is_mother_(is_mother), email_(email), children_(std::vector<Child*>()) {}
Parent::Parent(std::string&& name, std::string&& surname, bool is_mother, std::string&& email) : Person(std::move(name), std::move(surname)), is_mother_(is_mother), email_(std::move(email)), children_(std::vector<Child*>()) {}

std::ostream& operator<<(std::ostream& stream, const Parent& parent)
{
	stream << parent.name_ << "," << parent.surname_ << "," << (parent.is_mother_ ? "Mother" : "Father") << "," << parent.email_.get_email() << ",{";
	for (auto it = parent.children_.begin(); it != parent.children_.end(); ++it) {
		stream << (*it)->get_name() << " " << (*it)->get_surname();
		if (std::next(it) != parent.children_.end()) {
			stream << ",";
		}
	}
	stream << "}" << std::endl;
	return stream;
}

// Child class implementation
// Constructor implementations
Child::Child(const std::string& name, const std::string& surname, const Date& birth_date, Parent* dad, Parent* mom)
	: Person(name, surname), birth_date_(birth_date), dad_(dad), mom_(mom) {
}

Child::Child(std::string&& name, std::string&& surname, Date&& birth_date, Parent* dad, Parent* mom)
	: Person(std::move(name), std::move(surname)), birth_date_(std::move(birth_date)), dad_(dad), mom_(mom) {
}

std::ostream& operator<<(std::ostream& stream, const Child& child)
{
	stream << child.name_ << "," << child.surname_ << "," << child.birth_date_.get_date_string() << ","
		<< (child.dad_ ? child.dad_->get_name() + " " + child.dad_->get_surname() : "No Father") << ","
		<< (child.mom_ ? child.mom_->get_name() + " " + child.mom_->get_surname() : "No Mother") << std::endl;
	return stream;
}

// Employee class implementation
// Constructor implementations
Employee::Employee(const std::string& name, const std::string& surname, const std::string& email, const std::string& phone)
	: Person(name, surname), email_(email), phone_(phone), hours_worked_(0) {
}

Employee::Employee(std::string&& name, std::string&& surname, std::string&& email, std::string&& phone)
	: Person(std::move(name), std::move(surname)), email_(std::move(email_)), phone_(std::move(phone)), hours_worked_(0) {
}

std::ostream& operator<<(std::ostream& stream, const Employee& employee)
{
	stream << employee.name_ << "," << employee.surname_ << "," << employee.email_.get_email() << ","
		<< employee.phone_.get_phone() << std::endl;
	return stream;
}