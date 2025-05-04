/**
 * @file ChildDialog.h
 * @brief Defines the `ChildDialog` class for managing child-related information.
 * @details This file contains the declaration of the `ChildDialog` class, which provides a Qt-based dialog
 *		for adding or editing child information in the GUI.
 */

#ifndef CHILDDIALOG_H
#define CHILDDIALOG_H

#include <QDialog>
#include "Person.h"
#include "DataBase.h"
#include "ui_ChildDialog.h"

/**
 * @class ChildDialog
 * @brief Dialog for managing child-related information.
 * @details The ChildDialog class provides a user interface for editing child information such as name, surname,
 *          date of birth, mother, and father. It inherits from QDialog and uses the Qt framework for GUI elements.
 * @see Child
 */
class ChildDialog : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief Constructs a `ChildDialog` object.
	 * @details This constructor initializes the dialog and sets it's fields to reflect child properties.
	 * @param parent The parent widget.
	 * @param child A pointer to the `Child` object to edit or add.
	 * @param database The database to search for parents in.
	 */
	explicit ChildDialog(QWidget* parent, Child* child, Database& database);

	/**
	 * @brief Accepts the dialog and updates the child information.
	 */
	void accept() override;

	/**
	 * @brief Destructor for `ChildDialog`.
	 */
	~ChildDialog() = default;

private:
	Child* child_; ///< Pointer to the `Child` object being edited or added.
	Database& database_; ///< Reference to the database being managed.
	Parent* past_mom_; ///< Pointer to the previous mother (optional).
	Parent* past_dad_; ///< Pointer to the previous father (optional).

	Ui::ChildDialogClass ui; ///< The user interface for the child dialog.

	/**
	 * @brief sets the parents of the child.
	 */
	void set_parents();

	/**
	 * @brief Populates the parent options in the dialog.
	 * @param parents A multimap of parent names to `Parent` pointers.
	*/
	void populate_parents(std::multimap<std::string, Parent*>);
};

#endif // CHILDDIALOG_H