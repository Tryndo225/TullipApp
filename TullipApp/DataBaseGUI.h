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
#include "DataBase.h"
#include "ChildEntry.h"
#include "ParentEntry.h"
#include "EmployeeEntry.h"
#include "ChildDialog.h"
#include "ParentDialog.h"
#include "EmployeeDialog.h"

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
	 * @brief Default constructor.
	 * @details This constructor initializes the GUI without a database.
	 */
	DataBaseGUI();

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

	void parent_add();

	void employee_add();

	/**
	 * @brief Edits an existing child in the database.
	 * @details This function opens a dialog for editing an existing child and updates the GUI upon completion.
	 * @param child A pointer to the `Child` object to edit.
	 */
	void child_edit(Child* child);

	void parent_edit(Parent* child);

	void employee_edit(Employee* child);

	/**
	 * @brief Removes a child from the database.
	 * @details This function removes a child from the database and updates the GUI accordingly.
	 * @param child A pointer to the `Child` object to remove.
	 */
	void child_remove(Child* child);

	void parent_remove(Parent* child);

	void employee_remove(Employee* child);

	void child_sort_change(int sort_index);

	void parent_sort_change(int sort_index);

	void employee_sort_change(int sort_index);

	void child_search();

	void parent_search();

	void employee_search();

	void child_search_by_pointer(Child* child);

	void parent_search_by_pointer(Parent* child);

	void employee_search_by_pointer(Employee* child);

	~DataBaseGUI();

private:
	Ui::DataBaseGUIClass ui; ///< The user interface for the GUI.

	Database database_; ///< The database being managed by the GUI.

	int child_sort_index_ = 1; ///< The current sort index for children.
	int parent_sort_index_ = 1; ///< The current sort index for parents.
	int employee_sort_index_ = 1; ///< The current sort index for employees.

	std::string save_path_ = ""; ///< The path to save the database.

	std::vector<QMetaObject::Connection> connections_; ///< List of connections for signals and slots.

	/**
	 * @brief Sets up the GUI.
	 * @details This function initializes the GUI components and connects signals to slots.
	 */
	void setup();

	/**
	 * @brief Saves the current state of the database to a file.
	 * @details This function prompts the user for a file path and saves the database to that file.
	 */
	void save_database();

	/**
	 * @brief Imports a database from a file.
	 * @details This function prompts the user for a file path and imports the database from that file.
	 */
	void import_database();

	/**
	 * @brief Exports the current database to a file.
	 * @details This function prompts the user for a file path and exports the database to that file.
	 */
	void export_database();

	/**
	 * @brief Handles tab change events.
	 * @param index The index of the newly selected tab.
	 */
	void tab_change(int index);

	/**
	 * @brief Selects the appropriate sorting to use based on child sort index.
	 */
	void sort_to_populate_children_tab();

	/**
	* @brief Selects the appropriate sorting to use based on parent sort index.
	*/
	void sort_to_populate_parent_tab();

	/**
	 * @brief Selects the appropriate sorting to use based on employee sort index.
	 */
	void sort_to_populate_employee_tab();

	/**
	 * @brief Populates the children tab with a list of children.
	 * @param children A vector of pointers to `Child` objects to display.
	 */
	void populate_children_tab(const std::vector<Child*>& children);

	/**
	 * @brief Populates the parent tab with a list of parents.
	 * @param parents A vector of pointers to `Parent` objects to display.
	 */
	void populate_parent_tab(const std::vector<Parent*>& children);

	/**
	 * @brief Populates the parent tab with a list of parents.
	 * @param parents A vector of pointers to `Parent` objects to display.
	 */
	void populate_employee_tab(const std::vector<Employee*>& children);

	/**
	 * @brief Populates the children tab with a multimap of children.
	 * @tparam T The type of the key in the multimap.
	 * @param children A multimap of keys and pointers to `Child` objects to display.
	 */
	template<typename T>
	void populate_children_tab(const std::multimap<T, Child*>& children);

	/**
	 * @brief Populates the parent tab with a multimap of parents.
	 * @tparam T The type of the key in the multimap.
	 * @param children A multimap of keys and pointers to `Parent` objects to display.
	 */
	template<typename T>
	void populate_parent_tab(const std::multimap<T, Parent*>& children);

	/**
	 * @brief Populates the parent tab with a multimap of parents.
	 * @tparam T The type of the key in the multimap.
	 * @param children A multimap of keys and pointers to `Parent` objects to display.
	 */
	template<typename T>
	void populate_employee_tab(const std::multimap<T, Employee*>& children);

	/**
	 * @brief Clears the children tab.
	 * @details Removes all entries from the children tab in the GUI.
	 */
	void children_tab_clear();

	/**
	 * @brief Clears the parent tab.
	 * @details Removes all entries from the parent tab in the GUI.
	 */
	void parent_tab_clear();

	/**
	 * @brief Clears the parent tab.
	 * @details Removes all entries from the parent tab in the GUI.
	 */
	void employee_tab_clear();
};

#endif // DATABASEGUI_H
