/**
 * @file LessonView.h
 * @brief Defines the `LessonView` class for viewing lesson-related information.
 * @details This file contains the declaration of the `LessonView` class, which provides a Qt-based widget
 *		to display and interact with a `Lesson` object in the GUI.
 */
#ifndef LESSONVIEW_H_
#define LESSONVIEW_H_

#include <QWidget>
#include "LessonDialog.h"
#include "Lesson.h"
#include "ui_LessonView.h"

/**
 * @class LessonView
 * @brief Represents a GUI widget for viewing lesson information.
 * @details The `LessonView` class provides a graphical representation of a `Lesson` object in the GUI.
 *		It allows for displaying and interacting with the details of a lesson, including children, employees,
 * @see Lesson
 */
class LessonView : public QWidget
{
	Q_OBJECT

signals:
	/**
	 * @brief Signal emitted when a child is clicked.
	 * @param child A pointer to the clicked `Child` object.
	 */
	void childClicked(Child* child);

	/**
	 * @brief Signal emitted when an employee is clicked.
	 * @param employee A pointer to the clicked `Employee` object.
	 */
	void employeeClicked(Employee* employee); 

	/**
	 * @brief Signal emitted when a lesson is edited.
	 */
	void lessonEdited();

public:
	/**
	 * @brief Constructs a `LessonView` widget.
	 * @details This constructor initializes the `LessonView` widget with the specified lesson and database.
	 * @param lesson A pointer to the `Lesson` object to be displayed.
	 * @param database The database to search for children and employees in.
	 */
	LessonView(Lesson* lesson, Database& database);

	/**
	 * @brief Destructor for the `LessonView` widget.
	 * @details Cleans up resources used by the `LessonView` widget.
	 */
	~LessonView();

private:
	Ui::LessonViewClass ui; ///< The UI class for the lesson view widget.
	Lesson* lesson_; ///< Pointer to the `Lesson` object being viewed.
	Database& database_; ///< Reference to the database being managed.

	/**
	 * @brief Function called when the address label is clicked.
	 * @details Responsible for copying the address to the clipboard.
	 */
	void address_clicked();

	/**
	 * @brief Populates the children sections of the lesson view.
	 * @details This function fills the lesson view with information about children associated with the lesson.
	 */
	void populate_children();

	/**
	 * @brief Populates the employees section of the lesson view.
	 * @details This function fills the lesson view with information about employees associated with the lesson.
	 */
	void populate_employees();

	/**
	 * @brief Clears the children section of the lesson view.
	 * @details This function removes all child information from the lesson view.
	 */
	void clear_children();

	/**
	 * @brief Clears the employees section of the lesson view.
	 * @details This function removes all employee information from the lesson view.
	 */
	void clear_employees();

	/**
	 * @brief Function called when the edit button is clicked.
	 * @details Opens a dialog to edit the lesson information.
	 */
	void edit_lesson();

	/**
	 * @brief Function called when the attendance button is clicked.
	 * @details Opens a dialog to manage attendance for the lesson.
	 */
	void attendace();
};

#endif // LESSONVIEW_H_
