#ifndef PARENTENTRY_H_
#define PARENTENTRY_H_

#include <QWidget>
#include "ui_ParentEntry.h"
#include "Person.h"
#include "ClickableLabel.h"
#include "ChildLabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ParentEntryClass; };
QT_END_NAMESPACE

class ParentEntry : public QWidget
{
	Q_OBJECT

signals:
	void editRequested(Parent* parent);
	void removeRequested(Parent* parent);
	void childSearchRequested(Child* parent);

public:
	ParentEntry(QWidget* parent, Parent* database_parent);
	~ParentEntry();

private:
	Ui::ParentEntryClass ui;
	Parent* database_parent_;
	void setup_parent();
	void email_clicked();
};

#endif // PARENTENTRY_H_
