#include "PersonLabel.h"

PersonLabel::PersonLabel(QWidget* parent, Person* person)
	: QWidget(parent), person_(person)
{
	ui.setupUi(this);
	ui.name_surname->setTextFormat(Qt::PlainText);
	ui.name_surname->setText(QString::fromStdString(person_->get_name() + " " + person_->get_surname()));
	connect(ui.name_surname, &ClickableLabel::clicked, this, &PersonLabel::on_label_clicked);
}

void PersonLabel::on_label_clicked()
{
	if (Child* child = dynamic_cast<Child*>(person_))
	{
		emit childClicked(child);
	}
	else if (Parent* parent = dynamic_cast<Parent*>(person_))
	{
		emit parentClicked(parent);
	}
	else if (Employee* employee = dynamic_cast<Employee*>(person_))
	{
		emit employeeClicked(employee);
	}
	else
	{
		emit personClicked(person_);
	}
}

PersonLabel::~PersonLabel()
{
}