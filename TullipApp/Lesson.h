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
	DateTime datetime_;
	Address address_;
	std::map<Child*, std::optional<Date>> children_;
	std::vector<Employee*> employees_;

public:
	Lesson() = default;

	Lesson(const DateTime& datetime, const Address& address, const std::map<Child*, std::optional<Date>>& children = std::map<Child*, std::optional<Date>>());
	Lesson(DateTime&& datetime, std::string&& address, std::map<Child*, std::optional<Date>>&& children = std::map<Child*, std::optional<Date>>());

	Lesson(const Lesson& lesson) = default;
	Lesson(Lesson&& lesson) noexcept = default;

	Lesson& operator=(const Lesson& lesson) = default;
	Lesson& operator=(Lesson&& lesson) noexcept = default;

	inline bool operator==(const Lesson& lesson) const { return datetime_ == lesson.datetime_ && address_ == lesson.address_ && children_ == lesson.children_; }

	inline const DateTime& get_datetime() const { return datetime_; }
	inline void set_datetime(const DateTime& datetime) { datetime_ = datetime; }

	inline const Date& get_date() const { return datetime_; }
	inline void set_date(Date&& date) { datetime_.set_date(std::forward<Date>(date)); }

	inline const Time& get_time() const { return datetime_; }
	inline void set_time(Time&& time) { datetime_.set_time(std::forward<Time>(time)); }

	inline const Address& get_address() const { return address_; }
	inline void set_address(Address&& address) { address_ = std::forward<Address>(address); }

	const std::vector<Child*> get_children() const;
	inline void add_child(Child* child) { children_.insert({ child, std::nullopt }); }
	inline void remove_child(Child* child) { children_.erase(child); }

	const std::vector<Child*> get_children_payment(bool payed) const;
	inline void set_child_to_payed(Child* child) { children_[child] = Date::get_current_date(); };

	~Lesson() = default;
};

#endif 