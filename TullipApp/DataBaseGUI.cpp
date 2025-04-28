#include "DataBaseGUI.h"

DataBaseGUI::DataBaseGUI(Database&& database, QWidget* parent)
	: QMainWindow(parent), data_base_(std::move(database))
{
	ui.setupUi(this);
	populate_children_tab(data_base_.sort_children_by_name());
}

template<typename T>
void DataBaseGUI::populate_children_tab(const std::multimap<T, Child*>& children)
{
	std::cout << "Populating children tab with multimap" << std::endl;
	// Clear the existing entries in the tab
	children_tab_clear();

	size_t count = 0;
	// Populate the tab with new entries
	for (const auto& [key, child] : children)
	{
		std::cout << "Adding child: " << child->get_name() << std::endl;
		auto* entry = new ChildEntry(this, child);

		if (ui.children_scroll_contents->layout() == nullptr)
		{
			ui.children_scroll_contents->setLayout(new QVBoxLayout());
		}

		ui.children_scroll_contents->layout()->addWidget(entry);
		count++;
	}
}

void DataBaseGUI::populate_children_tab(const std::vector<Child*>& children)
{
	// Clear the existing entries in the tab
	children_tab_clear();

	// Populate the tab with new entries
	for (const auto& child : children)
	{
		auto* entry = new ChildEntry(this, child);
		ui.children_scroll_contents->layout()->addWidget(entry);
	}
}

void DataBaseGUI::children_tab_clear()
{
	// Clear the existing entries in the tab
	std::cout << "Clearing children tab" << std::endl;
	QLayoutItem* item;
	while ((item = ui.children_scroll_contents->layout()) != nullptr)
	{
		std::cout << "Deleting item" << std::endl;
		delete item;
	}
}

DataBaseGUI::~DataBaseGUI()
{
}