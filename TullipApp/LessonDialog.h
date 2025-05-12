/**
 * @file LessonDialog.h
 * @brief Defines the `LessonDialog` class for managing lesson-related information.
 * @details This file contains the declaration of the `LessonDialog` class, which provides a Qt-based dialog
 *		for adding or editing lesson information in the GUI.
 */

#ifndef LESSONDIALOG_H_
#define LESSONDIALOG_H_

#include <QDialog>
#include "DataBase.h"
#include "PersonCheckBox.h"
#include "ui_LessonDialog.h"
#include "Lesson.h"
#include <vector>
#include <map>

/**
 * @class LessonDialog
 * @brief Dialog for managing lesson-related information.
 * @details The LessonDialog class provides a user interface for editing lesson information such as day, time,
 *          address, children, and employees. It inherits from QDialog and uses the Qt framework for GUI elements.
 * @see Lesson
 */
class LessonDialog : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief Constructs a `LessonDialog` object.
	 * @details This constructor initializes the dialog and sets its fields to reflect lesson properties.
	 * @param lesson A pointer to the `Lesson` object to edit or add.
	 * @param database The database to search for children and employees in.
	 * @param parent The parent widget. Defaults to `nullptr`.
	 */
	LessonDialog(Lesson* lesson, Database& database, QWidget *parent = nullptr);

	/**
	 * @brief Accepts the dialog and updates the lesson information.
	 * @details This function gathers the selected children and employees, updates the lesson properties,
	 *          and closes the dialog.
	 */
	void accept() override;

	/**
	 * @brief Destructor for `LessonDialog`.
	 * @details Cleans up resources used by the dialog.
	 */
	~LessonDialog();

private:
	Ui::LessonDialogClass ui; ///< The user interface for the lesson dialog.
	Database& database_; ///< Reference to the database being managed.
	Lesson* lesson_; ///< Pointer to the `Lesson` object being edited or added.

	/**
	 * @brief Populates the dialog with children and employees.
	 * @details This function fills the dialog with checkboxes for children based on the database.
	 * @param children A multimap of children.
	 */
	void populate_children(std::multimap<std::string, Child*> children);

	/**
	 * @brief Populates the dialog with children and employees.
	 * @details This function fills the dialog with checkboxes for children based on the database.
	 * @param children A vector of children.
	 */
	void populate_children(std::vector<Child*> children);

	/**
	 * @brief Creates a checkbox for a child.
	 * @param child A pointer to the `Child` object to create a checkbox for.
	 */
	void create_child_check_box(Child* child);

	/**
	 * @brief Populates the dialog with employees.
	 * @details This function fills the dialog with checkboxes for employees based on the database.
	 * @param employees A multimap of employees.
	 */
	void populate_employees(std::multimap<std::string, Employee*> employees);

	/**
	 * @brief Populates the dialog with employees.
	 * @details This function fills the dialog with checkboxes for employees based on the database.
	 * @param employees A vector of employees.
	 */
	void populate_employees(std::vector<Employee*> employees);

	/**
	 * @brief Clears the children checkboxes from the dialog.
	 * @details This function removes all child checkboxes from the dialog.
	 */
	void clear_children();

	/**
	 * @brief Clears the employees checkboxes from the dialog.
	 * @details This function removes all employee checkboxes from the dialog.
	 */
	void clear_employees();

	/**
	 * @brief Creates a checkbox for an employee.
	 * @param employee A pointer to the `Employee` object to create a checkbox for.
	 */
	void create_employee_check_box(Employee* employee);

	/**
	 * @brief Updates the lesson with selected children.
	 * @details This function gathers the selected children from the checkboxes and updates the lesson.
	 */
	void gather_children();

	/**
	 * @brief Updates the lesson with selected employees.
	 * @details This function gathers the selected employees from the checkboxes and updates the lesson.
	 */
	void gather_employees();

	/**
	 * @brief Searches for children based on the input in the name and surname fields.
	 * @details This function filters the children based on the name and surname entered in the dialog.
	 */
	void children_search();

	/**
	 * @brief Searches for employees based on the input in the name and surname fields.
	 * @details This function filters the employees based on the name and surname entered in the dialog.
	 */
	void employees_search();
};

#endif // LESSONDIALOG_H_
