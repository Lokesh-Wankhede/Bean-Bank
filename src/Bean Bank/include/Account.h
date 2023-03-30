// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Account class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#pragma once

#include <random>
#include <set>

// TODO: Make the class Abstract by adding a pure virtual function
class Account
{
public:
	/**
	* \brief Validates the account number. It must be 10 digit number.
	* \param accountNumber 10 digit number
	* \return True if valid. false otherwise.
	*/
	static auto ValidateAccountNumber(unsigned long long accountNumber) -> bool;

	/**
	* \brief Generate a truly random Account number.
	* \return 10 digit random number.
	*/
	static auto GenerateAccountNumber() -> unsigned long long;

#pragma region Getters and Setters

	static auto GetTotalAccounts() -> unsigned int;
	static auto AddAccount() -> void;
	static auto RemoveAccount() -> void;
	auto AddBalance(int balance) -> bool;
	auto WithdrawBalance(int amount) -> bool;
	auto SetBalance(int balance) -> bool;
	[[nodiscard("Please handle the return value.")]] auto GetBalance() const -> int;
	auto SetAccountNumber(unsigned long long accountNumber) -> bool;
	[[nodiscard("Please handle the return value.")]] auto
		GetAccountNumber() const -> unsigned long long;

#pragma endregion

private:
	unsigned long long MAccountNumber{ 0 };
	int MBalance{ 0 };
	static unsigned int TotalAccounts;
};
