#pragma once

#include <QWidget>
#include "ui_ChildLabel.h"
#include "Person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChildLabelClass; };
QT_END_NAMESPACE

class ChildLabel : public QWidget
{
	Q_OBJECT

signals:
	void childClicked(Child* child);

public:
	ChildLabel(QWidget* parent, Child* child);
	~ChildLabel();

private:
	Ui::ChildLabelClass ui;
	Child* child_;
};
