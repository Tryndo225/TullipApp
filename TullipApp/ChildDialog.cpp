#include "ChildDialog.h"
#include <qmessagebox.h>

ChildDialog::ChildDialog(QWidget* parent, Child* child, Database& database)
	: QDialog(parent), child_(child), database_(database), past_mom_(child->get_mom()), past_dad_(child->get_dad())
{
	ui.setupUi(this);
	setWindowTitle("Child Dialog");

	ui.name_edit->setText(QString::fromStdString(child_->get_name()));
	ui.surname_edit->setText(QString::fromStdString(child_->get_surname()));

	if (child_->get_birth_date().get_date_string() == "00/00/0000")
	{
		ui.birthdate_edit->setText("");
	}
	else
	{
		ui.birthdate_edit->setText(QString::fromStdString(child_->get_birth_date().get_date_string()));
	}

	populate_parents(database_.sort_parents_by_surname());

	if (child_->get_mom() != nullptr)
	{
		auto mom_name = child_->get_mom()->get_name() + " " + child_->get_mom()->get_surname();
		ui.mom_edit->setCurrentText(QString::fromStdString(mom_name));
	}
	if (child_->get_dad() != nullptr)
	{
		auto dad_name = child_->get_dad()->get_name() + " " + child_->get_dad()->get_surname();
		ui.dad_edit->setCurrentText(QString::fromStdString(dad_name));
	}
}

void ChildDialog::accept()
{
	auto name = ui.name_edit->text().toStdString();
	auto surname = ui.surname_edit->text().toStdString();
	auto birthdate = ui.birthdate_edit->text().toStdString();

	if (name.empty() || surname.empty() || birthdate.empty())
	{
		QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
		return;
	}

	child_->set_name(std::move(name));
	child_->set_surname(std::move(surname));
	child_->set_birth_date(std::move(Date(birthdate)));
	set_parents();
	QDialog::accept();
}

void ChildDialog::set_parents()
{
	auto selected_mom = ui.mom_edit->currentText().toStdString();
	auto selected_dad = ui.dad_edit->currentText().toStdString();
	if (!selected_mom.empty())
	{
		auto mom = database_.get_parent_by_name_surname(selected_mom);
		if (mom != past_mom_)
		{
			if (past_mom_ != nullptr)
			{
				past_mom_->remove_child(child_);
			}
			if (mom->is_mother())
			{
				child_->set_mom(mom);
				mom->add_child(child_);
			}
			else
			{
				QMessageBox::warning(this, "Input Error", "Selected mother is not a mother. Thus, she was not set as one.");
			}
		}
	}
	if (!selected_dad.empty())
	{
		auto dad = database_.get_parent_by_name_surname(selected_dad);

		if (dad != past_dad_)
		{
			if (past_dad_ != nullptr)
			{
				past_dad_->remove_child(child_);
			}
			if (dad->is_father())
			{
				child_->set_dad(dad);
				dad->add_child(child_);
			}
			else
			{
				QMessageBox::warning(this, "Input Error", "Selected father is not a father. Thus, he was not set as one.");
			}
		}
	}
}

void ChildDialog::populate_parents(std::multimap<std::string, Parent*> parents)
{
	for (const auto& [key, parent] : parents)
	{
		ui.mom_edit->addItem(QString::fromStdString(parent->get_name() + " " + parent->get_surname()));
		ui.dad_edit->addItem(QString::fromStdString(parent->get_name() + " " + parent->get_surname()));
	}
}