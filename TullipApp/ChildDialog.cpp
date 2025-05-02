#include "ChildDialog.h"
#include <qmessagebox.h>

ChildDialog::ChildDialog(QWidget* parent, Child* child, Database& database)
	: QDialog(parent), child_(child), database_(database)
{
	std::cout << "Creating ChildDialog for child: " << child_->get_name() << std::endl;
	ui.setupUi(this);
	setWindowTitle("Child Dialog");
	ui.name_edit->setText(QString::fromStdString(child_->get_name()));
	ui.surname_edit->setText(QString::fromStdString(child_->get_surname()));
	ui.birthdate_edit->setText(QString::fromStdString(child_->get_birth_date().get_date_string()));

	populate_parents(database_.sort_parents_by_surname());
}

void ChildDialog::accept()
{
	std::cout << "Accepting ChildDialog" << std::endl;
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
		child_->set_mom(database_.get_parent_by_name_surname(selected_mom));
	}
	if (!selected_dad.empty())
	{
		child_->set_dad(database_.get_parent_by_name_surname(selected_dad));
	}
}

void ChildDialog::populate_parents(std::multimap<std::string, Parent*> parents)
{
	for (const auto& [key, parent] : parents)
	{
		ui.mom_edit->addItem(QString::fromStdString(parent->get_name() + parent->get_surname()));
		ui.dad_edit->addItem(QString::fromStdString(parent->get_name() + parent->get_surname()));
	}
}