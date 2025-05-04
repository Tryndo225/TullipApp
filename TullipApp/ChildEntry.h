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
	void parrentSearchRequested(Parent* parent);
	void editRequested(Child* child);
	void removeRequested(Child* child);

public:
	/**
	 * @brief Constructs a `ChildEntry` widget.
	 * @param parent The parent widget. Defaults to `nullptr`.
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

	void search_mother();
	void search_father();
	void setup_child_entry();
};

#endif // CHILDENTRY_H
