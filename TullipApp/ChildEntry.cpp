#include "ChildEntry.h"
#include <QString> // Include QString header for conversion

ChildEntry::ChildEntry(QWidget* parent, Child* child)
	: QWidget(parent), child_(child)
{
	ui.setupUi(this);
	ui.name->setTextFormat(Qt::PlainText);
	ui.surname->setTextFormat(Qt::PlainText);
	ui.date_of_birth->setTextFormat(Qt::PlainText);
	ui.age->setTextFormat(Qt::PlainText);
	ui.mother_full_name->setTextFormat(Qt::PlainText);
	ui.father_full_name->setTextFormat(Qt::PlainText);

	connect(ui.edit_button, &QPushButton::clicked, this, [this]() { emit editRequested(child_); });
	connect(ui.remove_button, &QPushButton::clicked, this, [this]() { emit removeRequested(child_); });
	connect(ui.mother_full_name, &ClickableLabel::clicked, this, &ChildEntry::search_mother);
	connect(ui.father_full_name, &ClickableLabel::clicked, this, &ChildEntry::search_father);
	setup_child_entry();
}

void ChildEntry::setup_child_entry()
{
	ui.name->setText(QString::fromStdString(child_->get_name()));
	ui.surname->setText(QString::fromStdString(child_->get_surname()));
	ui.date_of_birth->setText(QString::fromStdString(child_->get_birth_date().get_date_string()));
	ui.age->setText(QString::number(child_->get_age()));

	if (child_->get_mom() != nullptr)
	{
		ui.mother_full_name->setText(QString::fromStdString(child_->get_mom()->get_name() + " " + child_->get_mom()->get_surname()));
	}
	else
	{
		ui.mother_full_name->setText("");
	}
	if (child_->get_dad() != nullptr)
	{
		ui.father_full_name->setText(QString::fromStdString(child_->get_dad()->get_name() + " " + child_->get_dad()->get_surname()));
	}
	else
	{
		ui.father_full_name->setText("");
	}
}

void ChildEntry::search_mother()
{
	if (child_->get_mom() != nullptr)
	{
		emit parrentSearchRequested(child_->get_mom());
	}
}

void ChildEntry::search_father()
{
	if (child_->get_dad() != nullptr)
	{
		emit parrentSearchRequested(child_->get_dad());
	}
}

ChildEntry::~ChildEntry()
{
}