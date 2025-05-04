#include "DateTime.h"
#include <QApplication>
#include <QStyleFactory>
#include "DataBaseGUI.h"

int main(int argc, char* argv[])
{
	std::cout << DateTime::get_current_datetime() << std::endl;

	QApplication app(argc, argv);

	// 1) Tell Qt to use the Fusion style
	app.setStyle(QStyleFactory::create("Fusion"));

	// 2) Build a dark palette
	QPalette dark;
	dark.setColor(QPalette::Window, QColor(53, 53, 53));
	dark.setColor(QPalette::WindowText, Qt::white);
	dark.setColor(QPalette::Base, QColor(25, 25, 25));
	dark.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	dark.setColor(QPalette::ToolTipBase, Qt::white);
	dark.setColor(QPalette::ToolTipText, Qt::white);
	dark.setColor(QPalette::Text, Qt::white);
	dark.setColor(QPalette::Button, QColor(53, 53, 53));
	dark.setColor(QPalette::ButtonText, Qt::white);
	dark.setColor(QPalette::BrightText, Qt::red);
	dark.setColor(QPalette::Link, QColor(42, 130, 218));
	dark.setColor(QPalette::Highlight, QColor(42, 130, 218));
	dark.setColor(QPalette::HighlightedText, Qt::black);

	app.setPalette(dark);

	// (Optional) if you want tooltip backgrounds to match:
	app.setStyleSheet("QToolTip { background-color: #353535; color: white; border: none; }");

	Database database;
	// Populate the database with some data
	// Populate the database with some child data
	//database.add_child(Child("John", "Doe", Date(1, 1, 2000), nullptr, nullptr));
	//database.add_child(Child("Jane", "Smith", Date(2, 2, 2001), nullptr, nullptr));
	//database.add_child(Child("Alice", "Johnson", Date(3, 3, 2002), nullptr, nullptr));
	//database.add_child(Child("Bob", "Brown", Date(4, 4, 2003), nullptr, nullptr));
	//database.add_child(Child("Charlie", "Davis", Date(5, 5, 2004), nullptr, nullptr));
	//database.add_child(Child("Eve", "Wilson", Date(6, 6, 2005), nullptr, nullptr));
	//database.add_child(Child("Frank", "Garcia", Date(7, 7, 2006), nullptr, nullptr));
	//database.add_child(Child("Grace", "Martinez", Date(8, 8, 2007), nullptr, nullptr));
	//database.add_child(Child("Hank", "Lopez", Date(9, 9, 2008), nullptr, nullptr));
	//database.add_child(Child("Ivy", "Gonzalez", Date(10, 10, 2009), nullptr, nullptr));
	//database.add_child(Child("Jack", "Hernandez", Date(11, 11, 2010), nullptr, nullptr));
	//database.add_child(Child("Kathy", "Clark", Date(12, 12, 2011), nullptr, nullptr));
	//database.add_child(Child("Leo", "Rodriguez", Date(13, 1, 2012), nullptr, nullptr));
	//database.add_child(Child("Mia", "Lewis", Date(14, 2, 2013), nullptr, nullptr));
	//database.add_child(Child("Nina", "Walker", Date(15, 3, 2014), nullptr, nullptr));
	//database.add_child(Child("Oscar", "Hall", Date(16, 4, 2015), nullptr, nullptr));
	//database.add_child(Child("Pam", "Allen", Date(17, 5, 2016), nullptr, nullptr));
	//database.add_child(Child("Paul", "Allen", Date(17, 5, 2016), nullptr, nullptr));
	//database.add_child(Child("Quinn", "Young", Date(18, 6, 2017), nullptr, nullptr));
	//database.add_child(Child("Rita", "King", Date(19, 7, 2018), nullptr, nullptr));
	//database.add_child(Child("Sam", "Wright", Date(20, 8, 2019), nullptr, nullptr));
	//database.add_child(Child("Tina", "Scott", Date(21, 9, 2020), nullptr, nullptr));
	//database.add_child(Child("Uma", "Green", Date(22, 10, 2021), nullptr, nullptr));

	//// Populate the database with some parent data
	//database.add_parent(Parent("Sara", "Alic-Ekinovic", 1, "alicsara3012@gmail.com"));
	//database.add_parent(Parent("Michael", "Smith", 0, "michael.smith@example.com"));
	//database.add_parent(Parent("Sarah", "Johnson", 1, "sarah.johnson@example.com"));
	//database.add_parent(Parent("David", "Williams", 0, "david.williams@example.com"));
	//database.add_parent(Parent("Emily", "Brown", 1, "emily.brown@example.com"));
	//database.add_parent(Parent("James", "Jones", 0, "james.jones@example.com"));
	//database.add_parent(Parent("Olivia", "Garcia", 1, "olivia.garcia@example.com"));
	//database.add_parent(Parent("Robert", "Martinez", 0, "robert.martinez@example.com"));
	//database.add_parent(Parent("Sophia", "Hernandez", 1, "sophia.hernandez@example.com"));
	//database.add_parent(Parent("William", "Lopez", 0, "william.lopez@example.com"));
	//database.add_parent(Parent("Isabella", "Gonzalez", 1, "isabella.gonzalez@example.com"));

	DataBaseGUI mainWindow(std::move(database));
	mainWindow.show();

	return app.exec();
}