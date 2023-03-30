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
constexpr auto MIN_NAME_SIZE = 3;
constexpr auto MAX_NAME_SIZE = 20;
constexpr auto MIN_ADDRESS_SIZE = 5;
constexpr auto MAX_ADDRESS_SIZE = 150;
constexpr auto MIN_USER_ID = 1;
constexpr auto MAX_USER_ID = 5000;
constexpr auto MIN_USER_PASSWORD = 1000000;
constexpr auto MAX_USER_PASSWORD = 9999999;

unsigned int User::TotalUsers{};

User::User(const std::string& firstName = "", const std::string& lastName = "",
	const int age = 0, const unsigned long long phoneNo = 0,
	const int userId = 0, const int userPassword = 0,
	const GenderT gender = GenderT::Other, const std::string& address = "")
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
	if (gender == GenderT::Male || gender == GenderT::Female || gender == GenderT::Other)
		MGender = gender;
	if (ValidateAddress(address))
		MAddress = address;
}

auto User::ValidateName(const string& name) -> bool
{
	// name must be greater than MIN_NAME_SIZE or less than MAX_NAME_SIZE.
	if (name.length() <= MIN_NAME_SIZE || name.length() >= MAX_NAME_SIZE)
		return false;

	// check if letters are in between A to Z or a to z.
	// all other characters are not allowed including space.
	return std::ranges::all_of(name, [](const char c)
		{
			return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
		}) &&
		name.length() > 2 && name.length() < 20;
}

auto User::ValidateAddress(const string& address) -> bool
{
	// address must be greater than MIN_ADDRESS_SIZE or less than MAX_ADDRESS_SIZE.
	if (address.length() <= MIN_ADDRESS_SIZE || address.length() >= MAX_ADDRESS_SIZE)
		return false;

	// space is not allowed in first or last position of address.
	if (address[0] == 32 || address[address.length() - 1] == 32)
		return false;

	// check if letters are in between A to Z or a to z.
	// we can use the std::ranges::all_of algorithm to check if all the
	// characters in the address string are valid.
	return std::ranges::all_of(address, [](const char i)
		{
			return (i >= 65 && i <= 90) || (i >= 97 && i <= 122) || (i == 32);
		}
	);
}

auto User::ValidateAge(const int age) -> bool
{
	return (age >= MIN_USER_AGE && age <= MAX_USER_AGE);
}

auto User::ValidatePhoneNumber(const unsigned long long phoneNumber) const -> bool
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

auto User::ValidateUserId(const int userId) -> bool
{
	return (userId > MIN_USER_ID && userId <= MAX_USER_ID);
}

auto User::ValidateUserPassword(const int password) -> bool
{
	return password >= MIN_USER_PASSWORD && password <= MAX_USER_PASSWORD;
}

auto operator<<(std::ofstream& ofs, const User& user) -> std::ofstream&
{
	ofs << user.GetFirstName() << '-' << user.GetLastName() << '-'
		<< user.GetAge() << '-' << user.GetPhoneNumber() << '-'
		<< user.GetUserId() << '-' << user.GetUserPassword() << '-'
		<< static_cast<int>(user.GetGender()) << '-' << user.GetAddress() << "\n";
	return ofs;
}

auto operator>>(std::ifstream& ifs, const User& user) -> std::ifstream&
{
	std::cout << user.GetFirstName() << '-' << user.GetLastName() << '-'
		<< user.GetAge() << '-' << user.GetPhoneNumber() << '-'
		<< user.GetUserId() << '-' << user.GetUserPassword() << '-'
		<< static_cast<int>(user.GetGender()) << '-' << user.GetAddress() << "\n";
	return ifs;
}

#pragma region Getters and Setters

auto User::GetTotalUsers() -> unsigned { return TotalUsers; }
auto User::AddUser() -> void { TotalUsers++; }
auto User::RemoveUser() -> void { TotalUsers--; }

auto User::SetFirstName(const string& name) -> bool
{
	if (!ValidateName(name))
		return false;
	MFirstName = name;
	return true;
}

auto User::GetFirstName() const -> string { return MFirstName; }

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

auto User::SetUserId(const int userId) -> bool
{
	if (!ValidateUserId(userId))
		return false;
	MUserId = userId;
	return true;
}

auto User::GetUserId() const -> int { return MUserId; }

auto User::SetUserPassword(const int password) -> bool
{
	if (!ValidateUserPassword(password))
		return false;
	MUserPassword = password;
	return true;
}

auto User::GetUserPassword() const -> int { return MUserPassword; }

#pragma endregion
