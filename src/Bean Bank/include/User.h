// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The User class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh


#pragma once

#include <string>

using std::string;

// Gender: 1- Male, 2- Female, 3- Other
enum class GenderT { Male = 1, Female = 2, Other = 3 };

class User
{
public:
	User() = default;

	/**
	 * \brief Creates the user object.
	 * \param firstName first name
	 * \param middleName middle name
	 * \param lastName last name
	 * \param address address
	 * \param gender gender
	 * \param age age
	 * \param phoneNo 10 digit phone number
	 * \param userId unique Id
	 * \param userPassword userPassword
	 * \param mPin User mPin
	 */
	explicit User(const string& firstName, const string& middleName, const string& lastName, const string& address,
		GenderT gender, int age, unsigned long long phoneNo,
		const string& userId, const string& userPassword, int mPin);

	/**
	 * \brief Checks if user is valid or not.
	 * \param user User to validate
	 * \return true if valid, false otherwise.
	 */
	static auto IsValid(const User& user) -> bool;

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
	* \brief Validates the age. Age must be from 18 to 200 years.
	*
	* \param ageStr age in string
	* \return true if age is valid, false otherwise.
	*/
	static auto ValidateAgeStr(const string& ageStr) -> bool;

	/**
	* \brief Validates the phone number by standard regex.
	*
	* \param phoneNumber 10 digit number to validate
	* \return true if phone number valid, false otherwise.
	*/
	[[nodiscard("Please handle the return value.")]]
	static auto ValidatePhoneNumber(unsigned long long phoneNumber) -> bool;

	/**
	* \brief Validates the phone number by standard regex.
	*
	* \param phoneNumber 10 digit number to validate (in string)
	* \return true if phone number valid, false otherwise.
	*/
	[[nodiscard("Please handle the return value.")]]
	static auto ValidatePhoneNumberStr(const string& phoneNumber) -> bool;

	/**
	* \brief Checks for problems in userId.
	*
	* \param userId userId to validate
	* \return true if userId is valid, false otherwise.
	*/
	static auto ValidateUserId(const string& userId) -> bool;

	/**
	* \brief Validates the user password.
	 *
	 * \param password password to validate
	 * \return true if password is valid, false otherwise.
	 */
	static auto ValidateUserPassword(const string& password) -> bool;

	/**
	 * \brief Validates the mPin of the user.
	 * \param pin Pin number to validate
	 * \return true of valid, false otherwise.
	 */
	static auto ValidateMPin(int pin) -> bool;


#pragma region Setters and Getters

	auto SetFirstName(const string& name) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetFirstName() const->string;

	auto SetMiddleName(const string& name) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetMiddleName() const->string;

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

	auto SetUserId(const string& userId) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetUserId() const->string;

	auto SetUserPassword(const string& password) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetUserPassword() const->string;

	auto SetMPin(int mPin) -> bool;

	[[nodiscard("Please handle the return value.")]] auto GetMPin() const -> int;

#pragma endregion

private:
	// avoid the grouping same types to follow the initialization order in the constructor.
	string MFirstName{}, MMiddleName{}, MLastName{}, MAddress{};
	GenderT MGender{};
	int MAge{};
	unsigned long long MPhoneNumber{};
	string MUserId{}, MUserPassword{};
	int MmPin{};
};
