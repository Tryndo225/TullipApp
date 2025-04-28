#include "ChildEntry.h"
#include <QString> // Include QString header for conversion

ChildEntry::ChildEntry(QWidget* parent, Child* child)
	: QWidget(parent)
{
	std::cout << "Creating ChildEntry for child: " << child->get_name() << std::endl;
	ui.setupUi(this);
	ui.name->setText(QString::fromStdString(child->get_name()));
	ui.surname->setText(QString::fromStdString(child->get_surname()));
	ui.date_of_birth->setText(QString::fromStdString(child->get_birth_date().get_date_string()));
	if (child->get_mom() != nullptr)
	{
		ui.mother_full_name->setText(QString::fromStdString(child->get_mom()->get_name()));
	}
	else
	{
		ui.mother_full_name->setText("");
	}
	if (child->get_dad() != nullptr)
	{
		ui.father_full_name->setText(QString::fromStdString(child->get_dad()->get_name()));
	}
	else
	{
		ui.father_full_name->setText("");
	}
	std::cout << "ChildEntry created for child: " << child->get_name() << std::endl;
}

ChildEntry::~ChildEntry()
{
}