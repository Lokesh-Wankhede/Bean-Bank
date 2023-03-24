// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The User class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh


#pragma once

#ifndef USER_H_
#define USER_H_

#include <fstream>
#include <regex>
#include <string>
#include "Account.h"

using std::string;

// Gender: 1- Male, 2- Female, 3- Other.

enum class GenderT { Male = 1, Female = 2, Other = 3 };

class User : public Account
{
public:

	/**
	 * \brief Creates the user only after verifying the values.
	 * \param firstName First Name of the user
	 * \param lastName Last name of the user
	 * \param age User's age
	 * \param phoneNo Phone number of the user
	 * \param userId Unique Id of user
	 * \param userPassword 7 digit number
	 * \param gender User's gender
	 * \param address User's address
	 */
	explicit User(const string& firstName, const string& lastName,
		int age, unsigned long long phoneNo, int userId, int userPassword,
		GenderT gender, const string& address);

	User() = default;

	/**
	* \brief Checks for illegal characters in name.
	*
	* \param name in string
	* \return True if name is valid, false otherwise.
	*/
	static auto ValidateName(const string& name) -> bool;

	/**
	* \brief Checks for the illegal characters in address.
	*
	* \param address string
	* \return True if address is valid, false otherwise.
	*/
	static auto ValidateAddress(const string& address) -> bool;

	/**
	* \brief Validates the age. Age must be from 18 to 200 years.
	*
	* \param age of the user
	* \return True if age is valid, false otherwise.
	*/
	static auto ValidateAge(int age) -> bool;

	/**
	* \brief Validates the phone number by standard regex.
	*
	* \param phoneNumber 10 digit number
	* \return True if phone number valid, false otherwise.
	*/
	[[nodiscard]] auto ValidatePhoneNumber(unsigned long long phoneNumber) const -> bool;

	/**
	* \brief Validates userId. It must in be between 1 to 50000.
	*
	* \param userId id of the user
	* \return True if userId is valid, false otherwise.
	*/
	static auto ValidateUserId(int userId) -> bool;

	/**
	* \brief Validates the user password. it must be 7 digit number.
	 *
	 * \param password 7 digit number
	 * \return True if password is valid, false otherwise.
	 */
	static auto ValidateUserPassword(int password) -> bool;

	friend auto operator<<(std::ofstream& ofs, const User& user)->std::ofstream&;

	friend auto operator>>(std::ifstream& ifs, const User& user)->std::ifstream&;


#pragma region Accessors and Mutators

	static auto GetTotalUsers() -> unsigned int;
	static auto AddUser() -> void;
	static auto RemoveUser() -> void;

	auto SetFirstName(const string& name) -> bool;

	[[nodiscard]] auto GetFirstName() const->string;

	auto SetLastName(const string& name) -> bool;

	[[nodiscard]] auto GetLastName() const->string;

	auto SetAddress(const string& address) -> bool;

	[[nodiscard]] auto GetAddress() const->string;

	auto SetGender(GenderT gender) -> bool;

	[[nodiscard]] auto GetGender() const->GenderT;

	auto SetAge(int age) -> bool;

	[[nodiscard]] auto GetAge() const -> int;

	auto SetPhoneNumber(unsigned long long number) -> bool;

	[[nodiscard]] auto GetPhoneNumber() const -> unsigned long long;

	auto SetUserId(int userId) -> bool;

	[[nodiscard]] auto GetUserId() const -> int;

	auto SetUserPassword(int password) -> bool;

	[[nodiscard]] auto GetUserPassword() const -> int;

#pragma endregion

private:
	GenderT MGender;
	string MFirstName, MLastName, MAddress;
	int MAge, MUserId, MUserPassword;
	unsigned long long MPhoneNumber;
	static unsigned int TotalUsers;
};



#endif
