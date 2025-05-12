/**
 * @file ChildLabel.h
 * @brief Defines the ChildLabel class for displaying child name.
 * @details This class represents a label for displaying child information in the ParrentEntry widget.
 */

#ifndef CHILDLABEL_H_
#define CHILDLABEL_H_

#include <QWidget>
#include "ui_PersonLabel.h"
#include "Person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PersonLabelClass; };
QT_END_NAMESPACE

/**
 * @class PersonLabel
 * @brief Represents a label for displaying person name.
 * @details This class is used to create a label that displays the name of a person and emits a signal when clicked.
 * @see Person
 * @see Child
 * @see Parent
 * @see Employee
 */
class PersonLabel : public QWidget
{
	Q_OBJECT

signals:
	/**
	 * @brief Signal emitted when the person label is clicked.
	 * @param person A pointer to the clicked person.
	 */
	void childClicked(Child* child);

	/**
	 * @brief Signal emitted when the parent label is clicked.
	 * @param person A pointer to the clicked parent.
	 */
	void parentClicked(Parent* perent);

	/**
	 * @brief Signal emitted when the employee label is clicked.
	 * @param person A pointer to the clicked employee.
	 */
	void employeeClicked(Employee* employee);

	/**
	 * @brief Signal emitted when the person label is clicked.
	 * @param person A pointer to the clicked person.
	 */
	void personClicked(Person* person);

public:
	/**
	 * @brief Constructs a PersonLabel for a given person and sets up the UI.
	 * @param parent The parent widget.
	 * @param person A pointer to the person to be displayed.
	 */
	PersonLabel(QWidget* parent, Person* person);

	/**
	 * @brief Destructor of PersonLabel.
	 */
	~PersonLabel();

private:
	Ui::PersonLabelClass ui; ///< The UI class for the PersonLabel.
	Person* person_; ///< Pointer to the person being displayed.

	/**
	 * @brief Handles the click event on the label.
	 * @details This function emits the appropriate signal based on the type of person clicked.
	 */
	void on_label_clicked();
};

#endif // CHILDLABEL_H_
