// Copyright (c) LogicalLokesh, All rights reserved.
//MIN_NAME_LENGTH
// Description: The User class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#include "User.h"
#include <regex>

#include "Logger.h"

using std::regex;

constexpr auto MIN_USER_AGE = 18;
constexpr auto MAX_USER_AGE = 200;
constexpr auto MIN_NAME_LENGTH = 2;
constexpr auto MAX_NAME_LENGTH = 20;
constexpr auto MIN_ADDRESS_LENGTH = 5;
constexpr auto MAX_ADDRESS_LENGTH = 150;
constexpr auto MIN_USERID_LENGTH = 5;
constexpr auto MAX_USERID_LENGTH = 20;
constexpr auto MIN_USER_PASSWORD_LENGTH = 4;
constexpr auto MAX_USER_PASSWORD_LENGTH = 20;
constexpr auto MIN_MPIN = 100000;
constexpr auto MAX_MPIN = 999999;

User::User
(
	const string& firstName, const string& middleName, const string& lastName,
	const string& address,
	const GenderT gender, const int age, const unsigned long long phoneNo,
	const string& userId, const string& userPassword, const int mPin
)
	: MFirstName(ValidateName(firstName) ? firstName : ""),
	MMiddleName(ValidateName(middleName) ? middleName : ""),
	MLastName(ValidateName(lastName) ? lastName : ""),
	MAddress(ValidateAddress(address) ? address : ""),
	MGender
	(
		(gender == GenderT::Male || gender == GenderT::Female || gender == GenderT::Other)
		? gender
		: GenderT::Other
	),
	MAge(ValidateAge(age) ? age : 0),
	MPhoneNumber(ValidatePhoneNumber(phoneNo) ? phoneNo : 0),
	MUserId(ValidateUserId(userId) ? userId : ""),
	MUserPassword(ValidateUserPassword(userPassword) ? userPassword : ""),
	MmPin(ValidateMPin(mPin) ? mPin : 0) {}


auto User::IsValid(const User& user) -> bool
{
	LOGGER->debug("[User->IsValid] Performing validation on user...");
	if (!ValidateName(user.GetFirstName()))
	{
		LOGGER->error("[User->IsValid] User validation failed: first name is not valid");
		return false;
	}
	if (!ValidateName(user.GetMiddleName()))
	{
		LOGGER->error("[User->IsValid] User validation failed: middle name is not valid");
		return false;
	}
	if (!ValidateName(user.GetLastName()))
	{
		LOGGER->error("[User->IsValid] User validation failed: last name is not valid");
		return false;
	}
	if (!ValidateAge(user.GetAge()))
	{
		LOGGER->error("[User->IsValid] User validation failed: age is not valid");
		return false;
	}
	if (!ValidatePhoneNumber(user.GetPhoneNumber()))
	{
		LOGGER->error("[User->IsValid] User validation failed: phone number is not valid");
		return false;
	}
	if (!ValidateUserId(user.GetUserId()))
	{
		LOGGER->error("[User->IsValid] User validation failed: user id is not valid");
		return false;
	}
	if (!ValidateUserPassword(user.GetUserPassword()))
	{
		LOGGER->error("[User->IsValid] User validation failed: user password is not valid");
		return false;
	}
	if (!ValidateMPin(user.GetMPin()))
	{
		LOGGER->error("[User->IsValid] User validation failed: mPin is not valid");
		return false;
	}
	if (user.GetGender() != GenderT::Male && user.GetGender() != GenderT::Female &&
		user.GetGender() != GenderT::Other)
	{
		LOGGER->error("[User->IsValid] User validation failed: gender is not valid");
		return false;
	}
	if (!ValidateAddress(user.GetAddress()))
	{
		LOGGER->error("[User->IsValid] User validation failed: address is not valid");
		return false;
	}

	LOGGER->debug("[User->IsValid] User validation success...");
	return true;
}

