#include "EmployeeEntry.h"
#include <QMessageBox>

EmployeeEntry::EmployeeEntry(QWidget* parent, Employee* employee)
	: QWidget(parent), employee_(employee)
{
	ui.setupUi(this);
	ui.name->setTextFormat(Qt::PlainText);
	ui.surname->setTextFormat(Qt::PlainText);
	ui.hours_worked->setTextFormat(Qt::PlainText);
	ui.email->setTextFormat(Qt::PlainText);
	ui.phone->setTextFormat(Qt::PlainText);

	connect(ui.edit_button, &QPushButton::clicked, this, [this]() { emit editRequested(employee_); });
	connect(ui.remove_button, &QPushButton::clicked, this, [this]() { emit removeRequested(employee_); });
	connect(ui.email, &ClickableLabel::clicked, this, &EmployeeEntry::email_clicked);
	connect(ui.phone, &ClickableLabel::clicked, this, &EmployeeEntry::phone_clicked);

	setup_employee_entry();
}

void EmployeeEntry::setup_employee_entry()
{
	ui.name->setText(QString::fromStdString(employee_->get_name()));
	ui.surname->setText(QString::fromStdString(employee_->get_surname()));
	ui.hours_worked->setText(QString::fromStdString("Hours: " + std::to_string(employee_->get_hours_worked())));
	ui.email->setText(QString::fromStdString(employee_->get_email().get_email()));
	ui.phone->setText(QString::fromStdString(employee_->get_phone().get_phone()));
}

void EmployeeEntry::email_clicked()
{
	if (employee_->get_email().get_email().empty())
	{
		QMessageBox::warning(this, "No Email", "No email address available.");
		return;
	}

	if (!employee_->get_email().copy())
	{
		QMessageBox::warning(this, "Copy Failed", "Failed to copy email to clipboard.");
	}
	else
	{
		QMessageBox::information(this, "Email Copied", "Email copied to clipboard: " + QString::fromStdString(employee_->get_email().get_email()));
	}
}

void EmployeeEntry::phone_clicked()
{
	if (employee_->get_phone().get_phone().empty())
	{
		QMessageBox::warning(this, "No Phone", "No phone number available.");
		return;
	}
	if (!employee_->get_phone().copy())
	{
		QMessageBox::warning(this, "Copy Failed", "Failed to copy phone number to clipboard.");
	}
	else
	{
		QMessageBox::information(this, "Phone Copied", "Phone number copied to clipboard: " + QString::fromStdString(employee_->get_phone().get_phone()));
	}
}

EmployeeEntry::~EmployeeEntry()
{
}