// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Bank class for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh


#include "Bank.h"

#include <sstream>

#include "Bean Bank.h"

unsigned int Bank::TotalUsers{ 0 };

auto Bank::LoadUserDataFile() -> bool
{
	try
	{
		ifstream in("user_data.txt");

		// Create the file if does not exist.
		if (!in.good())
		{
			ofstream out("user_data.txt", std::ios::trunc);
			out.close();
		}
		string line;
		while (getline(in, line))
		{
			if (line.empty()) // skip empty lines
				continue;

			// Iterate over every line and load it into a string.
			// then convert the string into corresponding types.
			std::stringstream ss(line);
			string firstName, lastName, address, ageStr, userIdStr,
				userPasswordStr, phoneNumberStr, genderStr;
			getline(ss, firstName, '-');
			getline(ss, lastName, '-');
			getline(ss, ageStr, '-');
			getline(ss, phoneNumberStr, '-');
			getline(ss, userIdStr, '-');
			getline(ss, userPasswordStr, '-');
			getline(ss, genderStr, '-');
			getline(ss, address, '-');

			auto gender = GenderT::Other;
			int age = 0, userId = 0, userPassword = 0;
			unsigned long long phoneNumber = 0;

			// Try conversion. If anything fails, catch and return false.
			try
			{
				age = std::stoi(ageStr);
				phoneNumber = std::stoull(phoneNumberStr);
				userId = std::stoi(userIdStr);
				userPassword = std::stoi(userPasswordStr);
				gender = static_cast<GenderT>(std::stoi(genderStr));
			}
			catch (const std::exception&) { return false; }

			if (static_cast<int> (gender) == 1)
				gender = GenderT::Male;
			if (static_cast<int> (gender) == 2)
				gender = GenderT::Female;
			// All required data is valid. Now create user and load it into vUsers.
			User user(firstName, lastName, age, phoneNumber, userId, userPassword, gender,
				address);
			vUsers.push_back(user);
			AddUser();
			User::AddUser();
		}
		in.close();
		return true;
	}
	catch (std::exception& e) { ExitWithMessage(e.what()); }
	return false;
}

auto Bank::WriteUserDataFile() -> bool
{
	try
	{
		ofstream out("user_data.txt", std::ios::trunc);
		if (!out.is_open())
			return false;
		for (User& user : vUsers)
			out << user;
		out.close();
		User::AddUser();
		Account::AddAccount();
		return true;
	}
	catch (std::exception& e) { ExitWithMessage(e.what()); }
	return false;
}

auto Bank::WriteUserDataFile(const User& user) -> bool
{
	try
	{
		ofstream out("user_data.txt", std::ios::app);
		if (!out.is_open())
			return false;
		out << user;
		out.close();

		User::AddUser();
		Account::AddAccount();
		AddUser();
		return true;
	}
	catch (std::exception& e) { ExitWithMessage(e.what()); }
	return false;
}

auto Bank::WriteAccountDataFile() -> bool
{
	try
	{
		ofstream out("account_data.txt", std::ios::trunc);
		if (!out.is_open())
			return false;

		for (const auto& [AccountNumber, UserId, UserPassword, Balance] : vAccountDetails)
		{
			out << AccountNumber << '-' <<
				UserId << '-' <<
				UserPassword << '-' <<
				Balance << '\n';
		}
		out.close();
		return true;
	}
	catch (std::exception& e) { ExitWithMessage(e.what()); }
	return false;
}

auto Bank::WriteAccountDataFile(const AccountDetailsT& account) -> bool
{
	try
	{
		ofstream out("account_data.txt", std::ios::app);
		if (!out.is_open())
			return false;
		out << account.AccountNumber << '-' <<
			account.UserId << '-' <<
			account.UserPassword << '-' <<
			account.Balance << '\n';
		out.close();
		Account::AddAccount();
		return true;
	}
	catch (std::exception& e) { ExitWithMessage(e.what()); }
	return false;
}

auto Bank::LoadUserAccountFile() -> bool
{
	try
	{
		ifstream in("account_data.txt");
		// Create the file if does not exist.
		if (!in.good())
		{
			ofstream out("account_data.txt", std::ios::trunc);
			out.close();
		}

		string line;
		while (getline(in, line))
		{
			if (line.empty()) // Skip empty lines
				continue;
			// Iterate over every line and load it into a string.
			// then convert the string into corresponding types.
			std::stringstream ss(line);
			string accountNumberStr, userIdStr, userPasswordStr, balanceStr;
			getline(ss, accountNumberStr, '-');
			getline(ss, userIdStr, '-');
			getline(ss, userPasswordStr, '-');
			getline(ss, balanceStr, '-');

			int userId = 0, balance = 0;
			unsigned long long accountNumber = 0, userPassword = 0;
			// Try conversion. If anything fails, catch and return false;
			try
			{
				accountNumber = std::stoull(accountNumberStr);
				userPassword = std::stoull(userPasswordStr);
				userId = std::stoi(userIdStr);
				balance = std::stoi(balanceStr);
			}
			catch (const std::exception&) { return false; }
			// All required data is valid. Now create account and load it into vAccountDetails.
			AccountDetailsT account{ NULL,NULL,NULL,NULL };
			account.AccountNumber = accountNumber;
			account.UserId = userId;
			account.UserPassword = userPassword;
			account.Balance = balance;
			vAccountDetails.push_back(account);
			Account::AddAccount();
		}
		in.close();
		return true;
	}
	catch (std::exception& e) { ExitWithMessage(e.what()); }
	return false;
}

auto Bank::BindUserData() -> bool
{
	try
	{
		// Perform a security check:
		// Number of accounts and users must match
		if (User::GetTotalUsers() != Account::GetTotalAccounts())
			return false;

		for (size_t i = 0; i < GetTotalUserCount(); i++)
		{
			if (vAccountDetails[i].UserId != vUsers[i].GetUserId())
				return false;
			if (!vUsers[i].SetAccountNumber(vAccountDetails[i].AccountNumber))
				return false;
			if (!vUsers[i].SetBalance(vAccountDetails[i].Balance))
				return false;
		}
		return true;
	}
	catch (std::exception& e) { ExitWithMessage(e.what()); }
	return false;
}

auto Bank::SyncUserAccountData() -> bool
{
	try
	{
		int i = 0;
		for (auto userItr = vUsers.begin(); userItr != vUsers.end(); ++userItr, i++)
		{
			vAccountDetails[i].AccountNumber = userItr->GetAccountNumber();
			vAccountDetails[i].Balance = userItr->GetBalance();
			vAccountDetails[i].UserId = userItr->GetUserId();
			vAccountDetails[i].UserPassword = userItr->GetUserPassword();
		}
		return true;
	}
	catch (std::exception& e) { ExitWithMessage(e.what()); }
	return false;
}

auto Bank::AddUser() -> bool
{
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
	TotalUsers = count;
	return true;
}
