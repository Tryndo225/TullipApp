#include "EmployeeDialog.h"
#include <QMessageBox>

EmployeeDialog::EmployeeDialog(QWidget* parent, Employee* employee)
	: QDialog(parent), employee_(employee)
{
	ui.setupUi(this);
	setWindowTitle("Employee Dialog");

	ui.name_edit->setText(QString::fromStdString(employee_->get_name()));
	ui.surname_edit->setText(QString::fromStdString(employee_->get_surname()));
	ui.hours_edit->setText(QString::number(employee_->get_hours_worked()));
	ui.email_edit->setText(QString::fromStdString(employee_->get_email().get_email()));
	ui.phone_edit->setText(QString::fromStdString(employee_->get_phone().get_phone()));
}

void EmployeeDialog::accept()
{
	auto name = ui.name_edit->text().toStdString();
	auto surname = ui.surname_edit->text().toStdString();
	auto hours = ui.hours_edit->text().toInt();
	auto email = ui.email_edit->text().toStdString();
	auto phone = ui.phone_edit->text().toStdString();
	if (name.empty() || surname.empty() || email.empty() || phone.empty())
	{
		QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
		return;
	}
	employee_->set_name(std::move(name));
	employee_->set_surname(std::move(surname));
	employee_->set_hours_worked(hours);
	employee_->set_email(std::move(email));
	employee_->set_phone(std::move(phone));
	QDialog::accept();
}

EmployeeDialog::~EmployeeDialog()
{
}