/**
 * @file ParentEntry.h
 * @brief Defines the `ParentEntry` class for managing the graphical representation of a parent in the GUI.
 * @details This file contains the declaration of the `ParentEntry` class, which provides a Qt-based widget
 *			for displaying and interacting with a `Parent` object in the GUI.
 */
#ifndef PARENTENTRY_H_
#define PARENTENTRY_H_

#include <QWidget>
#include "ui_ParentEntry.h"
#include "Person.h"
#include "ClickableLabel.h"
#include "PersonLabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ParentEntryClass; };
QT_END_NAMESPACE

/** 
 * @class ParentEntry
 * @brief Represents a GUI widget for a parent entry.
 * @details The `ParentEntry` class provides a graphical representation of a `Parent` object in the GUI.
 *			It allows for displaying and interacting with the details of a parent.
 * @see Parent
 */
class ParentEntry : public QWidget
{
	Q_OBJECT

signals:
	/**
	 * @brief Signal emitted when a child search is requested.
	 * @details This signal is emitted when the user clicks on a child and requests to search for a child associated with the parent.
	 * @param parent A pointer to the `Parent` object associated with the child.
	 */
	void childSearchRequested(Child* parent);

	/**
	 * @brief Signal emitted when a parent edit is requested.
	 * @details This signal is emitted when the user clicks on a parent's edit button and requests to edit the parent's details.
	 * @param parent A pointer to the `Parent` object to be edited.
	 */
	void editRequested(Parent* parent);

	/**
	 * @brief Signal emitted when a parent removal is requested.
	 * @details This signal is emitted when the user clicks on a parent's remove button and requests to remove the parent from the database.
	 * @param parent A pointer to the `Parent` object to be removed.
	 */
	void removeRequested(Parent* parent);

public:
	/**
	 * @brief Constructs a `ParentEntry` widget.
	 * @param parent The parent widget.
	 * @param database_parent A pointer to the `Parent` object to represent in the widget.
	 */
	ParentEntry(QWidget* parent, Parent* database_parent);

	/**
	 * @brief Destructor.
	 * @details Cleans up resources used by the `ParentEntry` widget.
	 */
	~ParentEntry();

private:
	Ui::ParentEntryClass ui; ///< The user interface for the parent entry widget.
	Parent* database_parent_; ///< Pointer to the `Parent` object being represented.
	
	/**
	 * @brief Sets up the parent entry widget.
	 * @details This method initializes the UI elements and connects signals and slots for user interactions.
	 *				It dynamically creates child labels for each child associated with the parent.
	 */
	void setup_parent();

	/**
	 * @brief Handles the email label click event.
	 * @details This method is called when the email label is clicked. It copies the email address to the clipboard.
	 */
	void email_clicked();
};

#endif // PARENTENTRY_H_
