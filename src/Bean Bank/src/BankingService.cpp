// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The BankingService class.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh


#include "BankingService.h"

auto BankingService::GetInstance() -> BankingService&
{
	static BankingService instance;
	return instance;
}
