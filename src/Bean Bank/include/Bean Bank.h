// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: This file contains the core logic of the Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#pragma once

#ifndef BEAN_BANK_H_
#define BEAN_BANK_H_

#include <string>


/** Consume newline character caused by previous input stream.
* \note Must be used inside an empty scope to prevent redeclaration.
 */
#define CONSUME_NEWLINE_CHARACTER string trash_; getline(cin, trash_);

 /** \note Soft pause the execution, wait for user to press enter.
 * Must be used inside an empty scope to prevent redeclaration.
 */
#define PAUSE string trash_; getline(cin, trash_);

auto SetConsoleColor(uint8_t) -> void;
auto ExitWithMessage(const std::string&) -> void;
auto ClearScreen() -> void;
auto ShowAppInfo() -> void;
auto ShowMenu() -> void;
auto NewAccountWizard() -> void;
auto CheckBalanceWizard() -> void;
auto DepositFundsWizard() -> void;
auto WithdrawFundsWizard() -> void;
auto CloseAccountWizard() -> void;
auto ShowAllAccountsWizard() -> void;

#endif
