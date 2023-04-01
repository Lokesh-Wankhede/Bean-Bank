// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: Banking service manager/handler for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#include "BankingService.h"

#include "CoreException.h"
#include "Logger.h"
#include "sqlite3.h"


auto BankingService::GetInstance() -> BankingService&
{
	static BankingService instance;
	return instance;
}

auto BankingService::Initialize() -> bool
{
	LOGGER->debug("Initializing database.");
	try
	{
		// open the database file
		if (const int result = sqlite3_open("BeanBank.db", &MBankDatabase); result != SQLITE_OK)
			throw DatabaseInitializationException(sqlite3_errmsg(MBankDatabase));
	}
	catch (DatabaseInitializationException&)
	{
		LOGGER->critical("Exception caught: DatabaseInitializationException");
		sqlite3_close(MBankDatabase);
		return false;
	}

	LOGGER->debug("Database initialized successfully.");

	return true;
}
