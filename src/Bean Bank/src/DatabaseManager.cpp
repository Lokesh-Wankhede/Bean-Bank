// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: Database manager/handler for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#include "DatabaseManager.h"

#include "CoreException.h"
#include "Logger.h"
#include "sqlite3.h"


auto DatabaseManager::GetInstance() -> DatabaseManager&
{
	static DatabaseManager instance;
	return instance;
}

auto DatabaseManager::InitializeDatabase() -> bool
{
	LOGGER->debug("[DatabaseManager] [InitializeDatabase] Initializing database...");
	try
	{
		// open the database file
		if (const int result = sqlite3_open("BeanBank.db", &MBankDatabase); result != SQLITE_OK)
			throw DatabaseInitializationException(sqlite3_errmsg(MBankDatabase));
	}
	catch (DatabaseInitializationException&)
	{
		LOGGER->critical(
			"[DatabaseManager] [InitializeDatabase] Exception caught: DatabaseInitializationException");
		sqlite3_close(MBankDatabase);
		return false;
	}

	LOGGER->debug("[DatabaseManager] [InitializeDatabase] Database initialized successfully.");
	return true;
}


auto DatabaseManager::ConstructDataTemplate() -> bool
{
	LOGGER->debug(
		"[DatabaseManager] [ConstructDataTemplate] Reconstructing data template started...");

	// make sure the database is initialized
	if (!InitializeDatabase())
	{
		LOGGER->error(
			"[DatabaseManager] [ConstructDataTemplate] Data template construction failed. "
			"Database is not initialized.");
		return false;
	}

	LOGGER->debug(
		"[DatabaseManager] [ConstructDataTemplate] Data template construction success.");

	// create main the table if not already exists
	if (sqlite3_exec(MBankDatabase,
		"CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, first_name VARCHAR(255),"
		"middle_name VARCHAR(255), last_name VARCHAR(255), age INT, phone_number BIGINT, gender VARCHAR(10),"
		"address VARCHAR(255), user_password VARCHAR(255), m_pin BIGINT, balance BIGINT);",
		nullptr, nullptr, nullptr) != SQLITE_OK)
	{
		LOGGER->error(
			"[DatabaseManager] [ConstructDataTemplate] Data template construction failed. {}",
			sqlite3_errmsg(MBankDatabase));
		return false;
	}

	// close the database
	if (sqlite3_close(MBankDatabase) == SQLITE_OK)
		return true;

	// database is not closed successfully
	LOGGER->error("[DatabaseManager] [ConstructDataTemplate] {}", sqlite3_errmsg(MBankDatabase));
	return false;
}
