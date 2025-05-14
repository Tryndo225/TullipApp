/**
 * @file Lesson.h
 * @brief Defines the Lesson class, which represents a lesson with its associated details.
 * @details This file contains the declaration of the Lesson class, which includes attributes
 *          such as schedule, location, participating children, employees, and attendance records.
 *          It provides methods to manage and retrieve this information.
 */

#ifndef LESSON_H_
#define LESSON_H_

#include <vector>
#include <utility>
#include <map>
#include <optional>
#include "DateTime.h"
#include "Person.h"
#include "Helper_Functions.h"

 /**
  * @class Lesson
  * @brief Represents a lesson.
  * @details The Lesson class encapsulates information about a lesson, including its schedule, location,
  *          participating children, employees, and attendance records. It provides methods to manage
  *          children, employees, and attendance, as well as to retrieve and update lesson details.
  */
class Lesson
{
private:
    Schedule schedule_; ///< The schedule of the lesson, including day and time.
    Address address_; ///< The address where the lesson takes place.
    std::map<Child*, std::optional<Date>> children_; ///< A map of children and their payment status (optional date of payment).
    std::vector<Employee*> employees_; ///< A list of employees participating in the lesson.
    std::map<Date, std::vector<Child*>> attendance_; ///< A map of attendance records, with dates as keys and vectors of children as values.

public:
    /**
     * @brief Default constructor.
     * @details Initializes a Lesson object with default values.
     */
    Lesson() = default;

    /**
     * @brief Constructs a Lesson with the given attributes.
     * @param schedule The schedule of the lesson (day and time).
     * @param address The address where the lesson takes place.
     * @param children A map of children and their payment status (optional). Defaults to an empty map.
     */
    Lesson(const Schedule& schedule, const Address& address, const std::map<Child*, std::optional<Date>>& children = {});

    /**
     * @brief Constructs a Lesson with the given attributes (rvalue).
     * @param schedule The schedule of the lesson (rvalue).
     * @param address The address where the lesson takes place (rvalue).
     * @param children A map of children and their payment status (optional, rvalue). Defaults to an empty map.
     */
    Lesson(Schedule&& schedule, std::string&& address, std::map<Child*, std::optional<Date>>&& children = {});

    // Rule of 5
    Lesson(const Lesson& lesson) = default;
    Lesson(Lesson&& lesson) noexcept = default;
    Lesson& operator=(const Lesson& lesson) = default;
    Lesson& operator=(Lesson&& lesson) noexcept = default;

    /**
     * @brief Equality operator.
     * @details Compares two Lesson objects for equality based on their attributes.
     * @param lesson The Lesson object to compare with.
     * @retval true If all attributes are equal.
     * @retval false Otherwise.
     */
    inline bool operator==(const Lesson& lesson) const { return schedule_ == lesson.schedule_ && address_ == lesson.address_ && children_ == lesson.children_; }

	// Schedule Management
    /**
	 * @brief Gets the schedule of the lesson.
	 * @return A constant reference to the Schedule object.
	 */
    inline const Schedule& get_schedule() const { return schedule_; }

	/**
	 * @brief Sets the schedule of the lesson.
	 * @param schedule The new schedule of the lesson (rvalue).
	 */
    inline void set_schedule(const Schedule& schedule) { schedule_ = schedule; }

    /**
     * @brief Gets the time of the lesson.
     * @return A constant reference to the Time object.
     */
    inline const Time get_time() const { return schedule_.get_time(); }

    /**
     * @brief Sets the time of the lesson.
     * @param time The new time of the lesson.
     */
    inline void set_time(const Time& time) { schedule_.set_time(time); }

    /**
     * @brief Gets the day of the lesson.
     * @return The day of the week as a WeekDays enum.
     */
    inline const WeekDays get_day() const { return schedule_.get_day(); }

    /**
     * @brief Sets the day of the lesson.
     * @param day The new day of the lesson (rvalue).
     */
    inline void set_day(WeekDays&& day) { schedule_.set_day(day); }

	/// Address Management
    /**
     * @brief Gets the address of the lesson.
     * @return A constant reference to the Address object.
     */
    inline const Address& get_address() const { return address_; }

