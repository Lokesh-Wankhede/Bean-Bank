// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The User class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh


#pragma once

#include <string>
#include "Account.h"

using std::string;

// Gender: 1- Male, 2- Female, 3- Other
enum class GenderT { Male = 1, Female = 2, Other = 3 };

class User : public Account
{
public:

	User() = default;

	/**
	 * \brief Creates the user object.
	 * \param firstName first name
	 * \param lastName last name
	 * \param age age
	 * \param phoneNo 10 digit phone number
	 * \param userId unique Id
	 * \param userPassword 7 digit number
	 * \param gender gender
	 * \param address address
	 */
	explicit User(const string& firstName, const string& lastName,
		int age, unsigned long long phoneNo, int userId, int userPassword,
		GenderT gender, const string& address);

	/**
	* \brief Checks for illegal characters in name.
	*
	* \param name name to validate
	* \return true if name is valid, false otherwise.
	*/
	static auto ValidateName(const string& name) -> bool;

	/**
	* \brief Checks for the illegal characters in address.
	*
	* \param address address to validate
	* \return true if address is valid, false otherwise.
	*/
	static auto ValidateAddress(const string& address) -> bool;

	/**
	* \brief Validates the age. Age must be from 18 to 200 years.
	*
	* \param age age to validate
	* \return true if age is valid, false otherwise.
	*/
	static auto ValidateAge(int age) -> bool;

	/**
	* \brief Validates the phone number by standard regex.
	*
	* \param phoneNumber 10 digit number to validate
	* \return true if phone number valid, false otherwise.
	*/
	[[nodiscard("Please handle the return value.")]] auto ValidatePhoneNumber
	(unsigned long long phoneNumber) const -> bool;

	/**
	* \brief Validates userId. It must in be between 1 to 50000.
	*
	* \param userId id of the user
	* \return true if userId is valid, false otherwise.
	*/
	static auto ValidateUserId(int userId) -> bool;

	/**
	* \brief Validates the user password. it must be 7 digit number.
	 *
	 * \param password 7 digit number
	 * \return true if password is valid, false otherwise.
	 */
	static auto ValidateUserPassword(int password) -> bool;

	friend auto operator<<(std::ofstream& ofs, const User& user)->std::ofstream&;

	friend auto operator>>(std::ifstream& ifs, const User& user)->std::ifstream&;


#pragma region Setters and Getters

	static auto GetTotalUsers() -> unsigned int;
	static auto AddUser() -> void;
	static auto RemoveUser() -> void;

	auto SetFirstName(const string& name) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetFirstName() const->string;

	auto SetLastName(const string& name) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetLastName() const->string;

	auto SetAddress(const string& address) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetAddress() const->string;

	auto SetGender(GenderT gender) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetGender() const->GenderT;

	auto SetAge(int age) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetAge() const -> int;

	auto SetPhoneNumber(unsigned long long number) -> bool;

	[[nodiscard("Please handle the return value.")]] auto
		GetPhoneNumber() const -> unsigned long long;

	auto SetUserId(int userId) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetUserId() const -> int;

	auto SetUserPassword(int password) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetUserPassword() const -> int;

#pragma endregion

private:
	GenderT MGender{};
	string MFirstName{}, MLastName{}, MAddress{};
	int MAge{}, MUserId{}, MUserPassword{};
	unsigned long long MPhoneNumber{};
	// Total number of users in the bank.
	static unsigned int TotalUsers;
};
