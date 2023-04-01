// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: Banking service manager/handler for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

// ReSharper disable CppClangTidyModernizeUseEqualsDelete
// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions

#pragma once

#include "sqlite3.h"

/**
 * \brief Banking service manager/handler.
 * \note BankingService follows a singleton pattern, use GetInstance();
 */
class BankingService
{
public:

	/**
	 * \brief Create the instance, or return the reference if already instantiated.
	 * \return A reference to BankingService instance.
	 */
	static auto GetInstance() -> BankingService&;

	auto Initialize() -> bool;

private:


	// the core database, holding all of the data of bank
	sqlite3* MBankDatabase = nullptr;

	BankingService() = default; // private constructor to prevent direct instantiation
	// delete copy constructor
	BankingService(const BankingService&) = delete;
	// delete assignment operator
	auto operator=(const BankingService&) ->
		BankingService & = delete;
};