#ifndef CHILDCHECKBOX_H_
#define CHILDCHECKBOX_H_

#include <QWidget>
#include "ui_ChildCheckBox.h"
#include "Person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChildCheckBoxClass; };
QT_END_NAMESPACE

class ChildCheckBox : public QWidget
{
	Q_OBJECT

public:
	ChildCheckBox(QWidget* parent, Child* child, bool checked);
	bool is_checked();
	Child* get_child();
	~ChildCheckBox();

private:
	Ui::ChildCheckBoxClass ui;
	Child* child_;
};

#endif // CHILDCHECKBOX_H_