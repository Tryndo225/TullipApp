/**
 * @file clickablelabel.h
 * @brief ClickableLabel class definition
 * @details This file defines a class that inherits from QLabel and emits a clicked signal when the label is clicked.
 */

#ifndef CLICKABLE_LABEL_H_
#define CLICKABLE_LABEL_H_
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

/**
 * @brief A QLabel subclass that emits a clicked signal when the label is clicked.
 * @details This class is useful for creating clickable labels in a Qt application.
 * @note The clicked signal is emitted when the left or right mouse button is released over the label.
 */
class ClickableLabel : public QLabel {
	Q_OBJECT
public:
	/**
	 * @brief Constructor for ClickableLabel.
	 * @param parent The parent widget of this label. Default is nullptr.
	 */
	explicit ClickableLabel(QWidget* parent = nullptr)
		: QLabel(parent)
	{
		setCursor(Qt::PointingHandCursor);
	}

signals:
	/**
	 * @brief Signal emitted when the label is clicked.
	 * @details This signal is emitted when the left or right mouse button is released over the label.
	 */
	void clicked();

protected:
	/**
	 * @brief Handles mouse release events.
	 * @param event The mouse event that occurred.
	 * @details This function checks if the left or right mouse button was released over the label and emits the clicked signal.
	 */
	void mouseReleaseEvent(QMouseEvent* event) override
	{
		if ((event->button() == Qt::LeftButton || event->button() == Qt::RightButton) && rect().contains(event->pos()))
		{
			emit clicked();
		}
		QLabel::mouseReleaseEvent(event);
	}
};
#endif // !CLICKABLE_LABEL_H_