    /**
     * @brief Sets the address of the lesson.
     * @param address The new address of the lesson (rvalue).
     */
    inline void set_address(Address&& address) { address_ = std::forward<Address>(address); }

    // Employee Management
    /**
     * @brief Gets the list of employees participating in the lesson.
     * @return A vector of pointers to Employee objects.
     */
    const std::vector<Employee*> get_employees() const;

    /**
     * @brief Adds an employee to the lesson.
     * @param employee A pointer to the Employee object to add.
     */
    inline void add_employee(Employee* employee) { employees_.push_back(employee); }

    /**
     * @brief Removes an employee from the lesson.
     * @param employee A pointer to the Employee object to remove.
     */
    void remove_employee(Employee* employee);

    // Child Management
    /**
     * @brief Gets the list of children participating in the lesson.
     * @return A vector of pointers to Child objects.
     */
    const std::vector<Child*> get_children() const;

    /**
     * @brief Adds a child to the lesson.
     * @param child A pointer to the Child object to add.
     */
    inline void add_child(Child* child) { children_.insert({ child, std::nullopt }); }

    /**
     * @brief Removes a child from the lesson.
     * @param child A pointer to the Child object to remove.
     */
    inline void remove_child(Child* child) { children_.erase(child); }

    /**
     * @brief Gets the list of children based on their payment status.
     * @param payed Indicates whether to retrieve children who have paid (true) or not paid (false).
     * @return A vector of pointers to Child objects matching the payment status.
     */
    const std::vector<Child*> get_children_payment(bool payed) const;

    /**
     * @brief Marks a child as having paid for the lesson.
     * @details Sets the payment date for the specified child to the current date.
     * @param child A pointer to the Child object to mark as paid.
     */
    inline void set_child_to_payed(Child* child) { children_[child] = Date::get_current_date(); }

    /**
     * @brief Gets the payment date of a child.
     * @param child A pointer to the Child object.
     * @return The payment date of the child.
     */
    inline Date get_child_payment_date(Child* child) const { return children_.at(child).value_or(Date()); }

    /**
     * @brief Sets the payment date of a child.
     * @param child A pointer to the Child object.
     * @param date The date of payment.
     */
    inline void set_child_payment_date(Child* child, Date date) { children_[child] = date; }

    // Attendance Management
    /**
     * @brief Gets the list of children who attended the lesson on a specific date.
     * @param date The date of the lesson.
     * @return A vector of pairs containing pointers to Child objects and their attendance status (true for present, false for absent).
     */
    const std::map<Child*, bool> get_attendance(const Date& date);

	/**
	 * @brief Gets the attendance records for all dates.
	 * @return A map of dates and vectors of pointers to Child objects who attended on those dates.
	 */
	inline std::map<Date, std::vector<Child*>> get_all_attendance() const { return attendance_; }

    /**
     * @brief Sets the attendance of children for a specific date.
     * @details If it is a new date, it increments employees' hours.
     * @param date The date of the lesson.
     * @param children A vector of pointers to Child objects to mark as present.
     */
    void set_attendance(const Date& date, const std::vector<Child*>& children);

	/**
	 * @brief Sets the attendance records for all dates.
	 * @param attendance A map of dates and vectors of pointers to Child objects who attended on those dates.
	 */
	void set_all_attendance(std::map<Date, std::vector<Child*>>&& attendance){ attendance_ = std::move(attendance); }

    /**
     * @brief Sets the attendance of a child for a specific date.
     * @param date The date of the lesson.
     * @param child A pointer to the Child object to mark as present.
     */
    void set_present(const Date& date, Child* child);

    /**
     * @brief Sets a child as absent for a specific date.
     * @param date The date of the lesson.
     * @param child A pointer to the Child object to mark as absent.
     */
    void set_absent(const Date& date, Child* child);

    /**
     * @brief Destructor.
     * @details Cleans up resources used by the Lesson object.
     */
    ~Lesson() = default;

    /**
     * @brief Outputs the Lesson object to a stream.
     * @param stream The output stream.
     * @param lesson The Lesson object to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& stream, const Lesson& lesson);
};

#endif // !LESSON_H_
