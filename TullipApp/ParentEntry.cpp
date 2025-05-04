#include "ParentEntry.h"
#include <QMessageBox>

ParentEntry::ParentEntry(QWidget* parent, Parent* database_parent)
	: QWidget(parent), database_parent_(database_parent)
{
	ui.setupUi(this);
	ui.name->setTextFormat(Qt::PlainText);
	ui.surname->setTextFormat(Qt::PlainText);
	ui.email->setTextFormat(Qt::PlainText);
	ui.gender->setTextFormat(Qt::PlainText);
	setup_parent();
}

void ParentEntry::setup_parent()
{
	ui.name->setText(QString::fromStdString(database_parent_->get_name()));
	ui.surname->setText(QString::fromStdString(database_parent_->get_surname()));
	ui.email->setText(QString::fromStdString(database_parent_->get_email().get_email()));
	ui.gender->setText(database_parent_->is_mother() ? "Mother" : "Father");

	connect(ui.edit_button, &QPushButton::clicked, this, [this]() { emit editRequested(database_parent_); });
	connect(ui.remove_button, &QPushButton::clicked, this, [this]() { emit removeRequested(database_parent_); });
	connect(ui.email, &ClickableLabel::clicked, this, &ParentEntry::email_clicked);

	for (auto& child : database_parent_->get_children())
	{
		auto* child_label = new ChildLabel(ui.children_contents, child);
		connect(child_label, &ChildLabel::childClicked, this, [this](Child* child_ptr) { emit childSearchRequested(child_ptr); });
		ui.children_contents->layout()->addWidget(child_label);
	}
}

void ParentEntry::email_clicked()
{
	if (database_parent_->get_email().get_email().empty())
	{
		QMessageBox::warning(this, "No Email", "No email address available.");
		return;
	}
	if (!database_parent_->get_email().copy())
	{
		QMessageBox::warning(this, "Copy Failed", "Failed to copy email to clipboard.");
	}
	else
	{
		QMessageBox::information(this, "Email Copied", "Email copied to clipboard: " + QString::fromStdString(database_parent_->get_email().get_email()));
	}
}

ParentEntry::~ParentEntry()
{
	// Clean up the children labels
	QLayoutItem* item;
	while ((item = ui.children_contents->layout()->takeAt(0)) != nullptr)
	{
		QWidget* widget = item->widget();
		if (widget)
		{
			widget->setParent(nullptr);
			delete widget;
		}
		delete item;
	}
}