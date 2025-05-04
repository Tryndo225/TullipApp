/**
 * @file EmployeeDialog.h
 * @brief Defines the EmployeeDialog class for editing employee information.
 * @details This file contains the definition of the EmployeeDialog class, which is used to edit employee information.
 */

#ifndef EMPLOYEEDIALOG_H_
#define EMPLOYEEDIALOG_H_

#include <QDialog>
#include "ui_EmployeeDialog.h"
#include "Person.h"

/**
 * @class EmployeeDialog
 * @brief Dialog for managing employee information.
 * @details The EmployeeDialog class provides a user interface for editing employee information such as name, surname,
 *          email, phone number, and hours worked. It inherits from QDialog and uses the Qt framework for GUI elements.
 */
class EmployeeDialog : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief Constructs an EmployeeDialog object and sets it up.
	 * @details This constructor initializes the dialog and sets it's fields to reflect employee properties.
	 * @param parent The parent widget.
	 * @param employee Pointer to the Employee object to be edited.
	 */
	EmployeeDialog(QWidget* parent, Employee* employee);

	/**
	 * @brief Accepts the dialog and updates the employee information.
	 * @details This function is called when the user clicks the "OK" button in the dialog.
	 */
	void accept() override;

	/**
	 * @brief Destructors an EmployeeDialog object.
	 */
	~EmployeeDialog();

private:
	Ui::EmployeeDialogClass ui; ///< The user interface for the employee dialog.
	Employee* employee_; ///< Pointer to the Employee object being edited.
};

#endif // EMPLOYEEDIALOG_H_
