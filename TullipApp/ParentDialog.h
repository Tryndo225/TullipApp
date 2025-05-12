/**
 * @file ParentDialog.h
 * @brief Defines the `ParentDialog` class for managing parent-related information.
 * @details This file contains the declaration of the `ParentDialog` class, which provides a Qt-based dialog
 *			for adding or editing parent information in the GUI.
 */
#ifndef PARENTDIALOG_H_
#define PARENTDIALOG_H_

#include <QDialog>
#include "ui_ParentDialog.h"
#include "Person.h"
#include "Database.h"
#include "PersonCheckBox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ParentDialogClass; };
QT_END_NAMESPACE

/**
 * @class ParentDialog
 * @brief Dialog for managing parent-related information.
 * @details The ParentDialog class provides a user interface for editing parent information such as name, surname,
 *			email an children. It inherits from QDialog and uses the Qt framework for GUI elements.
 */
class ParentDialog : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief Constructs a `ParentDialog` object.
	 * @details This constructor initializes the dialog and sets it's fields to reflect parent properties.
	 * @param parent_class The parent widget.
	 * @param parent A pointer to the `Parent` object to edit or add.
	 * @param database The database to search for children in.
	 */
	ParentDialog(QWidget* parent_class, Parent* parent, Database& database);

	/**
	 * @brief Populates the dialog with child checkboxes.
	 * @details This method creates checkboxes for each child in the database and adds them to the dialog.
	 * @param children A multimap of child names to child pointers.
	 */
	void populate_children(const std::multimap<std::string, Child*>& children);

	/**
	 * @brief Populates the dialog with child checkboxes.
	 * @details This method creates checkboxes for each child in the database and adds them to the dialog.
	 * @param children A vector of child pointers.
	 */
	void populate_children(const std::vector<Child*>& children);

	/**
	 * @brief Clears the child checkboxes from the dialog.
	 * @details This method removes all child checkboxes from the dialog.
	 */
	void clear_children();

	/**
	 * @brief Accepts the dialog and updates the parent information.
	 * @details This method is called when the user clicks the "OK" button in the dialog.
	 *			It validates the input fields and updates the parent object accordingly.
	 */
	void accept() override;

	/**
	 * @brief Destructor for `ParentDialog`.
	 * @details Cleans up resources used by the dialog.
	 */
	~ParentDialog();

private:
	Ui::ParentDialogClass ui; ///< The user interface for the parent dialog.
	Database& database_; ///< Reference to the database being managed.
	Parent* database_parent_; ///< Pointer to the `Parent` object being edited or added.

	/**
	 * @brief Searches for children based on the input in the name and surname fields.
	 * @details This method filters the children based on the name and surname entered in the dialog.
	 */
	void children_search();
};

#endif // PARENTDIALOG_H_
