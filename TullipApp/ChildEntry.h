/**
 * @file ChildEntry.h
 * @brief Defines the `ChildEntry` class for managing the graphical representation of a child in the GUI.
 * @details This file contains the declaration of the `ChildEntry` class, which provides a Qt-based widget
 *          for displaying and interacting with a `Child` object in the GUI.
 */

#ifndef CHILDENTRY_H
#define CHILDENTRY_H

#include <QWidget>
#include "ui_ChildEntry.h"
#include "Person.h"

/**
 * @class ChildEntry
 * @brief Represents a GUI widget for a child entry.
 * @details The `ChildEntry` class provides a graphical representation of a `Child` object in the GUI.
 *          It allows for displaying and interacting with the details of a child.
 * @see Child
 */
class ChildEntry : public QWidget
{
	Q_OBJECT

signals:
	/**
	 * @brief Signal emitted when a parent search is requested.
	 * @details This signal is emitted when the user clicks on a parrent and requests to search for a parent associated with the child.
	 * @param parent A pointer to the `Parent` object associated with the child.
	 */
	void parrentSearchRequested(Parent* parent);

	/**
	 * @brief Signal emitted when a child edit is requested.
	 * @details This signal is emitted when the user clicks on a child's edit button and requests to edit the child's details.
	 * @param child A pointer to the `Child` object to be edited.
	 */
	void editRequested(Child* child);

	/**
	 * @brief Signal emitted when a child removal is requested.
	 * @details This signal is emitted when the user clicks on a child's remove button and requests to remove the child from the database.
	 * @param child A pointer to the `Child` object to be removed.
	 */
	void removeRequested(Child* child);

public:
	/**
	 * @brief Constructs a `ChildEntry` widget.
	 * @param parent The parent widget.
	 * @param child A pointer to the `Child` object to represent in the widget.
	 */
	ChildEntry(QWidget* parent, Child* child);

	/**
	 * @brief Destructor.
	 * @details Cleans up resources used by the `ChildEntry` widget.
	 */
	~ChildEntry();

private:
	Ui::ChildEntryClass ui; ///< The user interface for the child entry widget.
	Child* child_; ///< Pointer to the `Child` object represented by this widget.

	/**
	 * @brief Search function that is called when the user clicks on the child's mother label.
	 * @details This function emits the `parrentSearchRequested` signal with the child's mother as the parameter.
	 */
	void search_mother();

	/**
	 * @brief Search function that is called when the user clicks on the child's father label.
	 * @details This function emits the `parrentSearchRequested` signal with the child's father as the parameter.
	 */
	void search_father();

	/**
	 * @brief Sets up the child entry widget.
	 */
	void setup_child_entry();
};

#endif // CHILDENTRY_H
