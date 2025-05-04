#include "LessonEntry.h"
#include <QMessageBox>

LessonEntry::LessonEntry(QWidget* parent, Lesson* lesson)
	: QWidget(parent), lesson_(lesson)
{
	ui.setupUi(this);
	ui.day->setTextFormat(Qt::PlainText);
	ui.time->setTextFormat(Qt::PlainText);
	ui.address->setTextFormat(Qt::PlainText);

	ui.day->setText(QString::fromStdString(weekday_to_string(lesson_->get_day())));
	ui.time->setText(QString::fromStdString(lesson_->get_time().get_time_string()));
	ui.address->setText(QString::fromStdString(lesson_->get_address().get_address()));

	connect(ui.remove_button, &QPushButton::clicked, this, [this]() { emit removeRequested(lesson_); });
	connect(ui.view_button, &QPushButton::clicked, this, [this]() { emit viewRequested(lesson_); });
	connect(ui.address, &ClickableLabel::clicked, this, &LessonEntry::address_clicked);
}

void LessonEntry::address_clicked()
{
	if (lesson_->get_address().get_address().empty())
	{
		QMessageBox::warning(this, "No Email", "No email address available.");
		return;
	}
	if (!lesson_->get_address().copy())
	{
		QMessageBox::warning(this, "Copy Failed", "Failed to copy email to clipboard.");
	}
	else
	{
		QMessageBox::information(this, "Email Copied", "Email copied to clipboard: " + QString::fromStdString(lesson_->get_address().get_address()));
	}
}

LessonEntry::~LessonEntry()
{
}