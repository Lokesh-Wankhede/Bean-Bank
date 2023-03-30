// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: This file contains the core logic of the Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#pragma once

#include <string>

// holds the version info
using VersionInfoT = struct
{
	int Major, Minor, Build;
};

/**
 * \brief Gets version info of the current exe using black magic and ancient incantations.
 * \return VersionInfoT - Version info of the Bean Bank.
 */
auto GetVersionInfo() -> VersionInfoT;

/** Consume newline character caused by previous input stream.
* \note Must be used inside an empty scope to prevent redeclaration.
 */
#define CONSUME_NEWLINE_CHARACTER string trash_; getline(cin, trash_);

/** \note Soft pause the execution, wait for user to press enter.
* Must be used inside an empty scope to prevent redeclaration.
*/
#define PAUSE string trash_; getline(cin, trash_);

/**
* \brief Changes the color of the console.
*
* \param colorCode (1 Blue) (2 Green) (3 Teal) (4 Red) (5 Purple) (6 Yellow) (7 White) (8 Grey)
*/
auto SetConsoleColor(uint8_t colorCode) -> void;

/**
 * \brief Exit the program with custom message screen.
 *
 * \param message string to be displayed
 */
[[noreturn]] auto ExitWithMessage(const std::string& message) -> void;

/**
 * \brief Clears the console screen.
 */
auto ClearScreen() -> void;

/**
 * \brief Clears the console and shows application information and version info.
 */
auto ShowAppInfo() -> void;

/**
 * \brief Clears the console and shows the main menu.
 */
auto ShowMenu() -> void;

/**
 * \brief Creates a new user account.
 */
auto NewAccountWizard() -> void;

/**
 * \brief Check user balance wizard.
 */
[[noreturn]] auto CheckBalanceWizard() -> void;

/**
 * \brief Wizard for depositing funds.
 */
auto DepositFundsWizard() -> void;


/**
 * \brief Wizard for withdrawing funds.
 */
auto WithdrawFundsWizard() -> void;


/**
 * \brief Wizard for closing an account.
 */
auto CloseAccountWizard() -> void;

/**
 * \brief Wizard for displaying basic info of all users.
 */
auto ShowAllAccountsWizard() -> void;
