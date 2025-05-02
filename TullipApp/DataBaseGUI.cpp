#include "DataBaseGUI.h"
#include <QScrollBar>

DataBaseGUI::DataBaseGUI(Database&& database, QWidget* parent)
	: QMainWindow(parent), database_(std::move(database))
{
	ui.setupUi(this);
	connect(ui.children_add_button, &QPushButton::clicked, this, &DataBaseGUI::child_add);
	connect(ui.children_sort_selector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DataBaseGUI::child_sort_change);
	connect(ui.children_search_bar, &QLineEdit::editingFinished, this, &DataBaseGUI::child_search);
	sort_to_populate_children_tab();
}

void DataBaseGUI::child_add()
{
	std::cout << "Child add button clicked" << std::endl;
	Child* child = new Child("", "", Date(1, 1, 1));
	std::cout << "Creating new child" << std::endl;
	ChildDialog dialog(this, child, database_);
	if (dialog.exec() == QDialog::Accepted)
	{
		database_.add_child(*child);
		std::cout << "Child added successfully" << std::endl;
		sort_to_populate_children_tab();
	}
	else
	{
		std::cout << "Child add cancelled" << std::endl;
	}
	delete child;
}

void DataBaseGUI::child_edit(Child* child)
{
	database_.update_child_start(child);
	ChildDialog dialog(this, child, database_);
	if (dialog.exec() == QDialog::Accepted)
	{
		std::cout << "Child edited successfully" << std::endl;
		database_.update_child_end(child);
		sort_to_populate_children_tab();
	}
	else
	{
		std::cout << "Child edit cancelled" << std::endl;
		database_.update_child_end(child);
	}
}

void DataBaseGUI::child_remove(Child* child)
{
	database_.remove_child(child);
	sort_to_populate_children_tab();
}

void DataBaseGUI::child_sort_change(int sort_index)
{
	child_sort_index_ = sort_index;
	ui.children_search_bar->clear();
	sort_to_populate_children_tab();
}

void DataBaseGUI::child_search()
{
	auto search_string = ui.children_search_bar->text();
	auto children = database_.search_children(search_string.toStdString());
	populate_children_tab(children);
}

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

		ui.children_scroll_contents->layout()->addWidget(entry);
	}
	ui.children_scroll->verticalScrollBar()->setValue(0);
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
		ui.children_scroll_contents->layout()->addWidget(entry);
	}
	ui.children_scroll->verticalScrollBar()->setValue(0);
}

void DataBaseGUI::children_tab_clear()
{
	// Clear the existing entries in the tab
	QLayout* layout = ui.children_scroll_contents->layout();
	if (!layout) return;

	// Delete all items in the layout
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

DataBaseGUI::~DataBaseGUI()
{
}