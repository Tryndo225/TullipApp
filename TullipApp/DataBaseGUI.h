/**
 * @file DataBaseGUI.h
 * @brief Defines the `DataBaseGUI` class for managing the graphical user interface of the database.
 * @details This file contains the declaration of the `DataBaseGUI` class, which provides a GUI for interacting
 *          with the database, including managing children, parents, employees, lessons and other entities.
 */

#ifndef DATABASEGUI_H
#define DATABASEGUI_H

#include <QMainWindow>
#include "ui_DataBaseGUI.h"
#include "DataBase.h"
#include "LessonEntry.h"
#include "ChildEntry.h"
#include "ParentEntry.h"
#include "EmployeeEntry.h"
#include "ChildDialog.h"
#include "ParentDialog.h"
#include "EmployeeDialog.h"
#include "LessonDialog.h"
#include "LessonView.h"

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

	void palette_change(const QPalette& palette);

	/**
	 * @brief Destructor for `DataBaseGUI`.
	 * @details Cleans up resources used by the GUI by calling clear on all tabs.
	 */
	~DataBaseGUI();

private:
	Ui::DataBaseGUIClass ui; ///< The user interface for the GUI.

	Database database_; ///< The database being managed by the GUI.

	int child_sort_index_ = 1; ///< The current sort index for children.
	int parent_sort_index_ = 1; ///< The current sort index for parents.
	int employee_sort_index_ = 1; ///< The current sort index for employees.
	int lesson_sort_index_ = 1; ///< The current sort index for lessons.

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
	 * @brief Selects the appropriate sorting to use based on lesson sort index.
	 */
	void sort_to_populate_lesson_tab();

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
	 * @brief Populates the lessons tab with a list of lessons.
	 * @param lessons A vector of pointers to `Lesson` objects to display.
	 */
	void populate_lesson_tab(const std::vector<Lesson*>& lessons);

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
	 * @brief Populates the lessons tab with a multimap of lessons.
	 * @tparam T The type of the key in the multimap.
	 * @param lessons A multimap of keys and pointers to `Lesson` objects to display.
	 */
	template<typename T>
	void populate_lesson_tab(const std::multimap<T, Lesson*>& lessons);

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

	/**
	 * @brief Clears the lessons tab.
	 * @details Removes all entries from the lessons tab in the GUI.
	 */
	void lesson_tab_clear();

	/**
	 * @brief Adds a new child to the database.
	 * @details This function opens a dialog for adding a new child and updates the GUI upon completion.
	 * @param child A pointer to the `Child` object to add.
	 */
	void child_add();

	/**
	 * @brief Adds a new parent to the database.
	 * @details This function opens a dialog for adding a new parent and updates the GUI upon completion.
	 * @param child A pointer to the `Parent` object to add.
	 */
	void parent_add();

	/**
	 * @brief Adds a new employee to the database.
	 * @details This function opens a dialog for adding a new employee and updates the GUI upon completion.
	 * @param child A pointer to the `Employee` object to add.
	 */
	void employee_add();

	/**
	 * @brief Adds a new lesson to the database.
	 * @details This function opens a dialog for adding a new lesson and updates the GUI upon completion.
	 * @param child A pointer to the `Lesson` object to add.
	 */
	void lesson_add();

	/**
	 * @brief Edits an existing child in the database.
	 * @details This function opens a dialog for editing an existing child and updates the GUI upon completion.
	 * @param child A pointer to the `Child` object to edit.
	 */
	void child_edit(Child* child);

	/**
	 * @brief Edits an existing parent in the database.
	 * @details This function opens a dialog for editing an existing parent and updates the GUI upon completion.
	 * @param child A pointer to the `Parent` object to edit.
	 */
	void parent_edit(Parent* child);

	/**
	 * @brief Edits an existing employee in the database.
	 * @details This function opens a dialog for editing an existing employee and updates the GUI upon completion.
	 * @param child A pointer to the `Employee` object to edit.
	 */
	void employee_edit(Employee* child);

	/**
	 * @brief Removes a child from the database.
	 * @details This function removes a child from the database and updates the GUI accordingly.
	 * @param child A pointer to the `Child` object to remove.
	 */
	void child_remove(Child* child);

	/**
	 * @brief Removes a parent from the database.
	 * @details This function removes a parent from the database and updates the GUI accordingly.
	 * @param child A pointer to the `Parent` object to remove.
	 */
	void parent_remove(Parent* child);

	/**
	 * @brief Removes an employee from the database.
	 * @details This function removes an employee from the database and updates the GUI accordingly.
	 * @param child A pointer to the `Employee` object to remove.
	 */
	void employee_remove(Employee* child);

	/**
	 * @brief Removes a lesson from the database.
	 * @details This function removes a lesson from the database and updates the GUI accordingly.
	 * @param lesson A pointer to the `Lesson` object to remove.
	 */
	void lesson_remove(Lesson* lesson);

	/**
	 * @brief Views a lesson in the GUI.
	 * @details This function opens a dialog to view the details of a lesson.
	 * @param lesson A pointer to the `Lesson` object to view.
	 */
	void lesson_view(Lesson* lesson);

	/**
	 * @brief Changes the sorting method for children.
	 * @param sort_index The index of the selected sorting method.
	 */
	void child_sort_change(int sort_index);

	/**
	 * @brief Changes the sorting method for parents.
	 * @param sort_index The index of the selected sorting method.
	 */
	void parent_sort_change(int sort_index);

	/**
	 * @brief Changes the sorting method for employees.
	 * @param sort_index The index of the selected sorting method.
	 */
	void employee_sort_change(int sort_index);

	/**
	 * @brief Changes the sorting method for lessons.
	 * @param sort_index The index of the selected sorting method.
	 */
	void lesson_sort_change(int sort_index);

	/**
	 * @brief Searches for children based on the provided name and surname.
	 * @details This function filters the list of children based on the provided name and surname.
	 */
	void child_search();

	/**
	 * @brief Searches for parents based on the provided name and surname.
	 * @details This function filters the list of parents based on the provided name and surname.
	 */
	void parent_search();

	/**
	 * @brief Searches for employees based on the provided name and surname.
	 * @details This function filters the list of employees based on the provided name and surname.
	 */
	void employee_search();

	/**
	 * @brief Searches for lessons based on the provided child name and surname.
	 * @details This function filters the list of lessons based on the provided child name and surname.
	 */
	void lesson_search();

	/**
	* @brief Searches for children based on the provided child pointer.
	* @param child A pointer to the `Child` object to search for.
	*/
	void child_search_by_pointer(Child* child);

	/**
	 * @brief Searches for parents based on the provided parent pointer.
	 * @param child A pointer to the `Parent` object to search for.
	 */
	void parent_search_by_pointer(Parent* child);

	/**
	 * @brief Searches for employees based on the provided employee pointer.
	 * @param child A pointer to the `Employee` object to search for.
	 */
	void employee_search_by_pointer(Employee* child);
};

#endif // DATABASEGUI_H
