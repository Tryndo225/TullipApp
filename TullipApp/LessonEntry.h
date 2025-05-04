/**
 * @file LessonEntry.h
 * @brief Defines the `LessonEntry` class for managing the graphical representation of a lesson in the GUI.
 * @details This file contains the declaration of the `LessonEntry` class, which provides a Qt-based widget
 *			for displaying and interacting with a `Lesson` object in the GUI.
 */

#ifndef DATABASEGUI_H_
#define DATABASEGUI_H_

#include <QWidget>
#include "ui_LessonEntry.h"
#include "Lesson.h"

/**
 * @class LessonEntry
 * @brief Represents a GUI widget for a lesson entry.
 * @details The `LessonEntry` class provides a graphical representation of a `Lesson` object in the GUI.
 *			It allows for displaying and interacting with the details of a lesson.
 * @see Lesson
 */
class LessonEntry : public QWidget
{
	Q_OBJECT
signals:
	/**
	 * @brief Signal emitted when a lesson removal is requested.
	 * @details This signal is emitted when the user clicks on a lesson's remove button and requests to remove the lesson from the database.
	 * @param lesson A pointer to the `Lesson` object to be removed.
	 */
	void removeRequested(Lesson* lesson);

	/**
	 * @brief Signal emitted when a lesson view is requested.
	 * @details This signal is emitted when the user clicks on a lesson's view button and requests to view the lesson's details.
	 * @param lesson A pointer to the `Lesson` object to be viewed.
	 */
	void viewRequested(Lesson* lesson);

public:
	/**
	 * @brief Constructs a `LessonEntry` widget.
	 * @details This constructor initializes the `LessonEntry` widget with the specified parent and lesson, and sets it up.
	 * @param parent The parent widget.
	 * @param lesson A pointer to the `Lesson` object to be displayed.
	 */
	LessonEntry(QWidget* parent, Lesson* lesson);

	/**
	 * @brief Function called when the address label is clicked.
	 * @details Resonsible for copying the address to the clipboard.
	 */
	void address_clicked();

	/**
	 * @brief Destructor for the `LessonEntry` widget.
	 */
	~LessonEntry();

private:
	Ui::LessonEntryClass ui; ///< The UI class for the lesson entry widget.
	Lesson* lesson_; ///< A pointer to the `Lesson` object being displayed.
};

#endif // DATABASEGUI_H_
