#include "Attendance.h"
#include "PersonLabel.h"
#include "PersonCheckBox.h"

Attendance::Attendance(QWidget *parent, Lesson* lesson)
	: QDialog(parent), lesson_(lesson)
{
	ui.setupUi(this);

	setWindowTitle(tr("Attendance"));

	ui.weekday->setText(QString::fromStdString(weekday_to_string(lesson_->get_day())));
	ui.timeofday->setText(QString::fromStdString(std::format("{:02}", lesson_->get_time().get_hours()) + ':' + std::format("{:02}", lesson_->get_time().get_minutes())));
	ui.calendarWidget->setSelectedDate(QDate::currentDate());

	updated_attendance_ = lesson_->get_all_attendance();
	old_date_ = Date(ui.calendarWidget->selectedDate().day(), ui.calendarWidget->selectedDate().month(), ui.calendarWidget->selectedDate().year());

	connect(ui.calendarWidget, &QCalendarWidget::selectionChanged, this, &Attendance::calendar_changed);

	populate_employees();
	populate_children(old_date_);
}

void Attendance::accept()
{
	gather_children_attendance(old_date_);
	lesson_->set_all_attendance(std::move(updated_attendance_));
	QDialog::accept();
}

void Attendance::calendar_changed()
{
	auto selected_date = ui.calendarWidget->selectedDate();
	auto date = Date(selected_date.day(), selected_date.month(), selected_date.year());
	if (old_date_ != date)
	{
		gather_children_attendance(old_date_);
		populate_children(date);
		old_date_ = date;
	}
}

void Attendance::populate_employees()
{
	for (const auto& employee : lesson_->get_employees())
	{
		auto* employee_label = new PersonLabel(this, employee);
		connect(employee_label, &PersonLabel::employeeClicked, this, [this](Employee* employee_ptr) { emit employeeClicked(employee_ptr); });
		ui.employees_scroll_contents->layout()->addWidget(employee_label);
	}
}

void Attendance::populate_children(Date date_selected)
{
	clear_children();

	int row = 0;
	int column = 0;

	auto* layout = qobject_cast<QGridLayout*>(ui.children_scroll_contents->layout());


	for (const auto& child : lesson_->get_children())
	{
		auto* child_checkbox = new PersonCheckBox(this, child, contains(updated_attendance_[date_selected], child));
		/*child_checkbox->setStyleSheet(R"(
			QCheckBox::indicator 
			{ 
				width: 20px; 
				height: 20px; 
			}
			QCheckBox 
			{
				font-size: 18px;
				font-weight: bold;
				border: 2px solid;
			})");*/
		layout->addWidget(child_checkbox, row, column);
		++column;
		if (column >= 3)
		{
			column = 0;
			++row;
		}
	}
}

void Attendance::gather_children_attendance(Date date_selected)
{
	while (auto item = ui.children_scroll_contents->layout()->takeAt(0))
	{
		auto* widget = item->widget();
		if (widget)
		{
			auto* child_checkbox = qobject_cast<PersonCheckBox*>(widget);
			if (child_checkbox)
			{
				auto child = child_checkbox->get_child();
				if (child_checkbox->is_checked())
				{
					updated_attendance_[date_selected].push_back(child);
				}
				else
				{
					remove_all(updated_attendance_[date_selected], child);
					if (updated_attendance_[date_selected].empty())
					{
						updated_attendance_.erase(date_selected);
					}
				}
			}
			delete widget;
		}
	}
}

void Attendance::clear_children()
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

void Attendance::clear_employees()
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

Attendance::~Attendance()
{
	clear_children();
	clear_employees();
}