auto User::ValidateName(const string& name) -> bool
{
	LOGGER->debug("[User->ValidateName] Performing validation on name ({})...", name);

	// name must be greater than MIN_NAME_LENGTH or less than MAX_NAME_LENGTH
	if (name.length() < MIN_NAME_LENGTH || name.length() > MAX_NAME_LENGTH)
	{
		LOGGER->error("[User->ValidateName] Invalid name length (name = {}, length = {})", name,
			name.length());
		return false;
	}

	// check if letters are in between A to Z or a to z
	// all other characters are not allowed including space
	const bool isValid = std::ranges::all_of(name, [&](const char c)
		{
			const bool isAllowedCharacter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
			if (!isAllowedCharacter)
				LOGGER->error(
					"[User->ValidateName] Invalid character found in name (name = {}, invalidChar = {})",
					name, c);
			return isAllowedCharacter;
		});

	LOGGER->debug("[User->ValidateName] Name ({}) is {}.", name, isValid ? "Valid" : "Invalid");
	return isValid;
}

auto User::ValidateAddress(const string& address) -> bool
{
	LOGGER->debug("[User->ValidateAddress] Performing validation on address ({})...", address);
	constexpr char allowedChars[] =
		// ReSharper disable StringLiteralTypo
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789/+-.,|();:'\"* ";
	// ReSharper restore StringLiteralTypo

	constexpr size_t allowedCharsCount = sizeof(allowedChars) - 1;

	// address must be greater than MIN_ADDRESS_LENGTH or less than MAX_ADDRESS_LENGTH
	if (address.length() <= MIN_ADDRESS_LENGTH || address.length() >= MAX_ADDRESS_LENGTH)
	{
		LOGGER->debug(
			"[User->ValidateAddress] Address ({}) is invalid because it is shorter than {} or longer than {}.",
			address, MIN_ADDRESS_LENGTH, MAX_ADDRESS_LENGTH);
		return false;
	}

	// space is not allowed in first or last position of address
	if (address[0] == 32 || address[address.length() - 1] == 32)
	{
		LOGGER->debug(
			"[User->ValidateAddress] Address ({}) is invalid because it starts or ends with a space character.",
			address);
		return false;
	}

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
		{
			LOGGER->debug(
				"[User->ValidateAddress] Address ({}) is invalid because it contains an invalid character: {}",
				address, c);
			return false;
		}
	}
	LOGGER->debug("[User->ValidateAddress] Address ({}) is valid.", address);
	return true;
}

auto User::ValidateAge(const int age) -> bool
{
	LOGGER->debug("[User->ValidateAge] Performing validation on age ({})...", age);
	const bool isValid = (age >= MIN_USER_AGE && age <= MAX_USER_AGE);
	LOGGER->debug("[User->ValidateAge] Age ({}) is {}.", age, isValid ? "Valid" : "Invalid");
	return isValid;
}

auto User::ValidateAgeStr(const string& ageStr) -> bool
{
	LOGGER->debug("[User->ValidateAgeStr] Performing validation on ageStr ({})...", ageStr);
	try
	{
		const int parsedInt = std::stoi(ageStr);
		return ValidateAge(parsedInt);
	}
	catch (std::exception& e)
	{
		LOGGER->debug(
			"[User->ValidateAgeStr] Error: Invalid ageStr string ({}) with message: {}.",
			ageStr, e.what());
		return false;
	}
}

auto User::ValidatePhoneNumber(const unsigned long long phoneNumber) -> bool
{
	LOGGER->debug(
		"[User->ValidatePhoneNumber] Performing validation on phone number ({})...",
		phoneNumber);
	try
	{
		// convert number to string and call ValidatePhoneNumberStr()
		const string parsedString = std::to_string(phoneNumber);
		LOGGER->debug(
			"[User->ValidatePhoneNumber] Parsed to string successfully, "
			"calling the ValidatePhoneNumberStr method...");
		return ValidatePhoneNumberStr(parsedString);
	}
	catch (std::exception& e)
	{
		LOGGER->debug(
			"[User->ValidatePhoneNumber] Error: Invalid parsedString ({}) with message: {}.",
			phoneNumber, e.what());
		return false;
	}
}

