#include "DateTime.h"
#include <QApplication>
#include <QStyleFactory>
#include "DataBaseGUI.h"

/**
 * @mainpage Tullip App Documentation
 *
 * @tableofcontents
 *
 * @section intro_sec Introduction
 * Tullip App is a Qt-based desktop application for managing a simple
 * database of Children, Parents, and Employees. It provides a tabbed
 * interface, powerful sorting and searching, import/export via CSV,
 * and automatic quick-save functionality.
 *
 * @section features_sec Key Features
 * - **CRUD Operations**: Create, Read, Update, Delete entries for Children,
 *   Parents, and Employees via intuitive dialogs.
 * - **Tabbed Interface**: Switch between Children, Parents, and Employees modules
 *   using a clear tab structure.
 * - **Advanced Sorting & Filtering**: Click column headers to sort tables;
 *   use the search box to filter by name or surname in real-time.
 * - **Import/Export**: Load and save the entire database to CSV files via
 *   the File menu.
 * - **Automatic Quick-Save**: On application exit, unsaved changes are
 *   written to `autosave.csv` in the working directory.
 *
 * @section ui_overview_sec User Interface Overview
 * - **Menu Bar**:
 *   - `File` → `Save as...`: Saves the current database to CSV. (saves the path for quick-save).
 *   - `File` → `Import...`: Open a CSV to load entries (saves the path for quick-save).
 *   - `File` → `Export...`: Expoty current database to CSV.
 *	 - Exit: Closes the application. (unsaved changes are quick-saved to *path*_quick_save.csv).
 * - **Main Tabs**:
 *   - **Children**: Table of child records.
 *   - **Parents**: Table of parent records.
 *   - **Employees**: Table of employee records.
 *	 - **Lessons**: Table of lesson records.
 * - **Table Controls**:
 *   - **Add**: Opens a dialog to enter a new record.
 *   - **Edit**: Modify the selected record.
 *   - **Remove**: Remove the selected record.
 *	 - **View**: View the selected lesson record.
 *   - **Search Box**: Filter rows by typing part of a name or surname.
 *   - **Sorting ComboBox**: Select sorting method for the table.
 *	 - **Clickable Labels**: Click on a childer labels (when viewing parents) or parent labels (when viewing children) to be taken to the corresponding entry.
 * - **Lesson View Controls**:
 *	 - **Edit**: Opens a dialog to edit the selected lesson.
 *	 - **Attendance**: Opens a dialog to mark attendance for the selected lesson.
 *	 - **Clickable Labels**: Click on a child label or employee label to be taken to the corresponding entry.
 *
 * @section dialogs_sec Data Entry Dialogs
 * Each module (Child, Parent, Employee) has a corresponding dialog for
 * adding or editing records. Common fields include:
 * - **Name** (string)
 * - **Surname** (string)
 * - **Additional Fields**:
 *   - Children: Date of Birth, Parent(s) (Mother, Father)
 *   - Parents: Email, Child(ren)
 *   - Employees: Email, Phone, Hours Worked
 *
 * @section usage_sec How to Operate
 * 1. **Launching**: Run the `TullipApp` executable.
 * 2. **Adding Records**:
 *    - Select the appropriate tab (e.g., Children).
 *    - Click **Add**, fill in fields, and press **OK**.
 * 3. **Editing Records**:
 *    - Select a row and click **Edit**.
 *    - Modify data in the dialog and click **OK**.
 * 4. **Deleting Records**:
 *    - Select one or more rows.
 *    - Click **Remove** on the correspoding record.
 * 5. **Sorting**:
 *    - Select option from the ComboBox.
 * 6. **Searching**:
 *    - Enter text in the search box bellow the table to dynamically filter
 *      records with matching/similar name or surname.
 * 7. **Importing/Exporting**:
 *    - Use `File → Save as...` to save the current database to CSV.
 *    - Use `File → Import...` to select a CSV file matching the data schema.
 *    - Use `File → Export...` to export the current database to CSV.
 * 8. **Quick-Save**:
 *    - On exit, unsaved modifications are automatically written to
 *      `*path*_quick_save.csv`. You may re-import this file on next launch.
 *
 * @section modules_sec Project Structure
 * - **DataBaseGUI**: Main window and signal-slot logic
 *   (@c DataBaseGUI.h/.cpp, @c DataBaseGUI.ui)
 * - **Database**: In-memory storage and CSV serialization
 *   (@c DataBase.h/.cpp)
 * - **Date**: Date handling and validation
 *   (@c DateTime.h/.cpp)
 * - **Time**: Time handling and validation
 *	 (@c DateTime.h/.cpp)
 *	 **DateTime**: Date and time handling
 *   (@c DateTime.h/.cpp)
 * - **Schedule**: Class representing a schedule with weekday and time
 *	 (@c DateTime.h/.cpp)
 * - **DateTime Exceptions**: Custom exceptions for date/time errors
 *   (@c DateTime_Exceptions.h/.cpp)
 * - **Person**: Person base class for Child, Parent, and Employee
 *   (@c Person.h/.cpp)
 * - **Child**: Class representing a child with parents
 *   (@c Person.h/.cpp)
 * - **Parent**: Class representing a parent with children
 *   (@c Person.h/.cpp)
 * - **Employee**: Class representing an employee
 *   (@c Person.h/.cpp)
 * - **Lesson**: Class representing a lesson with schedule, children and employees
 *   (@c Lesson.h/.cpp)
 * - **Address**: Class representing a physical address
 *   (@c Data_Helper_Types.h/.cpp)
 * - **Email**: Class representing an email address
 *   (@c Data_Helper_Types.h/.cpp)
 * - **Phone**: Class representing a phone number
 *   (@c Data_Helper_Types.h/.cpp)
 * - **Helper Functions**: Utility functions
 *	 (@c Helper_Functions.h/.cpp)
 * - **CSV Parser**: Functions for parsing CSV files
 *   (@c DataBase_Parser_Functions.h/.cpp)
 *
 * - **Entries & Dialogs**:
 *   - @c ChildEntry/UI widget & @c ChildDialog
 *   - @c ParentEntry/UI widget & @c ParentDialog
 *   - @c EmployeeEntry/UI widget & @c EmployeeDialog
 *
 * @section build_sec Building and Running
 * @subsection requirements Sub-requirements
 * - Qt 5.x or 6.x
 * - CMake 3.10+
 * - C++17 compiler (e.g., GCC 9+, Clang 10+, MSVC 2019+)
 *
 * @subsection build_steps Build Steps
 * @code{.bash}
 * git clone https://github.com/Tryndo225/TullipApp.git
 * cd repo
 * mkdir build && cd build
 * cmake ..
 * cmake --build .
 * @endcode
 */

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	QFont font("Karla");
	app.setFont(font);

	app.setStyle(QStyleFactory::create("Fusion"));

	Database database;
	////Populate the database with some data
	////Populate the database with some child data
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

	//// Populate the database with some employee data
	//database.add_employee(Employee("Jakub", "Kalisky", "kubo.kalisky@gmail.com", "123456789"));
	//database.add_employee(Employee("Danka", "Rumanovicova", "danka.rumik@gmail.com", "149687321"));
	//database.add_employee(Employee("Anna", "Taylor", "anna.taylor@example.com", "987654321"));
	//database.add_employee(Employee("Brian", "Adams", "brian.adams@example.com", "456123789"));
	//database.add_employee(Employee("Catherine", "Bell", "catherine.bell@example.com", "321654987"));
	//database.add_employee(Employee("Daniel", "Evans", "daniel.evans@example.com", "789456123"));
	//database.add_employee(Employee("Ella", "Foster", "ella.foster@example.com", "654789321"));
	//database.add_employee(Employee("Frank", "Harris", "frank.harris@example.com", "123789456"));
	//database.add_employee(Employee("Grace", "Miller", "grace.miller@example.com", "987321654"));
	//database.add_employee(Employee("Henry", "Moore", "henry.moore@example.com", "456987123"));
	//database.add_employee(Employee("Ivy", "Parker", "ivy.parker@example.com", "789123654"));
	//database.add_employee(Employee("Jack", "Turner", "jack.turner@example.com", "321987456"));

	//// Populate the database with some lesson data
	//database.add_lesson(Lesson(Schedule(WeekDays::Monday, Time(9, 0, 0)), "Ruzomberok"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Tuesday, Time(10, 0, 0)), "Bratislava"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Wednesday, Time(11, 0, 0)), "Kosice"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Thursday, Time(12, 0, 0)), "Nitra"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Friday, Time(13, 0, 0)), "Trnava"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Saturday, Time(14, 0, 0)), "Zilina"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Sunday, Time(15, 0, 0)), "Presov"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Monday, Time(16, 0, 0)), "Poprad"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Tuesday, Time(17, 0, 0)), "Banska Bystrica"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Wednesday, Time(18, 0, 0)), "Trencin"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Thursday, Time(19, 0, 0)), "Piestany"));
	//database.add_lesson(Lesson(Schedule(WeekDays::Friday, Time(20, 0, 0)), "Handlová"));

	DataBaseGUI mainWindow(std::move(database));
	mainWindow.show();

	return app.exec();
}