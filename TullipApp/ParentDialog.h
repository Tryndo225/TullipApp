#ifndef PARENTDIALOG_H_
#define PARENTDIALOG_H_

#include <QDialog>
#include "ui_ParentDialog.h"
#include "Person.h"
#include "Database.h"
#include "ChildCheckBox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ParentDialogClass; };
QT_END_NAMESPACE

class ParentDialog : public QDialog
{
	Q_OBJECT

public:
	ParentDialog(QWidget* parent_class, Parent* parent, Database& database);
	void populate_children(const std::multimap<std::string, Child*>& children);
	void accept() override;
	~ParentDialog();

private:
	Ui::ParentDialogClass ui;
	Database& database_;
	Parent* database_parent_;
};

#endif // PARENTDIALOG_H_
