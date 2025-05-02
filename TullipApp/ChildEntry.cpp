#include "ChildEntry.h"
#include <QString> // Include QString header for conversion

ChildEntry::ChildEntry(QWidget* parent, Child* child)
	: QWidget(parent), child_(child)
{
	std::cout << "Creating ChildEntry for child: " << child->get_name() << std::endl;
	ui.setupUi(this);
	ui.name->setTextFormat(Qt::PlainText);
	ui.surname->setTextFormat(Qt::PlainText);
	ui.date_of_birth->setTextFormat(Qt::PlainText);
	ui.age->setTextFormat(Qt::PlainText);
	ui.mother_full_name->setTextFormat(Qt::PlainText);
	ui.father_full_name->setTextFormat(Qt::PlainText);

	connect(ui.edit_button, &QPushButton::clicked, this, &ChildEntry::on_edit_button_clicked);
	connect(ui.remove_button, &QPushButton::clicked, this, &ChildEntry::on_remove_button_clicked);
	setup_childentry();
}

void ChildEntry::setup_childentry()
{
	ui.name->setText(QString::fromStdString(child_->get_name()));
	ui.surname->setText(QString::fromStdString(child_->get_surname()));
	ui.date_of_birth->setText(QString::fromStdString(child_->get_birth_date().get_date_string()));
	ui.age->setText(QString::number(child_->get_age()));

	if (child_->get_mom() != nullptr)
	{
		ui.mother_full_name->setText(QString::fromStdString(child_->get_mom()->get_name()));
	}
	else
	{
		ui.mother_full_name->setText("");
	}
	if (child_->get_dad() != nullptr)
	{
		ui.father_full_name->setText(QString::fromStdString(child_->get_dad()->get_name()));
	}
	else
	{
		ui.father_full_name->setText("");
	}
	std::cout << "ChildEntry created for child: " << child_->get_name() << std::endl;
}

void ChildEntry::on_edit_button_clicked()
{
	std::cout << "Edit button clicked for child: " << ui.name->text().toStdString() << std::endl;

	emit editRequested(child_);
}

void ChildEntry::on_remove_button_clicked()
{
	std::cout << "Remove button clicked for child: " << ui.name->text().toStdString() << std::endl;

	emit removeRequested(child_);
}

ChildEntry::~ChildEntry()
{
}