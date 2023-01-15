/**
 * Copyright: LogicalLokesh. All rights reserved.
 *
 * File:   Bank.h
 *
 * Brief:  Account class for Bean Bank.
 *
 * Author: LogicalLokesh (github.com/LogicalLokesh)
 * Date:   January 2023
**/

#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "User.h"
#include "main.h"

using std::string;
using std::getline;
using std::vector;
using std::ifstream;
using std::ofstream;

inline vector<User> vUsers;

using AccountDetailsT = struct
{
	unsigned long long AccountNumber;
	int UserId;
	unsigned long long UserPassword;
	int Balance;
};

inline vector<AccountDetailsT> vAccountDetails;

class Bank
{
	static unsigned int TotalUsers;

public:
	/**
	 * \brief Loads the user_data file into vUsers.
	 *
	 * \return True on success, false otherwise.
	 */
	static bool LoadUserDataFile()
	{
		try
		{
			ifstream in("user_data.txt");
			// Create the file if does not exist.
			if (!in.good())
			{
				ofstream out("user_data.txt", std::ios::trunc);
				out.close();
			}
			string line;
			while (getline(in, line))
			{
				if (line.empty()) // skip empty lines
					continue;

				// Iterate over every line and load it into a string.
				// then convert the string into corresponding types.
				std::stringstream ss(line);
				string firstName, lastName, address, ageStr, userIdStr,
					userPasswordStr, phoneNumberStr, genderStr;
				getline(ss, firstName, '-');
				getline(ss, lastName, '-');
				getline(ss, ageStr, '-');
				getline(ss, phoneNumberStr, '-');
				getline(ss, userIdStr, '-');
				getline(ss, userPasswordStr, '-');
				getline(ss, genderStr, '-');
				getline(ss, address, '-');

				GenderT gender = Other;
				int age = 0, userId = 0, userPassword = 0;
				unsigned long long phoneNumber = 0;

				// Try conversion. If anything fails, catch and return false.
				try
				{
					age = std::stoi(ageStr);
					phoneNumber = std::stoull(phoneNumberStr);
					userId = std::stoi(userIdStr);
					userPassword = std::stoi(userPasswordStr);
					gender = static_cast<GenderT>(std::stoi(genderStr));
				}
				catch (const std::exception&)
				{
					return false;
				}

				if (gender == 1)
					gender = Male;
				if (gender == 2)
					gender = Female;
				// All required data is valid. Now create user and load it into vUsers.
				User user(firstName, lastName, age, phoneNumber, userId, userPassword, gender, address);
				vUsers.push_back(user);
				AddUser();
				User::AddUser();
			}
			in.close();
			return true;
		}
		catch (std::exception& e)
		{
			ExitWithMessage(e.what());
		}
		return false;
	}

	/**
	 * \brief Write vUsers into user_data file.
	 *
	 * \return True on success, false otherwise.
	 */
	static bool WriteUserDataFile()
	{
		try
		{
			ofstream out("user_data.txt", std::ios::trunc);
			if (!out.is_open())
				return false;
			for (User& user : vUsers)
				out << user;
			out.close();
			User::AddUser();
			Account::AddAccount();
			return true;
		}
		catch (std::exception& e)
		{
			ExitWithMessage(e.what());
		}
		return false;
	}

	/**
	 * \brief Write user to user_data file.
	 * \param user to write.
	 * \return True on success, false otherwise.
	 */
	static bool WriteUserDataFile(const User& user)
	{
		try
		{
			ofstream out("user_data.txt", std::ios::app);
			if (!out.is_open())
				return false;
			out << user;
			out.close();

			User::AddUser();
			Account::AddAccount();
			AddUser();
			return true;
		}
		catch (std::exception& e)
		{
			ExitWithMessage(e.what());
		}
		return false;
	}

	/**
	 * \brief Write the vAccountDetails to the account_data file.
	 *
	 * \return True on success, false otherwise.
	 */
	static bool WriteAccountDataFile()
	{
		try
		{
			ofstream out("account_data.txt", std::ios::trunc);
			if (!out.is_open())
				return false;

			for (const auto& [AccountNumber, UserId, UserPassword, Balance] : vAccountDetails)
			{
				out << AccountNumber << '-' <<
					UserId << '-' <<
					UserPassword << '-' <<
					Balance << '\n';
			}
			out.close();
			return true;
		}
		catch (std::exception& e)
		{
			ExitWithMessage(e.what());
		}
		return false;
	}

