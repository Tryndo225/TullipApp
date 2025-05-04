/**
 * @file ChildLabel.h
 * @brief Defines the ChildLabel class for displaying child name.
 * @details This class represents a label for displaying child information in the ParrentEntry widget.
 */

#ifndef CHILDLABEL_H_
#define CHILDLABEL_H_

#include <QWidget>
#include "ui_ChildLabel.h"
#include "Person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChildLabelClass; };
QT_END_NAMESPACE

/**
 * @class ChildLabel
 * @brief Represents a label for displaying child name.
 * @details This class is used to create a label that displays the name of a child and emits a signal when clicked.
 * @see Child
 */
class ChildLabel : public QWidget
{
	Q_OBJECT

signals:
	/**
	 * @brief Signal emitted when the child label is clicked.
	 * @param child A pointer to the clicked child.
	 */
	void childClicked(Child* child);

public:
	/**
	 * @brief Constructs a ChildLabel for a given child and sets up the UI.
	 * @param parent The parent widget.
	 * @param child A pointer to the child to be displayed.
	 */
	ChildLabel(QWidget* parent, Child* child);

	/**
	 * @brief Destructor of ChildLabel.
	 */
	~ChildLabel();

private:
	Ui::ChildLabelClass ui; ///< The UI class for the ChildLabel.
	Child* child_; ///< Pointer to the child being displayed.
};

#endif // CHILDLABEL_H_
