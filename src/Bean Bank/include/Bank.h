// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Bank class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;


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

private:
	Bank() = default; // private constructor to prevent direct instantiation
	// delete copy constructor
	Bank(const Bank&) = delete; // NOLINT(modernize-use-equals-delete)
	// delete assignment operator
	auto operator=(const Bank&)->Bank & = delete; // NOLINT(modernize-use-equals-delete)
};
