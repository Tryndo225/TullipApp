#include "ChildCheckBox.h"

ChildCheckBox::ChildCheckBox(QWidget* parent, Child* child, bool checked)
	: QWidget(parent), child_(child)
{
	ui.setupUi(this);
	ui.child_checkBox->setText(QString::fromStdString(child_->get_name() + " " + child_->get_surname()));
	ui.child_checkBox->setChecked(checked);
}

bool ChildCheckBox::is_checked()
{
	return ui.child_checkBox->isChecked();
}

Child* ChildCheckBox::get_child()
{
	return child_;
}

ChildCheckBox::~ChildCheckBox()
{
}