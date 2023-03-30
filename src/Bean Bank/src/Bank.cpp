// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Bank class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh


#include "Bank.h"

unsigned int Bank::TotalUsers{};

auto Bank::GetInstance() -> Bank&
{
	static Bank instance;
	return instance;
}

#pragma region Getters and Setters

auto Bank::AddUser() -> bool
{
	// TODO: Implement a validity/safety check
	TotalUsers++;
	return true;
}

auto Bank::RemoveUser() -> bool
{
	if (TotalUsers == 0)
		return false;
	TotalUsers--;
	return true;
}

auto Bank::GetTotalUserCount() -> unsigned { return TotalUsers; }

auto Bank::SetTotalUserCount(const unsigned count) -> bool
{
	// TODO: Implement a validity/safety check
	TotalUsers = count;
	return true;
}

#pragma endregion
