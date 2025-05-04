#include "DataBaseGUI.h"
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <string>

// Constructors
DataBaseGUI::DataBaseGUI()
	: QMainWindow(nullptr), database_(Database())
{
	ui.setupUi(this);
	setWindowTitle("Tullip App");
	setup();
}

DataBaseGUI::DataBaseGUI(Database&& database, QWidget* parent)
	: QMainWindow(parent), database_(std::move(database))
{
	ui.setupUi(this);
	setWindowTitle("Tullip App");
	setup();
}

// Setup the GUI
void DataBaseGUI::setup()
{
	ui.tabs->setCurrentIndex(0);
	populate_children_tab(database_.sort_children_by_surname());

	connect(ui.tabs, &QTabWidget::currentChanged, this, &DataBaseGUI::tab_change);

	connect(ui.save_to, &QAction::triggered, this, &DataBaseGUI::save_database);
	connect(ui.import_from, &QAction::triggered, this, &DataBaseGUI::import_database);
	connect(ui.export_to, &QAction::triggered, this, &DataBaseGUI::export_database);

	connect(ui.children_add_button, &QPushButton::clicked, this, &DataBaseGUI::child_add);
	connect(ui.children_sort_selector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DataBaseGUI::child_sort_change);
	connect(ui.children_search_name_bar, &QLineEdit::returnPressed, this, &DataBaseGUI::child_search);
	connect(ui.children_search_surname_bar, &QLineEdit::returnPressed, this, &DataBaseGUI::child_search);

	connect(ui.parent_add_button, &QPushButton::clicked, this, &DataBaseGUI::parent_add);
	connect(ui.parent_sort_selector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DataBaseGUI::parent_sort_change);
	connect(ui.parent_search_name_bar, &QLineEdit::returnPressed, this, &DataBaseGUI::parent_search);
	connect(ui.parent_search_surname_bar, &QLineEdit::returnPressed, this, &DataBaseGUI::parent_search);

	connect(ui.employee_add_button, &QPushButton::clicked, this, &DataBaseGUI::employee_add);
	connect(ui.employee_sort_selector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DataBaseGUI::employee_sort_change);
	connect(ui.employee_search_name_bar, &QLineEdit::returnPressed, this, &DataBaseGUI::employee_search);
	connect(ui.employee_search_surname_bar, &QLineEdit::returnPressed, this, &DataBaseGUI::employee_search);
}

// Database operations
void DataBaseGUI::save_database()
{
	QString file_path = QFileDialog::getSaveFileName(this, "Save Database", "", "Database Files (*.csv);;All Files (*)");
	if (!file_path.isEmpty())
	{
		save_path_ = file_path.toStdString();
		try
		{
			database_.export_to_csv_file(file_path.toStdString());
		}
		catch (const std::exception& e)
		{
			QMessageBox::warning(this, "Save Error", QString("Failed to save database. Reason: %1").arg(e.what()));
		}
	}
	else
	{
		QMessageBox::warning(this, "Save Error", "Failed to save database. Please select a valid file path.");
	}
}

void DataBaseGUI::import_database()
{
	QString file_path = QFileDialog::getOpenFileName(this, "Import Database", "", "Database Files (*.csv);;All Files (*)");
	if (!file_path.isEmpty())
	{
		try
		{
			database_.import_from_csv_file(file_path.toStdString());
			save_path_ = file_path.toStdString();
			ui.tabs->setCurrentIndex(0);
			sort_to_populate_children_tab();
		}
		catch (const std::exception& e)
		{
			QMessageBox::warning(this, "Import Error", QString("Failed to import database. Reason: %1").arg(e.what()));
		}
	}
	else
	{
		QMessageBox::warning(this, "Save Error", "Failed to save database. Please select a valid file path.");
	}
}

void DataBaseGUI::export_database()
{
	QString file_path = QFileDialog::getSaveFileName(this, "Export Database", "", "Database Files (*.csv);;All Files (*)");
	if (!file_path.isEmpty())
	{
		try
		{
			database_.export_to_csv_file(file_path.toStdString());
		}
		catch (const std::exception& e)
		{
			QMessageBox::warning(this, "Export Error", QString("Failed to export database. Reason: %1").arg(e.what()));
		}
	}
	else
	{
		QMessageBox::warning(this, "Save Error", "Failed to save database. Please select a valid file path.");
	}
}

// Database tab logger
void DataBaseGUI::tab_change(int index)
{
	switch (index)
	{
	case 0:
		sort_to_populate_children_tab();
		break;
	case 1:
		sort_to_populate_parent_tab();
		break;
	case 2:
		sort_to_populate_employee_tab();
		break;
	case 3:
		sort_to_populate_lesson_tab();
		break;
	default:
		break;
	}
}

