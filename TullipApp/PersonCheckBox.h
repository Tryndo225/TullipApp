/**
 * @file PersonCheckBox.h
 * @brief Defines the `PersonCheckBox` class for managing a checkbox widget for a person.
 * @details This file contains the declaration of the `PersonCheckBox` class, which provides a Qt-based widget
 *          for displaying a checkbox associated with a `Person` object. It allows for checking and unchecking
 *          the checkbox and retrieving the associated person object.
 */

#ifndef PERSONCHECKBOX_H_
#define PERSONCHECKBOX_H_
#include <QWidget>
#include "ui_PersonCheckBox.h"
#include "Person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChildCheckBoxClass; };
QT_END_NAMESPACE

/**
 * @class PersonCheckBox
 * @brief Represents a checkbox widget for a person.
 * @details The `PersonCheckBox` class provides a graphical representation of a checkbox associated with a `Person` object.
 *          It allows for checking and unchecking the checkbox and retrieving the associated person object.
 * @see Person
 * @see Child
 * @see Parent
 * @see Employee
 */
class PersonCheckBox : public QWidget
{
	Q_OBJECT

public:
	/**
	 * @brief Constructor for PersonCheckBox
	 * @param parent Parent widget
	 * @param person Pointer to the Person object
	 * @param checked Initial checked state of the checkbox
	 */
	PersonCheckBox(QWidget* parent, Person* person, bool checked);

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
	 * @brief Get the Parent object
	 * @return Pointer to the Parent object
	 */
	Parent* get_parent();

	/**
	 * @brief Get the employee object
	 * @return Pointer to the Employee object
	 */
	Employee* get_employee();

	/**
	 * @brief Get the Person object
	 * @return Pointer to the Person object
	 */
	Person* get_person();

	/**
	 * @brief Destructor for ParentCheckBox
	 */
	~PersonCheckBox();

private:
	Ui::PersonCheckBoxClass ui; ///< The user interface for the checkbox widget.
	Person* person_; ///< Pointer to the Parent object associated with this checkbox.
};

#endif // CHILDCHECKBOX_H_