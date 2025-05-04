#ifndef EMPLOYEEENTRY_H_
#define EMPLOYEEENTRY_H_

#include <QWidget>
#include "ui_EmployeeEntry.h"
#include "Person.h"

class EmployeeEntry : public QWidget
{
	Q_OBJECT
signals:
	void editRequested(Employee* employee);
	void removeRequested(Employee* employee);

public:
	EmployeeEntry(QWidget* parent, Employee* employee);

	void email_clicked();
	void phone_clicked();

	~EmployeeEntry();

private:
	Ui::EmployeeEntryClass ui; ///< The user interface for the employee entry widget.
	Employee* employee_; ///< Pointer to the Employee object represented by this widget.

	void setup_employee_entry();
};

#endif // EMPLOYEEENTRY_H_
