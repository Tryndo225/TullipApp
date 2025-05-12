#include "LessonDialog.h"
#include "DateTime.h"
#include <QScrollBar>
#include <QMessageBox>

LessonDialog::LessonDialog(Lesson* lesson, Database& database, QWidget* parent)
	: lesson_(lesson), database_(database), QDialog(parent)
{
	ui.setupUi(this);

	ui.accept_button->setAutoDefault(false);
	ui.decline_button->setAutoDefault(false);
	ui.accept_button->setDefault(false);
	ui.decline_button->setDefault(false);

	ui.weekday_combo->setCurrentIndex(static_cast<int>(lesson_->get_day()));
	ui.time_edit->setTime(QTime(lesson_->get_time().get_hours(), lesson_->get_time().get_minutes()));
	ui.address_edit->setText(QString::fromStdString(lesson_->get_address().get_address()));

	populate_children(database_.sort_children_by_surname());
	populate_employees(database_.sort_employees_by_surname());

	connect(ui.children_name, &QLineEdit::returnPressed, this, &LessonDialog::children_search);
	connect(ui.children_surname, &QLineEdit::returnPressed, this, &LessonDialog::children_search);
	connect(ui.employee_name, &QLineEdit::returnPressed, this, &LessonDialog::employees_search);
	connect(ui.employee_surname, &QLineEdit::returnPressed, this, &LessonDialog::employees_search);
}

void LessonDialog::accept()
{
	if (ui.address_edit->text().isEmpty())
	{
		QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
		return;
	}
	lesson_->set_day(static_cast<WeekDays>(ui.weekday_combo->currentIndex()));
	lesson_->set_time(Time(ui.time_edit->time().hour(), ui.time_edit->time().minute(), 0));
	lesson_->set_address(ui.address_edit->text().toStdString());
	gather_children();
	gather_employees();

	QDialog::accept();
}

void LessonDialog::children_search()
{
	auto search_name = ui.children_name->text();
	auto search_surname = ui.children_surname->text();

	if (search_name.isEmpty() && search_surname.isEmpty())
	{
		populate_children(database_.sort_children_by_surname());
		return;
	}

	auto children = database_.search_children(search_name.toStdString(), search_surname.toStdString());
	populate_children(children);
}

void LessonDialog::employees_search()
{
	auto search_name = ui.employee_name->text();
	auto search_surname = ui.employee_surname->text();
	auto employees = database_.search_employees(search_name.toStdString(), search_surname.toStdString());
	populate_employees(employees);
}

void LessonDialog::populate_children(std::multimap<std::string, Child*> children)
{
	clear_children();

	for (const auto& child : children)
	{
		create_child_check_box(child.second);
	}

	ui.children_scroll->verticalScrollBar()->setValue(0);
}

void LessonDialog::populate_children(std::vector<Child*> children)
{
	clear_children();

	for (const auto& child : children)
	{
		create_child_check_box(child);
	}

	ui.children_scroll->verticalScrollBar()->setValue(0);
}

void LessonDialog::create_child_check_box(Child* child)
{
	auto* child_check_box = new PersonCheckBox(this, child, contains(lesson_->get_children(), child));
	ui.children_scroll_contents->layout()->addWidget(child_check_box);
}

void LessonDialog::populate_employees(std::multimap<std::string, Employee*> employees)
{
	clear_employees();

	for (const auto& employee : employees)
	{
		create_employee_check_box(employee.second);
	}

	ui.employee_scroll->verticalScrollBar()->setValue(0);
}

void LessonDialog::populate_employees(std::vector<Employee*> employees)
{
	clear_employees();

	for (const auto& employee : employees)
	{
		create_employee_check_box(employee);
	}

	ui.employee_scroll->verticalScrollBar()->setValue(0);
}

void LessonDialog::create_employee_check_box(Employee* employee)
{
	auto* employee_check_box = new PersonCheckBox(this, employee, contains(lesson_->get_employees(), employee));
	ui.employee_scroll_contents->layout()->addWidget(employee_check_box);
}

void LessonDialog::gather_children()
{
	auto children = lesson_->get_children();
	for (int i = 0; i < ui.children_scroll_contents->layout()->count(); ++i)
	{
		auto* check_box = qobject_cast<PersonCheckBox*>(ui.children_scroll_contents->layout()->itemAt(i)->widget());
		auto* child = check_box->get_child();
		if (check_box->is_checked())
		{
			if (!contains(children, child))
			{
				lesson_->add_child(child);
			}
		}
		else
		{
			lesson_->remove_child(child);
		}
	}
}

void LessonDialog::gather_employees()
{
	auto employees = lesson_->get_employees();
	for (int i = 0; i < ui.employee_scroll_contents->layout()->count(); ++i)
	{
		auto* check_box = qobject_cast<PersonCheckBox*>(ui.employee_scroll_contents->layout()->itemAt(i)->widget());
		auto* employee = check_box->get_employee();
		if (check_box && check_box->is_checked())
		{
			if (!contains(employees, employee))
			{
				lesson_->add_employee(employee);
			}
		}
		else
		{
			lesson_->remove_employee(employee);
		}
	}
}

void LessonDialog::clear_children()
{
	QLayoutItem* item;
	while ((item = ui.children_scroll_contents->layout()->takeAt(0)) != nullptr)
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

void LessonDialog::clear_employees()
{
	QLayoutItem* item;
	while ((item = ui.employee_scroll_contents->layout()->takeAt(0)) != nullptr)
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

LessonDialog::~LessonDialog()
{
	clear_children();
	clear_employees();
}
