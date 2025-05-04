#ifndef CHILDDIALOG_H
#define CHILDDIALOG_H

#include <QDialog>
#include "Person.h"
#include "DataBase.h"
#include "ui_ChildDialog.h"

class ChildDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ChildDialog(QWidget* parent, Child* child, Database& database);

	void accept() override;

	~ChildDialog() = default;

private:
	Child* child_;
	Database& database_;
	Parent* past_mom_;
	Parent* past_dad_;

	Ui::ChildDialogClass ui;

	void set_parents();
	void populate_parents(std::multimap<std::string, Parent*>);
};

#endif // CHILDDIALOG_H