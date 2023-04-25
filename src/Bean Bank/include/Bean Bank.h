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

// Consume newline character caused by previous input stream.
#define CONSUME_NEWLINE_CHARACTER string trash_; getline(cin, trash_);

// Soft pause the execution, wait for user to press enter.
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


template <typename ValidationFn>
auto GetUserInput(const std::string& prompt, ValidationFn validateFn) -> std::string;

/**
 * \brief Gets the input from user, but does not perform validation.
 * \param prompt text to prompt
 * \return User Input.
 */
auto GetUserInputNoValidation(const std::string& prompt) -> std::string;

/**
 * \brief Opens support page in the browser.
 */
auto OpenSupportPage() -> void;

/**
 * \brief Clears the console and shows application information and version info.
 */
auto ShowAppInfo() -> void;

/**
 * \brief Clears the console and opens the home page.
 */
auto OpenHomePage() -> void;

/**
 * \brief Opens the user dashboard area.
 * \return true if user want to visit homepage, false if user want to exit the app.
 */
auto OpenUserDashboard() -> bool;

/**
 * \brief Wizard for opening a new account.
 */
auto OpenNewAccountWizard() -> void;
