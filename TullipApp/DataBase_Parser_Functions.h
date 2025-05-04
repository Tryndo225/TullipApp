#ifndef DATABASE_PARSER_FUNCTIONS_H_
#define DATABASE_PARSER_FUNCTIONS_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "DataBase.h"
#include "Lesson.h"
#include "Person.h"

static class CSV_Parser
{
public:
	/**
	 * @brief Parses a lesson from a CSV line.
	 * @param line The CSV line containing lesson data.
	 * @param database The database to which the lesson will be added.
	 */
	static void parse_lesson(std::string& line, Database& database);

	/**
	 * @brief Parses a child from a CSV line.
	 * @param line The CSV line containing child data.
	 * @param database The database to which the child will be added.
	 */
	static void parse_child(const std::string& line, Database& database);

	/**
	 * @brief Parses a parent from a CSV line.
	 * @param line The CSV line containing parent data.
	 * @param database The database to which the parent will be added.
	 */
	static void parse_parent(const std::string& line, Database& database);

	/**
	 * @brief Parses an employee from a CSV line.
	 * @param line The CSV line containing employee data.
	 * @param database The database to which the employee will be added.
	 */
	static void parse_employee(const std::string& line, Database& database);

private:
	/**
	 * @brief Parses lesson's employees from a CSV line.
	 * @param line The CSV line containing lesson's employees data.
	 * @param database The database from which it searches employees.
	 */
	static void parse_lesson_employees(std::string& employees_str, Lesson& lesson, Database& database);

	/**
	 * @brief Parses lesson's children from a CSV line.
	 * @param line The CSV line containing lesson's children data.
	 * @param database The database from which it searches children.
	 */
	static void parse_lesson_children(std::string& children_str, Lesson& lesson, Database& database);

	/**
	 * @brief Parses lesson's attendance from a CSV line.
	 * @param line The CSV line containing lesson's attendance data.
	 * @param database The database from which it searches children.
	 */
	static void parse_lesson_attendance(std::string& attendance_str, Lesson& lesson, Database& database);
}

#endif // !DATABASE_PARSER_FUNCTIONS_H_
