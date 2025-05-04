#ifndef CLICKABLE_LABEL_H_
#define CLICKABLE_LABEL_H_
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class ClickableLabel : public QLabel {
	Q_OBJECT
public:
	explicit ClickableLabel(QWidget* parent = nullptr)
		: QLabel(parent)
	{
		setCursor(Qt::PointingHandCursor);
	}

signals:
	void clicked();

protected:
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
