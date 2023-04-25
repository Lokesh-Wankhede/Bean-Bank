// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Bank class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh


#include "Bank.h"

auto Bank::GetInstance() -> Bank&
{
	static Bank instance;
	return instance;
}
