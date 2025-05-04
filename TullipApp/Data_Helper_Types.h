/**
 * @file Data_Helper_Types.h
 * @brief Defines utility classes for managing contact-related data such as email, phone, and address.
 * @details This file contains the `Contacts` base class and its derived classes: `Email`, `Phone`, and `Address`.
 *          These classes provide functionality for managing and manipulating contact-related data.
 */

#ifndef PERSON_HELPER_TYPES_H_
#define PERSON_HELPER_TYPES_H_

#include <string>

 /**
  * @class Contacts
  * @brief Base class for contact-related utilities.
  * @details Provides common functionality for derived classes such as `Email`, `Phone`, and `Address`.
  *				It defines a method to copy text to the clipboard.
  */
class Contacts
{
protected:
	/**
	 * @brief Copies the given text to the clipboard.
	 * @param text The text to copy to the clipboard.
	 * @return true if the operation was successful, false otherwise.
	 */
	static bool copy_to_clipboard(const std::string& text);
};

/**
 * @class Email
 * @brief Represents an email address.
 * @details Provides functionality to manage and manipulate email addresses.
 * @see Contacts
 */
class Email : public Contacts
{
private:
	std::string email_; ///< The email address.

public:
	/**
	 * @brief Default constructor.
	 */
	Email() = default;

	/**
	 * @brief Constructs an Email object with the given email address.
	 * @param email The email address to initialize with.
	 */
	Email(const std::string& email);

	/**
	 * @brief Constructs an Email object with the given email address (rvalue).
	 * @param email The email address to initialize with.
	 */
	Email(std::string&& email);

	// Rule of 5
	Email(const Email& email) = default;
	Email(Email&& email) noexcept = default;
	Email& operator=(const Email& email) = default;
	Email& operator=(Email&& email) noexcept = default;

	/**
	 * @brief Compares two Email objects for equality.
	 * @param email The Email object to compare with.
	 * @retval true If the email addresses are equal.
	 * @retval false Otherwise.
	 */
	inline bool operator==(const Email& email) const { return email_ == email.email_; }

	/**
	 * @brief Gets the email address.
	 * @return The email address as a constant reference.
	 */
	inline const std::string& get_email() const { return email_; }

	/**
	 * @brief Sets the email address.
	 * @param email The new email address (rvalue).
	 */
	inline void set_email(std::string&& email) { email_ = std::forward<std::string>(email); }

	/**
	 * @brief Copies the email address to the clipboard.
	 * @return true if the operation was successful, false otherwise.
	 */
	inline bool copy() const { return copy_to_clipboard(email_); }

	/**
	 * @brief Outputs the email address to a stream.
	 * @param stream The output stream.
	 * @param email The Email object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Email& email);

	/**
	 * @brief Destructor.
	 */
	~Email() = default;
};

/**
 * @class Phone
 * @brief Represents a phone number.
 * @details Provides functionality to manage and manipulate phone numbers.
 * @see Contacts
 */
class Phone : public Contacts
{
private:
	std::string phone_; ///< The phone number.

public:
	/**
	 * @brief Default constructor.
	 */
	Phone() = default;

	/**
	 * @brief Constructs a Phone object with the given phone number.
	 * @param phone The phone number to initialize with.
	 */
	Phone(const std::string& phone);

	/**
	 * @brief Constructs a Phone object with the given phone number (rvalue).
	 * @param phone The phone number to initialize with.
	 */
	Phone(std::string&& phone);

	// Rule of 5
	Phone(const Phone& phone) = default;
	Phone(Phone&& phone) noexcept = default;
	Phone& operator=(const Phone& phone) = default;
	Phone& operator=(Phone&& phone) noexcept = default;

	/**
	 * @brief Compares two Phone objects for equality.
	 * @param phone The Phone object to compare with.
	 * @retval true If the phone numbers are equal.
	 * @retval false Otherwise.
	 */
	inline bool operator==(const Phone& phone) const { return phone_ == phone.phone_; }

	/**
	 * @brief Gets the phone number.
	 * @return The phone number as a constant reference.
	 */
	inline const std::string& get_phone() const { return phone_; }

	/**
	 * @brief Sets the phone number.
	 * @param phone The new phone number (rvalue).
	 */
	inline void set_phone(std::string&& phone) { phone_ = std::forward<std::string>(phone); }

	/**
	 * @brief Copies the phone number to the clipboard.
	 * @return true if the operation was successful, false otherwise.
	 */
	inline bool copy() const { return copy_to_clipboard(phone_); }

	/**
	 * @brief Outputs the phone number to a stream.
	 * @param stream The output stream.
	 * @param phone The Phone object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Phone& phone);

	/**
	 * @brief Destructor.
	 */
	~Phone() = default;
};

/**
 * @class Address
 * @brief Represents a physical address.
 * @details Provides functionality to manage and manipulate addresses.
 * @see Contacts
 */
class Address : public Contacts
{
private:
	std::string address_; ///< The physical address.

public:
	/**
	 * @brief Default constructor.
	 */
	Address() = default;

	/**
	 * @brief Constructs an Address object with the given address.
	 * @param address The address to initialize with.
	 */
	Address(const std::string& address);

	/**
	 * @brief Constructs an Address object with the given address (rvalue).
	 * @param address The address to initialize with.
	 */
	Address(std::string&& address);

	// Rule of 5
	Address(const Address& address) = default;
	Address(Address&& address) noexcept = default;
	Address& operator=(const Address& address) = default;
	Address& operator=(Address&& address) noexcept = default;

	/**
	 * @brief Compares two Address objects for equality.
	 * @param address The Address object to compare with.
	 * @retval true If the addresses are equal.
	 * @retval false Otherwise.
	 */
	inline bool operator==(const Address& address) const { return address_ == address.address_; }

	/**
	 * @brief Gets the address.
	 * @return The address as a constant reference.
	 */
	inline const std::string& get_address() const { return address_; }

	/**
	 * @brief Sets the address.
	 * @param address The new address (rvalue).
	 */
	inline void set_address(std::string&& address) { address_ = std::forward<std::string>(address); }

	/**
	 * @brief Copies the address to the clipboard.
	 * @return true if the operation was successful, false otherwise.
	 */
	inline bool copy() const { return copy_to_clipboard(address_); }

	/**
	 * @brief Outputs the address to a stream.
	 * @param stream The output stream.
	 * @param address The Address object to output.
	 * @return The output stream.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const Address& address);

	/**
	 * @brief Destructor.
	 */
	~Address() = default;
};

#endif // !PERSON_HELPER_TYPES_H_
