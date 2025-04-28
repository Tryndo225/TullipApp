#ifndef CHILDENTRY_H
#define CHILDENTRY_H

#include <QWidget>
#include "ui_ChildEntry.h"

#include "Person.h"

class ChildEntry : public QWidget
{
	Q_OBJECT

public:
	ChildEntry(QWidget* parent, Child* child);
	~ChildEntry();

private:
	Ui::ChildEntryClass ui;
};

#endif // CHILDENTRY_H
