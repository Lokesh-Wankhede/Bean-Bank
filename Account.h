/**
 * Copyright: LogicalLokesh. All rights reserved.
 *
 * Brief:  Account class for Bean Bank.
 *
 * Author: LogicalLokesh (github.com/LogicalLokesh)
 * Date:   January 2023
**/

#pragma once

#include <random>
#include <set>

class Account
{
	unsigned long long MAccountNumber = 0;
	int MBalance = 0;
	static unsigned int TotalAccounts;

public:
	/**
	 * \brief Validates the account number. It must be 10 digit number.
	 *
	 * \param accountNumber 10 digit number to validate
	 * \return True if valid, false otherwise.
	 */
	static bool ValidateAccountNumber(const unsigned long long accountNumber)
	{
		return accountNumber >= 999999999 && accountNumber <= 9999999999;
	}

	/**
	 * \brief Generate a truly random Account number.
	 *
	 * \return Pointer to a 10 digit random number.
	 */
	static unsigned long long GenerateAccountNumber()
	{
		std::set<unsigned long long> uniqueNumbers;
		std::mt19937 rng(std::random_device{}()); // Use a random number generator
		std::uniform_int_distribution<unsigned long long> dist(1000000000, 9999999999);

		// Generate 10-digit numbers until we have a unique one.
		while (uniqueNumbers.size() < 10)
			uniqueNumbers.insert(dist(rng)); // Insert a random 10-digit number

		return *uniqueNumbers.begin(); // Return the first unique number
	}

#pragma region Accessors and Mutators

	static unsigned int GetTotalAccounts() { return TotalAccounts; }
	static void AddAccount() { TotalAccounts++; }
	static void RemoveAccount() { TotalAccounts--; }

	bool AddBalance(const int balance)
	{
		MBalance += balance;
		return true;
	}

	bool WithdrawBalance(const int amount)
	{
		if (MBalance <= amount && MBalance - amount != 0)
			return false;
		MBalance -= amount;
		return true;
	}

	bool SetBalance(const int balance)
	{
		MBalance = balance;
		return true;
	}

	[[nodiscard]] int GetBalance() const { return MBalance; }

	bool SetAccountNumber(const unsigned long long accountNumber)
	{
		if (!ValidateAccountNumber(accountNumber))
			return false;
		MAccountNumber = accountNumber;
		return true;
	}

	[[nodiscard]] unsigned long long GetAccountNumber() const { return MAccountNumber; }

#pragma endregion
};

unsigned int Account::TotalAccounts = 0;
