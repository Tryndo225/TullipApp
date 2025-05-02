/**
 * @file DataBaseGUI.h
 * @brief Defines the `DataBaseGUI` class for managing the graphical user interface of the database.
 * @details This file contains the declaration of the `DataBaseGUI` class, which provides a GUI for interacting
 *          with the database, including managing children and other entities.
 */

#ifndef DATABASEGUI_H
#define DATABASEGUI_H

#include <QMainWindow>
#include "ui_DataBaseGUI.h"
#include "ChildEntry.h"
#include "DataBase.h"
#include "ChildDialog.h"

 /**
  * @class DataBaseGUI
  * @brief Represents the graphical user interface for the database.
  * @details The `DataBaseGUI` class provides a Qt-based GUI for managing the database, including displaying
  *          and interacting with children, parents, lessons, and employees.
  * @see Database
  */
class DataBaseGUI : public QMainWindow
{
	Q_OBJECT

public:
	/**
	 * @brief Constructs a `DataBaseGUI` object.
	 * @param database The database to manage.
	 * @param parent The parent widget. Defaults to `nullptr`.
	 */
	DataBaseGUI(Database&& database, QWidget* parent = nullptr);

	/**
	 * @brief Adds a new child to the database.
	 * @details This function opens a dialog for adding a new child and updates the GUI upon completion.
	 * @param child A pointer to the `Child` object to add.
	 */
	void child_add();

	/**
	 * @brief Edits an existing child in the database.
	 * @details This function opens a dialog for editing an existing child and updates the GUI upon completion.
	 * @param child A pointer to the `Child` object to edit.
	 */
	void child_edit(Child* child);

	/**
	 * @brief Removes a child from the database.
	 * @details This function removes a child from the database and updates the GUI accordingly.
	 * @param child A pointer to the `Child` object to remove.
	 */
	void child_remove(Child* child);

	void child_sort_change(int sort_index);

	void child_search();

	/**
	 * @brief Destructor.
	 * @details Cleans up resources used by the `DataBaseGUI` object.
	 */
	~DataBaseGUI();

private:
	Ui::DataBaseGUIClass ui; ///< The user interface for the GUI.

	Database database_; ///< The database being managed by the GUI.

	int child_sort_index_ = 1; ///< The current sort index for children.

	void sort_to_populate_children_tab();

	/**
	 * @brief Populates the children tab with a list of children.
	 * @param children A vector of pointers to `Child` objects to display.
	 */
	void populate_children_tab(const std::vector<Child*>& children);

	/**
	 * @brief Populates the children tab with a multimap of children.
	 * @tparam T The type of the key in the multimap.
	 * @param children A multimap of keys and pointers to `Child` objects to display.
	 */
	template<typename T>
	void populate_children_tab(const std::multimap<T, Child*>& children);

	/**
	 * @brief Clears the children tab.
	 * @details Removes all entries from the children tab in the GUI.
	 */
	void children_tab_clear();
};

#endif // DATABASEGUI_H
