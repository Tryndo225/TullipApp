#include "LessonView.h"
#include "PersonLabel.h"
#include "DateTime.h"
#include <QMessageBox>
#include "Attendance.h"

LessonView::LessonView(Lesson* lesson, Database& database)
	: QWidget(nullptr), lesson_(lesson), database_(database)
{
	ui.setupUi(this);
	ui.day_label->setText(QString::fromStdString(weekday_to_string(lesson_->get_day())));
	ui.time_label->setText(QString::fromStdString(lesson_->get_time().get_time_string()));
	ui.address_label->setText(QString::fromStdString(lesson_->get_address().get_address()));
	
	connect(ui.edit_button, &QPushButton::clicked, this, &LessonView::edit_lesson);
	connect(ui.attendance_button, &QPushButton::clicked, this, &LessonView::attendace);
	connect(ui.address_label, &ClickableLabel::clicked, this, &LessonView::address_clicked);

	populate_children();
	populate_employees();
}

void LessonView::address_clicked()
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

void LessonView::populate_children()
{
	for (const auto& child : lesson_->get_children())
	{
		auto* child_label = new PersonLabel(ui.children_scroll_contents, child);
		connect(child_label, &PersonLabel::childClicked, this, [this](Child* child_ptr) { emit childClicked(child_ptr); });
		ui.children_scroll_contents->layout()->addWidget(child_label);
	}
}

void LessonView::populate_employees()
{
	for (const auto& employee : lesson_->get_employees())
	{
		auto* employee_label = new PersonLabel(ui.employees_scroll_contents, employee);
		connect(employee_label, &PersonLabel::employeeClicked, this, [this](Employee* employee_ptr) { emit employeeClicked(employee_ptr); });
		ui.employees_scroll_contents->layout()->addWidget(employee_label);
	}
}

void LessonView::clear_children()
{
	QLayoutItem* item;
	while ((item = ui.children_scroll_contents->layout()->takeAt(0)) != nullptr)
	{
		QWidget* widget = item->widget();
		if (widget)
		{
			widget->setParent(nullptr);
			delete widget;
		}
	}
}

void LessonView::clear_employees()
{
	QLayoutItem* item;
	while ((item = ui.employees_scroll_contents->layout()->takeAt(0)) != nullptr)
	{
		QWidget* widget = item->widget();
		if (widget)
		{
			widget->setParent(nullptr);
			delete widget;
		}
	}
}

void LessonView::edit_lesson()
{
	database_.update_lesson_start(lesson_);
	
	LessonDialog lesson_dialog(lesson_, database_, this);

	if (lesson_dialog.exec() == QDialog::Accepted)
	{
		database_.update_lesson_end(lesson_);
		ui.day_label->setText(QString::fromStdString(weekday_to_string(lesson_->get_day())));
		ui.time_label->setText(QString::fromStdString(lesson_->get_time().get_time_string()));
		ui.address_label->setText(QString::fromStdString(lesson_->get_address().get_address()));
		clear_children();
		clear_employees();
		populate_children();
		populate_employees();

		emit lessonEdited();
	}
	else
	{
		database_.update_lesson_end(lesson_);
	}
}

void LessonView::attendace()
{
	Attendance attendance(this, lesson_);
	connect(&attendance, &Attendance::employeeClicked, this, [this](Employee* employee_ptr) { emit employeeClicked(employee_ptr); });
	attendance.exec();
}

LessonView::~LessonView()
{
	clear_children();
	clear_employees();
}
