#ifndef DATABASEGUI_H
#define DATABASEGUI_H
#include <QMainWindow>
#include "ui_DataBaseGUI.h"
#include "ChildEntry.h"
#include "DataBase.h"

class DataBaseGUI : public QMainWindow
{
	Q_OBJECT

public:
	DataBaseGUI(QWidget* parent = nullptr);
	~DataBaseGUI();

private:
	Ui::DataBaseGUIClass ui;

	Database data_base_;

	void populateChildrenTab(const std::vector<Child*>& children);
};

#endif // DATABASEGUI_H