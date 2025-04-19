#include "Person.h"

// Person class implementation
// Constructor implementations
Person::Person(const std::string& name, const std::string& surname) : name_(name), surname_(surname) {}
Person::Person(std::string&& name, std::string&& surname) : name_(std::move(name)), surname_(std::move(surname)) {}

// Parent class implementation
// Constructor implementations
Parent::Parent(const std::string& name, const std::string& surname, const std::string& email) : Person(name, surname), email_(email) {}
Parent::Parent(std::string&& name, std::string&& surname, std::string&& email) : Person(std::move(name), std::move(surname)), email_(std::move(email)) {}

// Child class implementation
// Constructor implementations
Child::Child(const std::string& name, const std::string& surname, const Date& birth_date, Parent* dad, Parent* mom) 
   : Person(name, surname), birth_date_(birth_date), dad_(dad), mom_(mom) {}

Child::Child(std::string&& name, std::string&& surname, Date&& birth_date, Parent* dad, Parent* mom) 
   : Person(std::move(name), std::move(surname)), birth_date_(std::move(birth_date)), dad_(dad), mom_(mom) {}
