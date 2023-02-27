/**
 * Copyright: LogicalLokesh. All rights reserved.
 *
 * Note:  Bean Bank requires C++ standard 20 or above,
 *        and designed to work on Windows operating system.
 *
 * Author: LogicalLokesh (github.com/LogicalLokesh)
 * Date:   January 2023
**/

#pragma once

/** Consume newline character caused by previous input stream.
* \note Must be used inside an empty scope to prevent redeclaration.
 */
#define CONSUME_NEWLINE_CHARACTER string trash_; getline(cin, trash_);

 /** \note Soft pause the execution, wait for user to press enter.
  * Must be used inside an empty scope to prevent redeclaration.
  */
#define PAUSE string trash_; getline(cin, trash_);

void SetConsoleColor(uint8_t);
void ExitWithMessage(const string&);
void ClearScreen();
void ShowAppInfo();
void ShowMenu();
void NewAccountWizard();
void CheckBalanceWizard();
void DepositFundsWizard();
void WithdrawFundsWizard();
void CloseAccountWizard();
void ShowAllAccountsWizard();
