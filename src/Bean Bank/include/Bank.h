// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Bank class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#pragma once

#include <string>
#include <vector>
#include "User.h"

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;


/**
 * \brief Bank class follows singleton pattern, Use GetInstance().
 */
class Bank // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
	/**
	 * \brief Create the instance, or return the reference if already instantiated.
	 * \return A reference to bank instance.
	 */
	static auto GetInstance() -> Bank&;

#pragma region Getters and Setters

	/**
	* \brief Add one user to the bank.
	* \return true on success, false otherwise.
	*/
	static auto AddUser() -> bool;

	/**
	 * \brief Remove one user from the bank.
	 * \return true on success, false otherwise.
	 */
	static auto RemoveUser() -> bool;

	[[nodiscard("Please handle the return value.")]] static auto
	GetTotalUserCount() -> unsigned int;

	/**
	 * \brief Sets the TotalUserCount to the given value.
	 * \param count The count to set the value to.
	 * \return true on success, false otherwise.
	 */
	static auto SetTotalUserCount(unsigned int count) -> bool;

#pragma endregion

private:
	Bank() = default; // private constructor to prevent direct instantiation
	// delete copy constructor
	Bank(const Bank&) = delete; // NOLINT(modernize-use-equals-delete)
	// delete assignment operator
	auto operator=(const Bank&) -> Bank& = delete; // NOLINT(modernize-use-equals-delete)

	static unsigned int TotalUsers;
};
