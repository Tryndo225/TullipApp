#include "ParentDialog.h"
#include "Helper_Functions.h"
#include <QMessageBox>

ParentDialog::ParentDialog(QWidget* parent, Parent* database_parent, Database& database)
	: QDialog(parent), database_parent_(database_parent), database_(database)
{
	ui.setupUi(this);

	setWindowTitle("Parent Dialog");

	ui.name_edit->setText(QString::fromStdString(database_parent_->get_name()));
	ui.surname_edit->setText(QString::fromStdString(database_parent_->get_surname()));
	ui.email_edit->setText(QString::fromStdString(database_parent_->get_email().get_email()));
	ui.gender_comboBox->setCurrentIndex(database_parent_->is_mother() ? 0 : 1);
	populate_children(database_.sort_children_by_surname());
}

void ParentDialog::populate_children(const std::multimap<std::string, Child*>& children)
{
	for (const auto& child : children)
	{
		auto child_check_box = new ChildCheckBox(this, child.second, contains(database_parent_->get_children(), child.second));
		ui.children_contents->layout()->addWidget(child_check_box);
	}
}

void ParentDialog::accept()
{
	auto name = ui.name_edit->text().toStdString();
	auto surname = ui.surname_edit->text().toStdString();
	auto email = ui.email_edit->text().toStdString();
	bool is_mother = ui.gender_comboBox->currentIndex() == 0;

	if (name.empty() || surname.empty() || email.empty())
	{
		QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
		return;
	}
	database_parent_->set_name(std::move(name));
	database_parent_->set_surname(std::move(surname));
	database_parent_->set_email(std::move(email));

	if (is_mother)
	{
		database_parent_->set_as_mother();
	}
	else
	{
		database_parent_->set_as_father();
	}

	for (auto& child_check_box : ui.children_contents->findChildren<ChildCheckBox*>())
	{
		if (child_check_box->is_checked() && !contains(database_parent_->get_children(), child_check_box->get_child()))
		{
			database_parent_->add_child(child_check_box->get_child());
			if (database_parent_->is_mother())
			{
				child_check_box->get_child()->set_mom(database_parent_);
			}
			else
			{
				child_check_box->get_child()->set_dad(database_parent_);
			}
		}
		else if (!child_check_box->is_checked() && contains(database_parent_->get_children(), child_check_box->get_child()))
		{
			database_parent_->remove_child(child_check_box->get_child());
			if (database_parent_ == child_check_box->get_child()->get_mom())
			{
				child_check_box->get_child()->set_mom(nullptr);
			}
			else if (database_parent_ == child_check_box->get_child()->get_dad())
			{
				child_check_box->get_child()->set_dad(nullptr);
			}
		}

		QDialog::accept();
	}
}

ParentDialog::~ParentDialog()
{
	QLayoutItem* item;
	while ((item = ui.children_contents->layout()->takeAt(0)) != nullptr)
	{
		QWidget* widget = item->widget();
		if (widget)
		{
			widget->setParent(nullptr);
			delete widget;
		}
		delete item;
	}
}