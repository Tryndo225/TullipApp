#ifndef SCALABLELABEL_H_
#define SCALABLELABEL_H_
#include <QLabel>
#include <QResizeEvent>
#include <QFontMetrics>

class ScalableLabel : public QLabel {
	Q_OBJECT
public:
	using QLabel::QLabel;

protected:
	void resizeEvent(QResizeEvent* ev) override
	{
		QLabel::resizeEvent(ev);
		adjustFontSize();
	}

private:
	void adjustFontSize()
	{
		if (text().isEmpty()) return;

		int width = contentsRect().width();
		int height = contentsRect().height();

		QFont font_v = font();
		int low = 1, high = 200;

		while (low < high) {
			int mid = (low + high + 1) / 2;
			font_v.setPointSize(mid);
			QFontMetrics fm(font_v);
			QRect r = fm.boundingRect(contentsRect(), alignment(), text());
			if (r.width() <= width && r.height() <= height)
				low = mid;
			else
				high = mid - 1;
		}
		font_v.setPointSize(low);
		setFont(font_v);
	}
};

#endif // SCALABLELABEL_H_