	/**
	 * \brief Write the accountDetails_t to the account_data file.
	 *
	 * \param account object to write.
	 * \return True on success, false otherwise.
	 */
	static bool WriteAccountDataFile(const AccountDetailsT& account)
	{
		try
		{
			ofstream out("account_data.txt", std::ios::app);
			if (!out.is_open())
				return false;
			out << account.AccountNumber << '-' <<
				account.UserId << '-' <<
				account.UserPassword << '-' <<
				account.Balance << '\n';
			out.close();
			Account::AddAccount();
			return true;
		}
		catch (std::exception& e)
		{
			ExitWithMessage(e.what());
		}
		return false;
	}

	/**
	 * \brief Load the account_data file into vAccountDetails.
	 *
	 * \return True on success, false otherwise.
	 */
	static bool LoadUserAccountFile()
	{
		try
		{
			ifstream in("account_data.txt");
			// Create the file if does not exist.
			if (!in.good())
			{
				ofstream out("account_data.txt", std::ios::trunc);
				out.close();
			}

			string line;
			while (getline(in, line))
			{
				if (line.empty()) // Skip empty lines
					continue;
				// Iterate over every line and load it into a string.
				// then convert the string into corresponding types.
				std::stringstream ss(line);
				string accountNumberStr, userIdStr, userPasswordStr, balanceStr;
				getline(ss, accountNumberStr, '-');
				getline(ss, userIdStr, '-');
				getline(ss, userPasswordStr, '-');
				getline(ss, balanceStr, '-');

				int userId = 0, balance = 0;
				unsigned long long accountNumber = 0, userPassword = 0;
				// Try conversion. If anything fails, catch and return false;
				try
				{
					accountNumber = std::stoull(accountNumberStr);
					userPassword = std::stoull(userPasswordStr);
					userId = std::stoi(userIdStr);
					balance = std::stoi(balanceStr);
				}
				catch (const std::exception&)
				{
					return false;
				}
				// All required data is valid. Now create account and load it into vAccountDetails.
				AccountDetailsT account{ NULL,NULL,NULL,NULL };
				account.AccountNumber = accountNumber;
				account.UserId = userId;
				account.UserPassword = userPassword;
				account.Balance = balance;
				vAccountDetails.push_back(account);
				Account::AddAccount();
			}
			in.close();
			return true;
		}
		catch (std::exception& e)
		{
			ExitWithMessage(e.what());
		}
		return false;
	}

	/**
	 * \brief Performs very basic level integrity check on user_data and user_accounts,
	 * then binds and synchronizes their data.
	 *
	 * \return true on success, false otherwise.
	 */
	[[nodiscard]] static bool BindUserData()
	{
		try
		{
			// Perform a security check:
			// Number of accounts and users must match
			if (User::GetTotalUsers() != Account::GetTotalAccounts())
				return false;

			for (size_t i = 0; i < GetTotalUserCount(); i++)
			{
				if (vAccountDetails[i].UserId != vUsers[i].GetUserId())
					return false;
				if (!vUsers[i].SetAccountNumber(vAccountDetails[i].AccountNumber))
					return false;
				if (!vUsers[i].SetBalance(vAccountDetails[i].Balance))
					return false;
			}
			return true;
		}
		catch (std::exception& e)
		{
			ExitWithMessage(e.what());
		}
		return false;
	}


	/**
	 * \brief Synchronizes the User data with Account Data.
	 *
	 * \return True on success, false otherwise.
	 */
	static bool SyncUserAccountData()
	{
		try
		{
			int i = 0;
			for (auto userItr = vUsers.begin(); userItr != vUsers.end(); ++userItr, i++)
			{
				vAccountDetails[i].AccountNumber = userItr->GetAccountNumber();
				vAccountDetails[i].Balance = userItr->GetBalance();
				vAccountDetails[i].UserId = userItr->GetUserId();
				vAccountDetails[i].UserPassword = userItr->GetUserPassword();
			}
			return true;
		}
		catch (std::exception& e)
		{
			ExitWithMessage(e.what());
		}
		return false;
	}

#pragma region Accessors and Mutators

	/**
	* \brief Add one user to the bank.
	* \return true on success.
	*/
	static bool AddUser()
	{
		TotalUsers++;
		return true;
	}

	/**
	 * \brief Remove one user from the bank.
	 * \return true on success.
	 */
	static bool RemoveUser()
	{
		if (TotalUsers == 0)
			return false;
		TotalUsers--;
		return true;
	}

	[[nodiscard]] static unsigned int GetTotalUserCount() { return TotalUsers; }

	/**
	 * \brief Sets the TotalUserCount to the given value.
	 * \param count The count to set the value to.
	 * \return True on success, false otherwise.
	 */
	static bool SetTotalUserCount(const unsigned int count)
	{
		TotalUsers = count;
		return true;
	}

#pragma endregion
};

inline Bank bank;

unsigned int Bank::TotalUsers = 0;
