// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: Database manager/handler for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

// ReSharper disable CppClangTidyModernizeUseEqualsDelete
// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions

#pragma once

#include "sqlite3.h"

/**
 * \brief Database manager/handler.
 * \note DatabaseManager follows a singleton pattern, use GetInstance();
 */
class DatabaseManager
{
public:

	/**
	 * \brief Create the instance, or return the reference if already instantiated.
	 * \return A reference to DatabaseManager instance.
	 */
	static auto GetInstance() -> DatabaseManager&;

	/**
	 * \brief Initializes the database connection.
	 * \return true if successful, false otherwise.
	 */
	auto InitializeDatabase() -> bool;


	/**
	 * \brief Constructs the bare minimum and skeleton of database.
	 * \return true if successful, false otherwise.
	 */
	auto ConstructDataTemplate() -> bool;

private:

	// the core database, holding all of the data of bank
	sqlite3* MBankDatabase = nullptr;

	DatabaseManager() = default; // private constructor to prevent direct instantiation
	// delete copy constructor
	DatabaseManager(const DatabaseManager&) = delete;
	// delete assignment operator
	auto operator=(const DatabaseManager&) ->
		DatabaseManager & = delete;
};


/*auto Callback(void* data, const int argc, char** argv, char** azColName) -> int
{
	for (int i = 0; i < argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}*/
