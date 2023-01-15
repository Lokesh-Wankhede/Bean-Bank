/**
 * Copyright: LogicalLokesh. All rights reserved.
 *
 * File:   User.h
 *
 * Brief:  User class for Bean Bank.
 *
 * Author: LogicalLokesh (github.com/LogicalLokesh)
 * Date:   January 2023a
**/

#pragma once

#include <string>
#include <regex>
#include <fstream>
#include "Account.h"

using std::string;

// Gender: 1- Male, 2- Female, 3- Other.
using GenderT = enum { Male = 1, Female = 2, Other = 3 };

class User : public Account
{
	GenderT MGender;
	string MFirstName, MLastName, MAddress;
	int MAge, MUserId, MUserPassword;
	unsigned long long MPhoneNumber;
	static unsigned int TotalUsers;

public:
	/**
	* \brief Checks for illegal characters in name.
	*
	* \param name in string
	* \return True if name is valid, false otherwise.
	*/
	static auto ValidateName(const string& name)
	{
		// name must be greater than 2 or less than 20 characters.
		if (name.length() <= 2 || name.length() >= 20)
			return false;

		// check if letters are in between A to Z or a to z.
		// all other characters are not allowed including space.
		return std::ranges::all_of(name, [](const char c)
			{
				return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
			});
	}

	/**
	* \brief Checks for the illegal characters in address.
	*
	* \param address string
	* \return True if address is valid, false otherwise.
	*/
	static auto ValidateAddress(const string& address)
	{
		// address must be greater than 2 or less than 150 characters.
		if (address.length() <= 2 || address.length() >= 150)
			return false;

		// space is not allowed in first or last position of address.
		if (address[0] == 32 || address[address.length() - 1] == 32)
			return false;

		// check if letters are in between A to Z or a to z.
		// we can use the std::ranges::all_of algorithm to check if all the
		// characters in the address string are valid
		return std::ranges::all_of(address, [](const char i)
			{
				return (i >= 65 && i <= 90) || (i >= 97 && i <= 122) || (i == 32);
			});
	}

	/**
	* \brief Validates the age. Age must be from 18 to 200 years.
	*
	* \param age of the user
	* \return True if age is valid, false otherwise.
	*/
	static bool ValidateAge(const int age) { return (age >= 18 && age <= 200); }

	/**
	* \brief Validates the phone number by standard regex.
	*
	* \param phoneNumber 10 digit number
	* \return True if phone number valid, false otherwise.
	*/
	[[nodiscard]] bool ValidatePhoneNumber(const unsigned long long phoneNumber) const
	{
		// convert number to string for regex pattern matching.
		const string s = std::to_string(phoneNumber);

		// Indian phone numbers must be 10 digits long
		if (s.length() != 10)
			return false;

		// Check if all characters in the phone number are digits
		for (const char& c : s)
		{
			if (!std::isdigit(c))
				return false;
		}

		// 1) Begins with 0 or 91
		// 2) Then contains 6,7 or 8 or 9.
		// 3) Then contains 9 digits
		const std::regex pattern("(0|91)?[6-9][0-9]{9}");

		return std::regex_match(s, pattern);
	}

	/**
	* \brief Validates userId. It must in be between 1 to 50000.
	*
	* \param userId id of the user
	* \return True if userId is valid, false otherwise.
	*/
	static bool ValidateUserId(const int userId) { return (userId > 0 && userId < 50000); }

	/**
	* \brief Validates the user password. it must be 7 digit number.
	 *
	 * \param password 7 digit number
	 * \return True if password is valid, false otherwise.
	 */
	static bool ValidateUserPassword(const int password)
	{
		return password >= 1000000 && password <= 9999999;
	}

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
	explicit User(const string& firstName = "", const string& lastName = "",
		const int age = 0, const unsigned long long phoneNo = 0,
		const int userId = 0, const int userPassword = 0,
		const GenderT gender = Other, const string& address = "")
	{
		if (ValidateName(firstName))
			MFirstName = firstName;
		if (ValidateName(lastName))
			MLastName = lastName;
		if (ValidateAge(age))
			MAge = age;
		if (ValidatePhoneNumber(phoneNo))
			MPhoneNumber = phoneNo;
		if (ValidateUserId(userId))
			MUserId = userId;
		if (ValidateUserPassword(userPassword))
			MUserPassword = userPassword;
		if (gender == Male || gender == Female || gender == Other)
			MGender = gender;
		if (ValidateAddress(address))
			MAddress = address;
	}

	friend std::ofstream& operator<<(std::ofstream& ofs, const User& user)
	{
		ofs << user.GetFirstName() << '-' << user.GetLastName() << '-'
			<< user.GetAge() << '-' << user.GetPhoneNumber() << '-'
			<< user.GetUserId() << '-' << user.GetUserPassword() << '-'
			<< user.GetGender() << '-' << user.GetAddress() << "\n";
		return ofs;
	}

	friend std::ifstream& operator>>(std::ifstream& ifs, const User& user)
	{
		std::cout << user.GetFirstName() << '-' << user.GetLastName() << '-'
			<< user.GetAge() << '-' << user.GetPhoneNumber() << '-'
			<< user.GetUserId() << '-' << user.GetUserPassword() << '-'
			<< user.GetGender() << '-' << user.GetAddress() << "\n";
		return ifs;
	}


#pragma region Accessors and Mutators

	static unsigned int GetTotalUsers() { return TotalUsers; }
	static void AddUser() { TotalUsers++; }
	static void RemoveUser() { TotalUsers--; }

	bool SetFirstName(const string& name)
	{
		if (!ValidateName(name))
			return false;
		MFirstName = name;
		return true;
	}

	[[nodiscard]] string GetFirstName() const { return MFirstName; }

	bool SetLastName(const string& name)
	{
		if (!ValidateName(name))
			return false;
		MLastName = name;
		return true;
	}

	[[nodiscard]] string GetLastName() const { return MLastName; }

	bool SetAddress(const string& address)
	{
		if (!ValidateAddress(address))
			return false;
		MAddress = address;
		return true;
	}

	[[nodiscard]] string GetAddress() const { return MAddress; }

	bool SetGender(const GenderT gender)
	{
		if (gender == Male || gender == Female || gender == Other)
		{
			MGender = gender;
			return true;
		}
		return false;
	}

	[[nodiscard]] GenderT GetGender() const { return MGender; }

	bool SetAge(const int age)
	{
		if (!ValidateAge(age))
			return false;
		MAge = age;
		return true;
	}

	[[nodiscard]] int GetAge() const { return MAge; }

	bool SetPhoneNumber(const unsigned long long number)
	{
		if (!ValidatePhoneNumber(number))
			return false;
		MPhoneNumber = number;
		return true;
	}

	[[nodiscard]] unsigned long long GetPhoneNumber() const { return MPhoneNumber; }

	bool SetUserId(const int userId)
	{
		if (!ValidateUserId(userId))
			return false;
		MUserId = userId;
		return true;
	}

	[[nodiscard]] int GetUserId() const { return MUserId; }

	bool SetUserPassword(const int password)
	{
		if (!ValidateUserPassword(password))
			return false;
		MUserPassword = password;
		return true;
	}

	[[nodiscard]] int GetUserPassword() const { return MUserPassword; }

#pragma endregion
};

unsigned int User::TotalUsers = 0;
