/**
 * @file ChildCheckBox.h
 * @brief Defines the `ChildCheckBox` class for managing a checkbox widget for a child.
 * @details This file contains the declaration of the `ChildCheckBox` class, which provides a Qt-based widget
 *          for displaying a checkbox associated with a `Child` object. It allows for checking and unchecking
 *          the checkbox and retrieving the associated child object.
 */

#ifndef CHILDCHECKBOX_H_
#define CHILDCHECKBOX_H_

#include <QWidget>
#include "ui_ChildCheckBox.h"
#include "Person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChildCheckBoxClass; };
QT_END_NAMESPACE

/**
 * @class ChildCheckBox
 * @brief Represents a checkbox widget for a child.
 * @details The `ChildCheckBox` class provides a graphical representation of a checkbox associated with a `Child` object.
 *          It allows for checking and unchecking the checkbox and retrieving the associated child object.
 * @see Child
 */
class ChildCheckBox : public QWidget
{
	Q_OBJECT

public:
	/**
	 * @brief Constructor for ChildCheckBox
	 * @param parent Parent widget
	 * @param child Pointer to the Child object
	 * @param checked Initial checked state of the checkbox
	 */
	ChildCheckBox(QWidget* parent, Child* child, bool checked);

	/**
	 * @brief Get the state of the checkbox
	 * @param checked Checked state
	 */
	bool is_checked();

	/**
	 * @brief Get the child object
	 * @return Pointer to the Child object
	 */
	Child* get_child();

	/**
	 * @brief Destructor for ChildCheckBox
	 */
	~ChildCheckBox();

private:
	Ui::ChildCheckBoxClass ui; ///< The user interface for the checkbox widget.
	Child* child_; ///< Pointer to the Child object associated with this checkbox.
};

#endif // CHILDCHECKBOX_H_