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
	Email() = default;
	Email(const std::string& email);
	Email(std::string&& email);

	Email(const Email& email) = default;
	Email(Email&& email) noexcept = default;

	Email& operator=(const Email& email) = default;
	Email& operator=(Email&& email) noexcept = default;

	inline bool operator==(const Email& email) const { return email_ == email.email_; }

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
	Phone() = default;
	Phone(const std::string& phone);
	Phone(std::string&& phone);

	Phone(const Phone& phone) = default;
	Phone(Phone&& phone) noexcept = default;

	Phone& operator=(const Phone& phone) = default;
	Phone& operator=(Phone&& phone) noexcept = default;

	inline bool operator==(const Phone& phone) const { return phone_ == phone.phone_; }

	inline const std::string& get_phone() const { return phone_; }
	inline void set_phone(std::string&& phone) { phone_ = std::forward<std::string>(phone); }

	inline bool copy() const { return copy_to_clipboard(phone_); }

	friend std::ostream& operator<<(std::ostream& stream, const Phone& phone);

	~Phone() = default;
};

class Address : public Contacts
{
private:
	std::string address_;
public:
	Address() = default;
	Address(const std::string& address);
	Address(std::string&& address);

	Address(const Address& address) = default;
	Address(Address&& address) noexcept = default;

	Address& operator=(const Address& address) = default;
	Address& operator=(Address&& address) noexcept = default;

	inline bool operator==(const Address& address) const { return address_ == address.address_; }

	inline const std::string& get_address() const { return address_; }
	inline void set_address(std::string&& address) { address_ = std::forward<std::string>(address); }

	inline bool copy() const { return copy_to_clipboard(address_); }

	friend std::ostream& operator<<(std::ostream& stream, const Address& address);

	~Address() = default;
};

#endif // !PERSON_HELPER_TYPES_H_