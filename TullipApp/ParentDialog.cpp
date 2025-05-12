#include "ParentDialog.h"
#include "Helper_Functions.h"
#include <QMessageBox>
#include <QScrollBar>

ParentDialog::ParentDialog(QWidget* parent, Parent* database_parent, Database& database)
	: QDialog(parent), database_parent_(database_parent), database_(database)
{
	ui.setupUi(this);

	setWindowTitle("Parent Dialog");

	ui.okButton->setAutoDefault(false);
	ui.cancelButton->setAutoDefault(false);
	ui.okButton->setDefault(false);
	ui.cancelButton->setDefault(false);

	ui.name_edit->setText(QString::fromStdString(database_parent_->get_name()));
	ui.surname_edit->setText(QString::fromStdString(database_parent_->get_surname()));
	ui.email_edit->setText(QString::fromStdString(database_parent_->get_email().get_email()));
	ui.gender_comboBox->setCurrentIndex(database_parent_->is_mother() ? 0 : 1);
	populate_children(database_.sort_children_by_surname());

	connect(ui.name_edit, &QLineEdit::returnPressed, this, &ParentDialog::children_search);
	connect(ui.surname_edit, &QLineEdit::returnPressed, this, &ParentDialog::children_search);
}

void ParentDialog::children_search()
{
	auto search_name = ui.name_edit->text();
	auto search_surname = ui.surname_edit->text();

	if (search_name.isEmpty() && search_surname.isEmpty())
	{
		populate_children(database_.sort_children_by_surname());
		return;
	}

	auto children = database_.search_children(search_name.toStdString(), search_surname.toStdString());
	populate_children(children);
}

void ParentDialog::populate_children(const std::multimap<std::string, Child*>& children)
{
	clear_children();

	for (const auto& child : children)
	{
		auto child_check_box = new PersonCheckBox(this, child.second, contains(database_parent_->get_children(), child.second));
		ui.children_contents->layout()->addWidget(child_check_box);
	}

	ui.children->verticalScrollBar()->setValue(0);
}

void ParentDialog::populate_children(const std::vector<Child*>& children)
{
	clear_children();

	for (const auto& child : children)
	{
		auto child_check_box = new PersonCheckBox(this, child, contains(database_parent_->get_children(), child));
		ui.children_contents->layout()->addWidget(child_check_box);
	}

	ui.children->verticalScrollBar()->setValue(0);
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

	for (auto& child_check_box : ui.children_contents->findChildren<PersonCheckBox*>())
	{
		auto* child = child_check_box->get_child();
		if (child_check_box->is_checked())
		{
			if (!contains(database_parent_->get_children(), child))
			{
				database_parent_->add_child(child);
			}
		}
		else
		{
			database_parent_->remove_child(child);
		}
	}

	QDialog::accept();
}

void ParentDialog::clear_children()
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
	}
}

ParentDialog::~ParentDialog()
{
	clear_children();
}