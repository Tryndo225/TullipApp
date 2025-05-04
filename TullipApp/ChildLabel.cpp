#include "ChildLabel.h"

ChildLabel::ChildLabel(QWidget* parent, Child* child)
	: QWidget(parent), child_(child)
{
	ui.setupUi(this);
	ui.name_surname->setTextFormat(Qt::PlainText);
	ui.name_surname->setText(QString::fromStdString(child_->get_name() + " " + child_->get_surname()));
	connect(ui.name_surname, &ClickableLabel::clicked, this, [this]() { emit childClicked(child_); });
}

ChildLabel::~ChildLabel()
{
}