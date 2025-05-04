#pragma once

#include <QDialog>
#include "ui_EmployeeDialog.h"
#include "Person.h"

class EmployeeDialog : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief Constructs an EmployeeDialog object.
	 * @param parent The parent widget. Defaults to nullptr.
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
