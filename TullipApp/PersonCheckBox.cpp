#include "PersonCheckBox.h"

PersonCheckBox::PersonCheckBox(QWidget* parent, Person* person, bool checked)
	: QWidget(parent), person_(person)
{
	ui.setupUi(this);
	ui.person_checkBox->setText(QString::fromStdString(person_->get_name() + " " + person_->get_surname()));
	ui.person_checkBox->setChecked(checked);
}

bool PersonCheckBox::is_checked()
{
	return ui.person_checkBox->isChecked();
}

Child* PersonCheckBox::get_child()
{
	if (Child* child = dynamic_cast<Child*>(person_))
	{
		return child;
	}
	return nullptr;
}

Parent* PersonCheckBox::get_parent()
{
	if (Parent* parent = dynamic_cast<Parent*>(person_))
	{
		return parent;
	}
	return nullptr;
}

Employee* PersonCheckBox::get_employee()
{
	if (Employee* employee = dynamic_cast<Employee*>(person_))
	{
		return employee;
	}
	return nullptr;
}

Person* PersonCheckBox::get_person()
{
	return person_;
}

PersonCheckBox::~PersonCheckBox()
{
}