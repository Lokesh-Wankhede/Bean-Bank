// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The User class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#include "User.h"
#include <fstream>
#include <regex>

#include <iostream>

using std::regex;

constexpr auto MIN_USER_AGE = 18;
constexpr auto MAX_USER_AGE = 200;
constexpr auto MIN_NAME_SIZE = 2;
constexpr auto MAX_NAME_SIZE = 20;
constexpr auto MIN_ADDRESS_SIZE = 5;
constexpr auto MAX_ADDRESS_SIZE = 150;
constexpr auto MIN_USERID_SIZE = 5;
constexpr auto MAX_USERID_SIZE = 20;
constexpr auto MIN_USER_PASSWORD_SIZE = 4;
constexpr auto MAX_USER_PASSWORD_SIZE = 20;
constexpr auto MIN_MPIN = 100000;
constexpr auto MAX_MPIN = 999999;

User::User(const string& firstName = "", const string& middleName = "", const string& lastName = "",
	const int age = 0, const unsigned long long phoneNo = 0,
	const string& userId = "", const string& userPassword = "", const int mPin = 0,
	const GenderT gender = GenderT::Other, const string& address = "")
{
	if (ValidateName(firstName))
		MFirstName = firstName;
	if (ValidateName(middleName))
		MMiddleName = middleName;
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
	if (ValidateMPin(mPin))
		MmPin = mPin;
	if (gender == GenderT::Male || gender == GenderT::Female || gender == GenderT::Other)
		MGender = gender;
	if (ValidateAddress(address))
		MAddress = address;
}


auto User::IsValid(const User& user) -> bool
{
	if (!ValidateName(user.GetFirstName()))
		return false;
	if (!ValidateName(user.GetMiddleName()))
		return false;
	if (!ValidateName(user.GetLastName()))
		return false;
	if (!ValidateAge(user.GetAge()))
		return false;
	if (!ValidatePhoneNumber(user.GetPhoneNumber()))
		return false;
	if (!ValidateUserId(user.GetUserId()))
		return false;
	if (!ValidateUserPassword(user.GetUserPassword()))
		return false;
	if (!ValidateMPin(user.GetMPin()))
		return false;
	if (user.GetGender() == GenderT::Male || user.GetGender() == GenderT::Female ||
		user.GetGender() == GenderT::Other)
		return false;
	if (!ValidateAddress(user.GetAddress()))
		return false;
	return true;
}


auto User::ValidateName(const string& name) -> bool
{
	// name must be greater than MIN_NAME_SIZE or less than MAX_NAME_SIZE.
	if (name.length() < MIN_NAME_SIZE || name.length() > MAX_NAME_SIZE)
		return false;

	// check if letters are in between A to Z or a to z.
	// all other characters are not allowed including space.
	return std::ranges::all_of(name, [](const char c)
		{
			return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
		});
}

auto User::ValidateAddress(const string& address) -> bool
{
	constexpr char allowedChars[] =
		// ReSharper disable StringLiteralTypo
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789/+-.,|();:'\"* ";
	// ReSharper restore StringLiteralTypo

	constexpr size_t allowedCharsCount = sizeof(allowedChars) - 1;

	// address must be greater than MIN_ADDRESS_SIZE or less than MAX_ADDRESS_SIZE.
	if (address.length() <= MIN_ADDRESS_SIZE || address.length() >= MAX_ADDRESS_SIZE)
		return false;

	// space is not allowed in first or last position of address.
	if (address[0] == 32 || address[address.length() - 1] == 32)
		return false;

	for (const auto& c : address)
	{
		bool isValidChar = false;
		for (size_t i = 0; i < allowedCharsCount; ++i)
		{
			if (c == allowedChars[i])
			{
				isValidChar = true;
				break;
			}
		}
		if (!isValidChar)
			return false;
	}
	return true;
}

auto User::ValidateAge(const int age) -> bool
{
	return (age >= MIN_USER_AGE && age <= MAX_USER_AGE);
}

auto User::ValidateAgeStr(const string& ageStr) -> bool
{
	try
	{
		const int parsedInt = std::stoi(ageStr);
		return ValidateAge(parsedInt);
	}
	catch (std::exception&) { return false; }
}