// Add operations
void DataBaseGUI::child_add()
{
	Child* child = new Child();
	ChildDialog dialog(this, child, database_);
	if (dialog.exec() == QDialog::Accepted)
	{
		database_.add_child(*child);
		sort_to_populate_children_tab();
	}
	delete child;
}

void DataBaseGUI::parent_add()
{
	Parent* parent = new Parent();
	ParentDialog dialog(this, parent, database_);
	if (dialog.exec() == QDialog::Accepted)
	{
		database_.add_parent(*parent);
		sort_to_populate_parent_tab();
	}
	delete parent;
}

void DataBaseGUI::employee_add()
{
	Employee* employee = new Employee();
	EmployeeDialog dialog(this, employee);
	if (dialog.exec() == QDialog::Accepted)
	{
		database_.add_employee(*employee);
		sort_to_populate_employee_tab();
	}
	delete employee;
}

// Edit operations
void DataBaseGUI::child_edit(Child* child)
{
	database_.update_child_start(child);
	ChildDialog dialog(this, child, database_);
	if (dialog.exec() == QDialog::Accepted)
	{
		database_.update_child_end(child);
		sort_to_populate_children_tab();
	}
	else
	{
		database_.update_child_end(child);
	}
}

void DataBaseGUI::parent_edit(Parent* parent)
{
	database_.update_parent_start(parent);
	ParentDialog dialog(this, parent, database_);
	if (dialog.exec() == QDialog::Accepted)
	{
		database_.update_parent_end(parent);
		sort_to_populate_parent_tab();
	}
	else
	{
		database_.update_parent_end(parent);
	}
}

void DataBaseGUI::employee_edit(Employee* employee)
{
	database_.update_employee_start(employee);
	EmployeeDialog dialog(this, employee);
	if (dialog.exec() == QDialog::Accepted)
	{
		database_.update_employee_end(employee);
		sort_to_populate_employee_tab();
	}
	else
	{
		database_.update_employee_end(employee);
	}
}

// Remove operations
void DataBaseGUI::child_remove(Child* child)
{
	database_.remove_child(child);
	sort_to_populate_children_tab();
}

void DataBaseGUI::parent_remove(Parent* parent)
{
	database_.remove_parent(parent);
	sort_to_populate_parent_tab();
}

void DataBaseGUI::employee_remove(Employee* employee)
{
	database_.remove_employee(employee);
	sort_to_populate_employee_tab();
}

void DataBaseGUI::lesson_remove(Lesson* lesson)
{
	database_.remove_lesson(lesson);
	sort_to_populate_lesson_tab();
}

// Search operations
void DataBaseGUI::child_search_by_pointer(Child* child)
{
	ui.tabs->setCurrentIndex(0);
	ui.children_search_name_bar->setText(QString::fromStdString(child->get_name()));
	ui.children_search_surname_bar->setText(QString::fromStdString(child->get_surname()));
	child_search();
}

void DataBaseGUI::parent_search_by_pointer(Parent* parent)
{
	ui.tabs->setCurrentIndex(1);
	ui.parent_search_name_bar->setText(QString::fromStdString(parent->get_name()));
	ui.parent_search_surname_bar->setText(QString::fromStdString(parent->get_surname()));
	parent_search();
}

void DataBaseGUI::employee_search_by_pointer(Employee* employee)
{
	ui.tabs->setCurrentIndex(2);
	ui.employee_search_name_bar->setText(QString::fromStdString(employee->get_name()));
	ui.employee_search_surname_bar->setText(QString::fromStdString(employee->get_surname()));
	employee_search();
}

void DataBaseGUI::child_search()
{
	auto search_name = ui.children_search_name_bar->text();
	auto search_surname = ui.children_search_surname_bar->text();
	auto children = database_.search_children(search_name.toStdString(), search_surname.toStdString());
	populate_children_tab(children);
}

void DataBaseGUI::parent_search()
{
	auto search_name = ui.parent_search_name_bar->text();
	auto search_surname = ui.parent_search_surname_bar->text();
	auto parents = database_.search_parents(search_name.toStdString(), search_surname.toStdString());
	populate_parent_tab(parents);
}

void DataBaseGUI::employee_search()
{
	auto search_name = ui.employee_search_name_bar->text();
	auto search_surname = ui.employee_search_surname_bar->text();
	auto employees = database_.search_employees(search_name.toStdString(), search_surname.toStdString());
	populate_employee_tab(employees);
}

void DataBaseGUI::lesson_search()
{
	auto search_name = ui.lessons_search_by_child_name_bar->text();
	auto search_surname = ui.lessons_search_by_child_surname_bar->text();
	auto lessons = database_.search_lessons_by_child_name_surname(search_name.toStdString(), search_surname.toStdString());
	populate_lesson_tab(lessons);
}

