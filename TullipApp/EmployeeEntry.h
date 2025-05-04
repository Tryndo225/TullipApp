/**
 * @file EmployeeEntry.h
 * @brief Defines the ` EmployeeEntry` class for managing the graphical representation of a employee in the GUI.
 * @details This file contains the declaration of the ` EmployeeEntry` class, which provides a Qt-based widget
 *          for displaying and interacting with a `Employee` object in the GUI.
 */
#ifndef EMPLOYEEENTRY_H_
#define EMPLOYEEENTRY_H_

#include <QWidget>
#include "ui_EmployeeEntry.h"
#include "Person.h"

/**
 * @class EmployeeEntry
 * @brief Represents a GUI widget for an employee entry.
 * @details The `EmployeeEntry` class provides a graphical representation of an `Employee` object in the GUI.
 *          It allows for displaying and interacting with the details of an employee.
 * @see Employee
 */
class EmployeeEntry : public QWidget
{
	Q_OBJECT
signals:
	/**
	* @brief Signal emitted when a employee edit is requested.
	* @details This signal is emitted when the user clicks on a employee's edit button and requests to edit the employee's details.
	* @param employee A pointer to the `Employee` object to be edited.
	*/
	void editRequested(Employee* employee);

	/**
	 * @brief Signal emitted when a employee removal is requested.
	 * @details This signal is emitted when the user clicks on a employee's remove button and requests to remove the employee from the database.
	 * @param employee A pointer to the `Employee` object to be removed.
	 */
	void removeRequested(Employee* employee);

public:
	/**
	 * @brief Constructs an `EmployeeEntry` widget.
	 * @param parent A pointer to the parent widget.
	 * @param employee A pointer to the `Employee` object represented by this widget.
	 */
	EmployeeEntry(QWidget* parent, Employee* employee);

	/**
	 * @brief Function called when the email label is clicked.
	 * @details Resonsible for copying the email to the clipboard.
	 */
	void email_clicked();

	/**
	 * @brief Function called when the phone label is clicked.
	 * @details Responsible for copying the phone number to the clipboard.
	 */
	void phone_clicked();

	~EmployeeEntry();

private:
	Ui::EmployeeEntryClass ui; ///< The user interface for the employee entry widget.
	Employee* employee_; ///< Pointer to the Employee object represented by this widget.

	/**
	 * @brief Sets up the employee entry widget.
	 * @details Initializes the widget with the employee's details and connects signals to slots.
	 */
	void setup_employee_entry();
};

#endif // EMPLOYEEENTRY_H_
