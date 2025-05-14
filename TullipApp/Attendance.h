#ifndef ATTENDANCE_H_
#define ATTENDANCE_H_

#include <QDialog>
#include "ui_Attendance.h"
#include "Lesson.h"
#include "Database.h"


class Attendance : public QDialog
{
	Q_OBJECT

signals:
	void employeeClicked(Employee* employee);

public:
	Attendance(QWidget *parent, Lesson* lesson);
	void accept() override;
	~Attendance();

private:
	Ui::AttendanceClass ui;
	Lesson* lesson_;
	Date old_date_;
	std::map<Date, std::vector<Child*>> updated_attendance_;

	void populate_employees();
	void populate_children(Date date_selected);

	void gather_children_attendance(Date date_selected);

	void clear_employees();
	void clear_children();

	void calendar_changed();
};


#endif // ATTENDANCE_H_