auto User::ValidatePhoneNumberStr(const string& phoneNumber) -> bool
{
	LOGGER->debug(
		"[User->ValidatePhoneNumberStr] Performing validation on phoneNumber ({})...",
		phoneNumber);

	// Indian phone numbers must be 10 digits long
	if (phoneNumber.length() != 10)
	{
		LOGGER->debug("[User->ValidatePhoneNumberStr] Invalid phoneNumber length: {}",
			phoneNumber);
		return false;
	}

	// check if all characters in the phone number are digits
	for (const char& c : phoneNumber)
	{
		if (!std::isdigit(c))
		{
			LOGGER->debug(
				"[User->ValidatePhoneNumberStr] Invalid character '{}' found in phoneNumber: {}",
				c, phoneNumber);
			return false;
		}
	}

	// 1) begins with 0 or 91
	// 2) then contains 6,7 or 8 or 9
	// 3) then contains 9 digits
	const std::regex pattern("(0|91)?[6-9][0-9]{9}");

	// match and return the result.
	const bool isValid = std::regex_match(phoneNumber, pattern);
	LOGGER->debug(
		"[User->ValidatePhoneNumberStr] Phone number '{}' is {}.",
		phoneNumber, isValid ? "Valid" : "Invalid");
	return isValid;
}

auto User::ValidateUserId(const string& userId) -> bool
{
	LOGGER->debug("[User->ValidateUserId] Performing validation on userId ({})...", userId);

	// userId must be greater than MIN_USERID_LENGTH or less than MAX_USERID_LENGTH.
	if (userId.length() < MIN_USERID_LENGTH || userId.length() > MAX_USERID_LENGTH)
	{
		LOGGER->debug(
			"[User->ValidateUserId] userId ({}) is invalid, length must be between {} and {}.",
			userId, MIN_USERID_LENGTH, MAX_USERID_LENGTH);
		return false;
	}

	// space is not allowed in first or last position of userId.
	if (userId[0] == 32 || userId[userId.length() - 1] == 32)
	{
		LOGGER->debug(
			"[User->ValidateUserId] userId ({}) is invalid, space is not allowed in first or last position.",
			userId);
		return false;
	}

	// check if userId contains only allowed characters.
	// ReSharper disable StringLiteralTypo
	constexpr char allowedChars[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789/!@#$%^&`~+-.,|();:'\"* ";
	// ReSharper enable StringLiteralTypo

	constexpr size_t allowedCharsCount = sizeof(allowedChars) - 1;

	for (const auto& c : userId)
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
		{
			LOGGER->debug(
				"[User->ValidateUserId] userId ({}) is invalid, character ({}) is not allowed.",
				userId, c);
			return false;
		}
	}

	// TODO: Query the database for userIds to make sure the id is always unique and not duplicate.

	LOGGER->debug("[User->ValidateUserId] userId ({}) is valid.", userId);
	return true;
}

auto User::ValidateUserPassword(const string& password) -> bool
{
	LOGGER->debug("[User->ValidateUserPassword] Performing validation on password ({})...",
		password);

	// password must be greater than MIN_USER_PASSWORD_LENGTH or less than MAX_USER_PASSWORD_LENGTH.
	if (password.length() < MIN_USER_PASSWORD_LENGTH || password.length() >
		MAX_USER_PASSWORD_LENGTH)
	{
		LOGGER->debug(
			"[User->ValidateUserPassword] password ({}) is invalid, length must be between {} and {}.",
			password, MIN_USER_PASSWORD_LENGTH, MAX_USER_PASSWORD_LENGTH);
		return false;
	}

	// space is not allowed in first or last position of password.
	if (password[0] == 32 || password[password.length() - 1] == 32)
	{
		LOGGER->debug(
			"[User->ValidateUserPassword] password ({}) is invalid, space is not allowed in first or last position.",
			password);
		return false;
	}

	// check if password contains only allowed characters.
	// ReSharper disable StringLiteralTypo
	constexpr char allowedChars[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789/!@#$%^&`~+-.,|();:'\"* ";
	// ReSharper enable StringLiteralTypo

	constexpr size_t allowedCharsCount = sizeof(allowedChars) - 1;

	for (const auto& c : password)
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
		{
			LOGGER->debug(
				"[User->ValidateUserPassword] password ({}) is invalid, character ({}) is not allowed.",
				password, c);
			return false;
		}
	}

	LOGGER->debug("[User->ValidateUserPassword] password ({}) is valid.", password);
	return true;
}

