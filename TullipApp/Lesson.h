#ifndef LESSON_H_
#define LESSON_H_

#include <vector>
#include <utility>
#include <map>
#include <optional>
#include "DateTime.h"
#include "Person.h"

class Lesson
{
private:
	Date date_;
	Time time_;
	Address address_;
	std::map<Child*, std::optional<Date>> children_;
	std::vector<Employee*> employees_;

public:
	Lesson(const Date& date, const Time& time, const Address& address, const std::map<Child*, std::optional<Date>>& children = std::map<Child*, std::optional<Date>>());
	Lesson(Date&& date, Time&& time, std::string&& address, std::map<Child*, std::optional<Date>>&& children = std::map<Child*, std::optional<Date>>());

	Lesson(const Lesson& lesson) = default;
	Lesson(Lesson&& lesson) noexcept = default;

	Lesson& operator=(const Lesson& lesson) = default;
	Lesson& operator=(Lesson&& lesson) noexcept = default;

	inline const Date& get_date() const { return date_; }
	inline void set_date(Date&& date) { date_ = std::forward<Date>(date); }

	inline const Time& get_time() const { return time_; }
	inline void set_time(Time&& time) { time_ = std::forward<Time>(time); }

	inline const Address& get_address() const { return address_; }
	inline void set_address(Address&& address) { address_ = std::forward<Address>(address); }

	const std::vector<Child*> get_children() const;
    inline void add_child(Child* child) { children_.insert({child, std::nullopt}); }
	inline void remove_child(Child* child) { children_.erase(child); }

	const std::vector<Child*> get_children_payment(bool payed) const;
	inline void set_child_to_payed(Child* child) { children_[child] = Date::get_current_date(); };

	~Lesson() = default;
};



#endif 