// Sort change trackers
void DataBaseGUI::child_sort_change(int sort_index)
{
	child_sort_index_ = sort_index;
	ui.children_search_name_bar->clear();
	ui.children_search_surname_bar->clear();
	sort_to_populate_children_tab();
}

void DataBaseGUI::parent_sort_change(int sort_index)
{
	parent_sort_index_ = sort_index;
	ui.parent_search_name_bar->clear();
	ui.parent_search_surname_bar->clear();
	sort_to_populate_parent_tab();
}

void DataBaseGUI::employee_sort_change(int sort_index)
{
	employee_sort_index_ = sort_index;
	ui.employee_search_name_bar->clear();
	ui.employee_search_surname_bar->clear();
	sort_to_populate_employee_tab();
}

void DataBaseGUI::lesson_sort_change(int sort_index)
{
	lesson_sort_index_ = sort_index;
	ui.lessons_search_by_child_name_bar->clear();
	ui.lessons_search_by_child_surname_bar->clear();
	sort_to_populate_lesson_tab();
}

// Sort functions
void DataBaseGUI::sort_to_populate_children_tab()
{
	switch (child_sort_index_)
	{
	case 0:
		populate_children_tab(database_.sort_children_by_name());
		break;
	case 1:
		populate_children_tab(database_.sort_children_by_surname());
		break;
	case 2:
		populate_children_tab(database_.sort_children_by_birth_date());
		break;
	default:
		break;
	}
}

void DataBaseGUI::sort_to_populate_parent_tab()
{
	switch (parent_sort_index_)
	{
	case 0:
		populate_parent_tab(database_.sort_parents_by_name());
		break;
	case 1:
		populate_parent_tab(database_.sort_parents_by_surname());
		break;
	case 2:
		populate_parent_tab(database_.sort_parents_by_email());
		break;
	default:
		break;
	}
}

void DataBaseGUI::sort_to_populate_employee_tab()
{
	switch (employee_sort_index_)
	{
	case 0:
		populate_employee_tab(database_.sort_employees_by_name());
		break;
	case 1:
		populate_employee_tab(database_.sort_employees_by_surname());
		break;
	default:
		break;
	}
}

void DataBaseGUI::sort_to_populate_lesson_tab()
{
	switch (lesson_sort_index_)
	{
	case 0:
		populate_lesson_tab(database_.sort_lessons_by_day());
		break;
	case 1:
		populate_lesson_tab(database_.sort_lessons_by_time());
		break;
	case 2:
		populate_lesson_tab(database_.sort_lessons_by_schedule());
		break;
	default:
		break;
	}
}

// Populate functions
template<typename T>
void DataBaseGUI::populate_children_tab(const std::multimap<T, Child*>& children)
{
	// Clear the existing entries in the tab
	children_tab_clear();

	// Populate the tab with new entries
	for (const auto& [key, child] : children)
	{
		auto* entry = new ChildEntry(this, child);
		connect(entry, &ChildEntry::editRequested, this, &DataBaseGUI::child_edit);
		connect(entry, &ChildEntry::removeRequested, this, &DataBaseGUI::child_remove);
		connect(entry, &ChildEntry::parrentSearchRequested, this, &DataBaseGUI::parent_search_by_pointer);

		ui.children_scroll_contents->layout()->addWidget(entry);
	}
	ui.children_scroll->verticalScrollBar()->setValue(0);
}

template<typename T>
void DataBaseGUI::populate_parent_tab(const std::multimap<T, Parent*>& parents)
{
	parent_tab_clear();

	for (const auto& [key, parent] : parents)
	{
		auto* entry = new ParentEntry(this, parent);
		connect(entry, &ParentEntry::editRequested, this, &DataBaseGUI::parent_edit);
		connect(entry, &ParentEntry::removeRequested, this, &DataBaseGUI::parent_remove);
		connect(entry, &ParentEntry::childSearchRequested, this, &DataBaseGUI::child_search_by_pointer);
		ui.parents_scroll_contents->layout()->addWidget(entry);
	}
	ui.parents_scroll->verticalScrollBar()->setValue(0);
}

template<typename T>
void DataBaseGUI::populate_employee_tab(const std::multimap<T, Employee*>& employees)
{
	employee_tab_clear();
	for (const auto& [key, employee] : employees)
	{
		auto* entry = new EmployeeEntry(this, employee);
		connect(entry, &EmployeeEntry::editRequested, this, &DataBaseGUI::employee_edit);
		connect(entry, &EmployeeEntry::removeRequested, this, &DataBaseGUI::employee_remove);
		ui.employees_scroll_contents->layout()->addWidget(entry);
	}
	ui.employees_scroll->verticalScrollBar()->setValue(0);
}

