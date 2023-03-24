// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Bank class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#pragma once

#ifndef BANK_H_
#define BANK_H_


#include <fstream>
#include <string>
#include <vector>
#include "User.h"

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
public:
	/**
	 * \brief Loads the user_data file into vUsers.
	 *
	 * \return True on success, false otherwise.
	 */
	static auto LoadUserDataFile() -> bool;

	/**
	 * \brief Write vUsers into user_data file.
	 *
	 * \return True on success, false otherwise.
	 */
	static auto WriteUserDataFile() -> bool;

	/**
	 * \brief Write user to user_data file.
	 * \param user to write.
	 * \return True on success, false otherwise.
	 */
	static auto WriteUserDataFile(const User& user) -> bool;

	/**
	 * \brief Write the vAccountDetails to the account_data file.
	 *
	 * \return True on success, false otherwise.
	 */
	static auto WriteAccountDataFile() -> bool;

	/**
	 * \brief Write the accountDetails_t to the account_data file.
	 *
	 * \param account object to write.
	 * \return True on success, false otherwise.
	 */
	static auto WriteAccountDataFile(const AccountDetailsT& account) -> bool;

	/**
	 * \brief Load the account_data file into vAccountDetails.
	 *
	 * \return True on success, false otherwise.
	 */
	static auto LoadUserAccountFile() -> bool;

	/**
	 * \brief Performs very basic level integrity check on user_data and user_accounts,
	 * then binds and synchronizes their data.
	 *
	 * \return true on success, false otherwise.
	 */
	[[nodiscard]] static auto BindUserData() -> bool;

	/**
	 * \brief Synchronizes the User data with Account Data.
	 *
	 * \return True on success, false otherwise.
	 */
	static auto SyncUserAccountData() -> bool;

#pragma region Getters and Setters

	/**
	* \brief Add one user to the bank.
	* \return true on success.
	*/
	static auto AddUser() -> bool;

	/**
	 * \brief Remove one user from the bank.
	 * \return true on success.
	 */
	static auto RemoveUser() -> bool;

	[[nodiscard]] static auto GetTotalUserCount() -> unsigned int;

	/**
	 * \brief Sets the TotalUserCount to the given value.
	 * \param count The count to set the value to.
	 * \return True on success, false otherwise.
	 */
	static auto SetTotalUserCount(unsigned int count) -> bool;

#pragma endregion

private:
	static unsigned int TotalUsers;
};

inline Bank bank;

#endif