auto User::ValidateMPin(const int pin) -> bool
{
	LOGGER->debug("[User->ValidateMPin] Performing validation on pin ({})...", pin);

	const bool isValid = (pin > MIN_MPIN && pin <= MAX_MPIN);

	LOGGER->debug("[User->ValidateMPin] Pin {} is {}.", pin, isValid ? "Valid" : "Invalid");

	return isValid;
}

#pragma region Getters and Setters

auto User::SetFirstName(const string& name) -> bool
{
	LOGGER->debug("[User->SetFirstName] Setting MFirstName...");
	if (!ValidateName(name))
		return false;
	MFirstName = name;
	return true;
}

auto User::GetFirstName() const -> string { return MFirstName; }

auto User::SetMiddleName(const string& name) -> bool
{
	LOGGER->debug("[User->SetMiddleName] Setting MMiddleName...");
	if (!ValidateName(name))
		return false;
	MMiddleName = name;
	return true;
}

auto User::GetMiddleName() const -> string { return MMiddleName; }

auto User::SetLastName(const string& name) -> bool
{
	LOGGER->debug("[User->SetLastName] Setting MLastName...");
	if (!ValidateName(name))
		return false;
	MLastName = name;
	return true;
}

auto User::GetLastName() const -> string { return MLastName; }

auto User::SetAddress(const string& address) -> bool
{
	LOGGER->debug("[User->SetAddress] Setting MAddress...");
	if (!ValidateAddress(address))
		return false;
	MAddress = address;
	return true;
}

auto User::GetAddress() const -> string { return MAddress; }

auto User::SetGender(const GenderT gender) -> bool
{
	LOGGER->debug("[User->SetGender] Setting MGender...");
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
	LOGGER->debug("[User->SetAge] Setting MAge...");
	if (!ValidateAge(age))
		return false;
	MAge = age;
	return true;
}

auto User::GetAge() const -> int { return MAge; }

auto User::SetPhoneNumber(const unsigned long long number) -> bool
{
	LOGGER->debug("[User->SetPhoneNumber] Setting MPhoneNumber...");
	if (!ValidatePhoneNumber(number))
		return false;
	MPhoneNumber = number;
	return true;
}

auto User::GetPhoneNumber() const -> unsigned long long { return MPhoneNumber; }

auto User::SetUserId(const string& userId) -> bool
{
	LOGGER->debug("[User->SetUserId] Setting MUserId...");
	if (!ValidateUserId(userId))
		return false;
	MUserId = userId;
	return true;
}

auto User::GetUserId() const -> string { return MUserId; }

auto User::SetUserPassword(const string& password) -> bool
{
	LOGGER->debug("[User->SetUserPassword] Setting MUserPassword...");
	if (!ValidateUserPassword(password))
		return false;
	MUserPassword = password;
	return true;
}

auto User::GetUserPassword() const -> string { return MUserPassword; }

auto User::SetMPin(const int mPin) -> bool
{
	LOGGER->debug("[User->SetMPin] Setting mPin...");
	if (!ValidateMPin(mPin))
		return false;
	MmPin = mPin;
	return true;
}

auto User::GetMPin() const -> int { return MmPin; }

#pragma endregion
