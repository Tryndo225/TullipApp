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
	DataBaseGUI(Database&& database, QWidget* parent = nullptr);
	~DataBaseGUI();

private:
	Ui::DataBaseGUIClass ui;

	Database data_base_;

	void populate_children_tab(const std::vector<Child*>& children);

	template<typename T>
	void populate_children_tab(const std::multimap<T, Child*>& children);

	void children_tab_clear();
};

#endif // DATABASEGUI_H