/**
 * Copyright: LogicalLokesh. All rights reserved.
 *
 * File:   main.h
 *
 * Brief: Welcome to the Bean Bank!
 *        The bank that's here to help you save your beans and grow your wealth.
 *        With our state-of-the-art banking system, written in the latest
 *        and greatest version of C++, you can be sure that your beans are in safe hands.
 *        We've got all the features you need, like account creation, depositing
 *        and withdrawing funds, checking your balance and even closing your
 *        account (just in case you need to escape from the bean-holding life).
 *        And with our top-notch security features, you can be sure that your
 *        beans will be safe from even the most determined bean thieves.
 *        So why wait? Open an account with Bean Bank today and start saving your beans!
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
