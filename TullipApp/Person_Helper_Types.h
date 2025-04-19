#ifndef PERSON_HELPER_TYPES_H_
#define PERSON_HELPER_TYPES_H_

#include <string>

class Contacts
{
protected:
	static bool copy_to_clipboard(const std::string& text);
};


class Email : public Contacts
{
private:
	std::string email_;
public:
	Email(const std::string& email);
	Email(std::string&& email);

	Email(const Email& email) = default;
	Email(Email&& email) noexcept = default;

	Email& operator=(const Email& email) = default;
	Email& operator=(Email&& email) noexcept = default;

	inline const std::string& get_email() const { return email_; }
	inline void set_email(std::string&& email) { email_ = std::forward<std::string>(email); }

	inline bool copy() const { return copy_to_clipboard(email_); }

	friend std::ostream& operator<<(std::ostream& stream, const Email& email);

	~Email() = default;
};

class Phone : public Contacts
{
private:
	std::string phone_;
public:
	Phone(const std::string& phone);
	Phone(std::string&& phone);

	Phone(const Phone& phone) = default;
	Phone(Phone&& phone) noexcept = default;

	Phone& operator=(const Phone& phone) = default;
	Phone& operator=(Phone&& phone) noexcept = default;

	inline const std::string& get_phone() const { return phone_; }
	inline void set_phone(std::string&& phone) { phone_ = std::forward<std::string>(phone); }

	inline bool copy() const { return copy_to_clipboard(phone_); }

	friend std::ostream& operator<<(std::ostream& stream, const Phone& phone);

	~Phone() = default;
};

#endif // !PERSON_HELPER_TYPES_H_