auto User::ValidatePhoneNumber(const unsigned long long phoneNumber) -> bool
{
	// convert number to string for regex pattern matching.
	const string s = std::to_string(phoneNumber);

	// Indian phone numbers must be 10 digits long.
	if (s.length() != 10)
		return false;

	// check if all characters in the phone number are digits.
	for (const char& c : s)
	{
		if (!std::isdigit(c))
			return false;
	}

	// 1) begins with 0 or 91
	// 2) then contains 6,7 or 8 or 9
	// 3) then contains 9 digits
	const std::regex pattern("(0|91)?[6-9][0-9]{9}");

	// match and return the result.
	return std::regex_match(s, pattern);
}

auto User::ValidatePhoneNumberStr(const string& phoneNumber) -> bool
{
	// Indian phone numbers must be 10 digits long.
	if (phoneNumber.length() != 10)
		return false;

	// check if all characters in the phone number are digits.
	for (const char& c : phoneNumber)
	{
		if (!std::isdigit(c))
			return false;
	}

	// 1) begins with 0 or 91
	// 2) then contains 6,7 or 8 or 9
	// 3) then contains 9 digits
	const std::regex pattern("(0|91)?[6-9][0-9]{9}");

	// match and return the result.
	return std::regex_match(phoneNumber, pattern);
}

auto User::ValidateUserId(const string& userId) -> bool
{
	// address must be greater than MIN_USERID_SIZE or less than MAX_USERID_SIZE.
	if (userId.length() <= MIN_USERID_SIZE || userId.length() >= MAX_USERID_SIZE)
		return false;

	// space is not allowed in first or last position of address.
	return (userId[0] == 32 || userId[userId.length() - 1] == 32) ? false : true;
}

auto User::ValidateUserPassword(const string& password) -> bool
{
	// address must be greater than MIN_USER_PASSWORD_SIZE or less MAX_USER_PASSWORD_SIZE.
	if (password.length() <= MIN_USER_PASSWORD_SIZE || password.length() >= MAX_USER_PASSWORD_SIZE)
		return false;

	// space is not allowed in first or last position of address.
	return (password[0] == 32 || password[password.length() - 1] == 32) ? false : true;
}

auto User::ValidateMPin(const int pin) -> bool { return (pin > MIN_MPIN && pin <= MAX_MPIN); }

#pragma region Getters and Setters

auto User::SetFirstName(const string& name) -> bool
{
	if (!ValidateName(name))
		return false;
	MFirstName = name;
	return true;
}

auto User::GetFirstName() const -> string { return MFirstName; }

auto User::SetMiddleName(const string& name) -> bool
{
	if (!ValidateName(name))
		return false;
	MMiddleName = name;
	return true;
}

auto User::GetMiddleName() const -> string { return MMiddleName; }

auto User::SetLastName(const string& name) -> bool
{
	if (!ValidateName(name))
		return false;
	MLastName = name;
	return true;
}

auto User::GetLastName() const -> string { return MLastName; }

auto User::SetAddress(const string& address) -> bool
{
	if (!ValidateAddress(address))
		return false;
	MAddress = address;
	return true;
}

auto User::GetAddress() const -> string { return MAddress; }

auto User::SetGender(const GenderT gender) -> bool
{
	if (gender == GenderT::Male || gender == GenderT::Female || gender == GenderT::Other)
	{
		MGender = gender;
		return true;
	}
	return false;
}

auto User::GetGender() const -> GenderT { return MGender; }

auto User::SetAge(const int age) -> bool
{
	if (!ValidateAge(age))
		return false;
	MAge = age;
	return true;
}

auto User::GetAge() const -> int { return MAge; }

auto User::SetPhoneNumber(const unsigned long long number) -> bool
{
	if (!ValidatePhoneNumber(number))
		return false;
	MPhoneNumber = number;
	return true;
}

auto User::GetPhoneNumber() const -> unsigned long long { return MPhoneNumber; }

auto User::SetUserId(const string& userId) -> bool
{
	if (!ValidateUserId(userId))
		return false;
	MUserId = userId;
	return true;
}

auto User::GetUserId() const -> string { return MUserId; }

auto User::SetUserPassword(const string& password) -> bool
{
	if (!ValidateUserPassword(password))
		return false;
	MUserPassword = password;
	return true;
}

auto User::GetUserPassword() const -> string { return MUserPassword; }

auto User::SetMPin(const int mPin) -> bool
{
	if (!ValidateMPin(mPin))
		return false;
	MmPin = mPin;
	return true;
}

auto User::GetMPin() const -> int { return MmPin; }

#pragma endregion