template<typename T>
void DataBaseGUI::populate_lesson_tab(const std::multimap<T, Lesson*>& lessons)
{
	lesson_tab_clear();
	for (const auto& [key, lesson] : lessons)
	{
		auto* entry = new LessonEntry(this, lesson);
		// connect(entry, &LessonEntry::viewRequested, this, &DataBaseGUI::lesson_view);
		connect(entry, &LessonEntry::removeRequested, this, &DataBaseGUI::lesson_remove);
		ui.lessons_scroll_contents->layout()->addWidget(entry);
	}
	ui.lessons_scroll->verticalScrollBar()->setValue(0);
}

void DataBaseGUI::populate_children_tab(const std::vector<Child*>& children)
{
	// Clear the existing entries in the tab
	children_tab_clear();

	// Populate the tab with new entries
	for (const auto& child : children)
	{
		auto* entry = new ChildEntry(this, child);
		connect(entry, &ChildEntry::editRequested, this, &DataBaseGUI::child_edit);
		connect(entry, &ChildEntry::removeRequested, this, &DataBaseGUI::child_remove);
		connect(entry, &ChildEntry::parrentSearchRequested, this, &DataBaseGUI::parent_search_by_pointer);
		ui.children_scroll_contents->layout()->addWidget(entry);
	}
	ui.children_scroll->verticalScrollBar()->setValue(0);
}

void DataBaseGUI::populate_parent_tab(const std::vector<Parent*>& parents)
{
	parent_tab_clear();

	for (const auto& parent : parents)
	{
		auto* entry = new ParentEntry(this, parent);
		connect(entry, &ParentEntry::editRequested, this, &DataBaseGUI::parent_edit);
		connect(entry, &ParentEntry::removeRequested, this, &DataBaseGUI::parent_remove);
		connect(entry, &ParentEntry::childSearchRequested, this, &DataBaseGUI::child_search_by_pointer);
		ui.parents_scroll_contents->layout()->addWidget(entry);
	}
	ui.parents_scroll->verticalScrollBar()->setValue(0);
}

void DataBaseGUI::populate_employee_tab(const std::vector<Employee*>& employees)
{
	employee_tab_clear();
	for (const auto& employee : employees)
	{
		auto* entry = new EmployeeEntry(this, employee);
		connect(entry, &EmployeeEntry::editRequested, this, &DataBaseGUI::employee_edit);
		connect(entry, &EmployeeEntry::removeRequested, this, &DataBaseGUI::employee_remove);
		ui.employees_scroll_contents->layout()->addWidget(entry);
	}
	ui.employees_scroll->verticalScrollBar()->setValue(0);
}

void DataBaseGUI::populate_lesson_tab(const std::vector<Lesson*>& lessons)
{
	lesson_tab_clear();
	for (const auto& lesson : lessons)
	{
		auto* entry = new LessonEntry(this, lesson);
		connect(entry, &LessonEntry::removeRequested, this, &DataBaseGUI::lesson_remove);
		ui.lessons_scroll_contents->layout()->addWidget(entry);
	}
	ui.lessons_scroll->verticalScrollBar()->setValue(0);
}

// Clear functions
void DataBaseGUI::children_tab_clear()
{
	QLayout* layout = ui.children_scroll_contents->layout();

	QLayoutItem* item;
	while ((item = layout->takeAt(0)) != nullptr)
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

void DataBaseGUI::parent_tab_clear()
{
	QLayout* layout = ui.parents_scroll_contents->layout();

	QLayoutItem* item;

	while ((item = layout->takeAt(0)) != nullptr)
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

void DataBaseGUI::employee_tab_clear()
{
	QLayout* layout = ui.employees_scroll_contents->layout();
	QLayoutItem* item;
	while ((item = layout->takeAt(0)) != nullptr)
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

void DataBaseGUI::lesson_tab_clear()
{
	QLayout* layout = ui.lessons_scroll_contents->layout();
	QLayoutItem* item;
	while ((item = layout->takeAt(0)) != nullptr)
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

// Destructor
DataBaseGUI::~DataBaseGUI()
{
	if (!save_path_.empty())
	{
		try
		{
			auto quick_save_path = save_path_.substr(0, save_path_.find_last_of('.'));
			database_.export_to_csv_file(quick_save_path + "_quick_save.csv");
		}
		catch (const std::exception& e)
		{
			QMessageBox::warning(this, "Save Error", QString::fromStdString(e.what()));
		}
	}

	children_tab_clear();
	parent_tab_clear();
	employee_tab_clear();
	lesson_tab_clear();

	for (auto& connection : connections_)
	{
		disconnect(connection);
	}
}