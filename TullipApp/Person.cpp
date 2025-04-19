#include "Person.h"

// Person class implementation
// Constructor implementations
Person::Person(const std::string& name, const std::string& surname) : name_(name), surname_(surname) {}
Person::Person(std::string&& name, std::string&& surname) : name_(std::move(name)), surname_(std::move(surname)) {}





