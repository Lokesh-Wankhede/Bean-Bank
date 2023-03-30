// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Account class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#include "Account.h"

unsigned int Account::TotalAccounts{ 0 };

auto Account::ValidateAccountNumber(const unsigned long long accountNumber) -> bool
{
	// TODO: Replace the magic values with constants
	return accountNumber >= 999999999 && accountNumber <= 9999999999;
}

auto Account::GenerateAccountNumber() -> unsigned long long
{
	std::set<unsigned long long> uniqueNumbers;
	std::mt19937 rng(std::random_device{}()); // Use a random number generator
	std::uniform_int_distribution<unsigned long long> dist(1000000000, 9999999999);

	unsigned long long accountNumber;
	// insert the number and check if it's unique
	do
		accountNumber = dist(rng);
	while (!uniqueNumbers.insert(accountNumber).second);
	return accountNumber;
}

auto Account::GetTotalAccounts() -> unsigned int { return TotalAccounts; }

auto Account::AddAccount() -> void { TotalAccounts++; }

auto Account::RemoveAccount() -> void { TotalAccounts--; }

auto Account::AddBalance(const int balance) -> bool
{
	MBalance += balance;
	return true;
}

auto Account::WithdrawBalance(const int amount) -> bool
{
	if (MBalance < amount)
		return false;
	MBalance -= amount;
	return true;
}


auto Account::SetBalance(const int balance) -> bool
{
	MBalance = balance;
	// TODO: implement a validation or safety check
	return true;
}

auto Account::GetBalance() const -> int { return MBalance; }

auto Account::SetAccountNumber(const unsigned long long accountNumber) -> bool
{
	if (!ValidateAccountNumber(accountNumber))
		return false;
	MAccountNumber = accountNumber;
	return true;
}

auto Account::GetAccountNumber() const -> unsigned long long { return MAccountNumber; }
