// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: This file contains the core logic of the Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#include "Bean Bank.h"

#include <Windows.h>
#pragma comment(lib, "version.lib") // for version info, used in GetVersionInfo();
#include <iostream>
#include <string>
#include "Account.h"
#include "Bank.h"
#include "CoreException.h"
#include "Logger.h"
#include "User.h"


using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;

auto main() -> int
{
	InitializeLogger();

	// don't mess with this code, it's on its coffee break right now
	// get user's input with some 90s flair
	string userChoice;
	int choice;

	do
	{
		// show what's in the menu
		ShowMenu();

		// get user's input and check if it's valid
		if (!getline(cin, userChoice))
		{
			// if user input is invalid, politely tell them to fix it
			cout << "\n   Invalid input, please enter a valid choice.\n\n";
			continue;
		}

		// use istringstream to check if user entered a valid choice
		if (std::istringstream iss(userChoice); !(iss >> choice) || iss.peek() != EOF)
		{
			cout << "\n   Invalid input, please enter a valid choice.\n\n";
			continue;
		}

		// switch statement to handle user's choice
		switch (choice)
		{
		case 1:
			cout << "\n   Check Balance Wizard\n\n";
			break;
		case 2:
			cout << "\n   Deposit Funds Wizard\n\n";
			break;
		case 3:
			cout << "\n   Withdraw Funds Wizard\n\n";
			break;
		case 4:
			cout << "\n   New Account Wizard\n\n";
			break;
		case 5:
			cout << "\n   Close Account Wizard\n\n";
			break;
		case 6:
			cout << "\n   Show All Accounts Wizard\n\n";
			break;
		case 7:
			cout << "\n   Opening Support page in your browser!\n\n";
			ShellExecute(nullptr, L"open", L"https://logicallokesh.net/bean-bank", nullptr, nullptr,
				SW_SHOWNORMAL);
			ExitWithMessage("WTF bro!");
			break;
		case 8:
			// user has decided to exit the program
			return 0;

		default:
			// if user enters something other than a valid choice, they need their glasses
			cout << "\n   Invalid input, please enter a valid choice.\n\n";
		}

		// wait for two seconds before showing the menu again
		Sleep(2000);
	} while (true);
}

auto SetConsoleColor(const uint8_t colorCode) -> void
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

auto ExitWithMessage(const string& message) -> void
{
	MessageBeep(MB_ICONERROR);
	SetConsoleTitleW(L"Bean Bank | Error");
	ShowAppInfo();
	cout << "\n   Something went wrong :(\n";
	SetConsoleColor(4);
	cout << "\n   Error: ";
	SetConsoleColor(6);
	cout << message;
	cout << "\n   Visit support page to get help with this error.";
	SetConsoleColor(7);
	cout << "\n\n   If you can't find the solution, please report this error via:" <<
		"\n   Website: logicallokesh.net\\contact" <<
		"\n   E-mail:  support@logicallokesh.net" <<
		"\n   Instagram: @logicallokesh" <<
		"\n\n   Your feedback is really appreciated." <<
		"\n   Thank You." <<
		"\n\n   Press enter to exit.";
	{
		PAUSE
	}
	std::quick_exit(-1);
}

auto GetVersionInfo() -> VersionInfoT
{
	wchar_t path[MAX_PATH];
	// get the path of the current exe
	GetModuleFileName(nullptr, path, MAX_PATH);
	DWORD handle = 0;
	// set default version to 0.0.0
	VersionInfoT versionInfo{};

	// if we can get the version info size, we might be able to get the version info
	if (const DWORD size = GetFileVersionInfoSize(path, &handle))
	{
		// allocate a buffer to hold the version info
		const auto buffer = new char[size];
		if (GetFileVersionInfo(path, handle, size, buffer))
		{
			// get the fixed file info from the buffer
			VS_FIXEDFILEINFO* fileInfo = nullptr;
			UINT len;
			if (VerQueryValue(buffer, L"\\", reinterpret_cast<LPVOID*>(&fileInfo), &len))
			{
				// set the version info based on the product version
				versionInfo.Major = HIWORD(fileInfo->dwProductVersionMS);
				versionInfo.Minor = LOWORD(fileInfo->dwProductVersionMS);
				versionInfo.Build = HIWORD(fileInfo->dwProductVersionLS);
			}
		}
		// thank you, buffer! You served us well, but now it's time to go back to the void
		delete[] buffer;
	}
	// return the version info we found, or the default one if we didn't find anything
	return versionInfo;
}

auto ClearScreen() -> void
{
	const HANDLE gHConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	constexpr COORD homeCoords = { 0, 0 };

	if (gHConsole == INVALID_HANDLE_VALUE) return;

	// Get the number of cells in the current buffer
	if (!GetConsoleScreenBufferInfo(gHConsole, &csbi)) return;
	const DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire buffer with spaces
	if (!FillConsoleOutputCharacter(
		gHConsole,
		static_cast<TCHAR>(' '),
		cellCount,
		homeCoords,
		&count
	))
		return;

	// Fill the entire buffer with the current colors and attributes
	if (!FillConsoleOutputAttribute(
		gHConsole,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	))
		return;

	// Move the cursor home
	SetConsoleCursorPosition(gHConsole, homeCoords);
}

auto ShowAppInfo() -> void
{
	ClearScreen();
	SetConsoleColor(3);
	cout << "\n   ------------ Bean Bank ------------";
	SetConsoleColor(2);
	const auto [Major, Minor, Build] = GetVersionInfo();
	cout << "\n             Version: " << Major << "." << Minor << "." << Build;
	SetConsoleColor(3);
	cout << "\n     Crafted with ";
	SetConsoleColor(4);
	cout << static_cast<char>(3);
	SetConsoleColor(3);
	cout << " by LogicalLokesh" << endl;
	cout << "   -----------------------------------\n";
	SetConsoleColor(7);
}

auto ShowMenu() -> void
{
	SetConsoleTitleW(L"Bean Bank");
	ClearScreen();
	ShowAppInfo();
	cout << "\n   Welcome to the Bean Bank!" << "\n"
		<< "\n   Main Menu: " << "\n"
		<< "   1. Balance Inquiry" << "\n"
		<< "   2. Deposit Funds" << "\n"
		<< "   3. Withdrawal" << "\n"
		<< "   4. Create New Account" << "\n"
		<< "   5. Close An Account" << "\n"
		<< "   6. Show All Accounts" << "\n"
		<< "   7. Support\n"
		<< "   8. Quit\n" << "\n"
		<< "   Enter your choice: ";
}

auto NewAccountWizard() -> void
{
	User user;
	string firstName, lastName, address;
	int age{ 0 }, userId{ 0 }, userPassword{ 0 };
	unsigned long long phoneNumber;

	ShowAppInfo();
	SetConsoleTitleW(L"Bean Bank | Create New Account");
	cout << "\n   - Create New Account - \n" << endl;

#pragma region Get Details

	// Set first name
	while (true)
	{
		SetConsoleColor(7);
		cout << "   First Name: ";
		getline(cin, firstName);
		if (user.SetFirstName(firstName))
			break;
		SetConsoleColor(4);
		cout << "   Invalid Name. It should not contain any numbers, special characters, or spaces,"
			<< "\n   and it should be less than 20 characters. " << endl;
		Sleep(3000);
	}
	// Set last name
	while (true)
	{
		SetConsoleColor(7);
		cout << "   Last Name: ";
		getline(cin, lastName);
		if (user.SetLastName(lastName))
			break;
		SetConsoleColor(4);
		cout << "   Invalid Name. It should not contain any numbers, special characters, or spaces,"
			<< "\n   and it should be less than 20 characters." << endl;
		Sleep(3000);
	}
	// Set age
	while (true)
	{
		string ageStr;
		SetConsoleColor(7);
		cout << "   Age: ";
		cin >> age;
		{
			CONSUME_NEWLINE_CHARACTER
		}
		if (user.SetAge(age))
			break;
		if (age < 18)
		{
			SetConsoleColor(4);
			cout << "   You must be at least 18 years old to create an account." << endl;
			Sleep(3000);
			continue;
		}
		if (age > 200)
		{
			SetConsoleColor(4);
			cout << "   Are you over 200? Check your age again." << endl;
			Sleep(3000);
		}
	}
	// Set gender
	string gender;
	while (true)
	{
		SetConsoleColor(7);
		cout << "   1- Male, 2- Female, 3- Other\n";
		cout << "   Gender: ";
		getline(cin, gender);
		if (gender.empty() || gender != "1" && gender != "2" && gender != "3")
		{
			SetConsoleColor(4);
			cout << "   Please choose correct option." << endl;
			Sleep(3000);
			continue;
		}
		if (gender == "1")
			user.SetGender(GenderT::Male);
		if (gender == "2")
			user.SetGender(GenderT::Female);
		if (gender == "3")
			user.SetGender(GenderT::Other);
		break;
	}
	// Set phone number
	while (true)
	{
		SetConsoleColor(7);
		cout << "   Phone Number: ";
		cin >> phoneNumber;
		{
			CONSUME_NEWLINE_CHARACTER
		}
		if (user.SetPhoneNumber(phoneNumber))
			break;
		SetConsoleColor(4);
		cout << "   Invalid phone number." << endl;
		Sleep(3000);
	}
	// Set address
	while (true)
	{
		SetConsoleColor(7);
		cout << "   Address: ";
		getline(cin, address);
		if (user.SetAddress(address))
			break;
		SetConsoleColor(4);
		cout << "   Invalid address. It must be must be greater than 2 or less than 150 characters."
			<< endl;
		Sleep(3000);
	}
	// Set user id
	while (true)
	{
		SetConsoleColor(7);
		cout << "   User ID: ";
		string tmp; // Temporary string for storing user id
		getline(cin, tmp);
		try
		{
			userId = std::stoi(tmp); // Try to convert string to int
		}
		catch (const std::exception&)
		{
			userId = NULL; // Set to NULL if failed
		}

		if (user.SetUserId(userId))
			break;
		SetConsoleColor(4);
		cout << "   Invalid User ID. It must be a number between 1 to 50,000." << endl;
		Sleep(3000);
	}
	// Set user password
	while (true)
	{
		SetConsoleColor(7);
		cout << "   Password: ";
		string tmp; // Temporary string for storing password
		getline(cin, tmp);
		try
		{
			userPassword = std::stoi(tmp); // Try to convert string to int
		}
		catch (const std::exception&)
		{
			userPassword = NULL; // Set to NULL if failed
		}
		if (user.SetUserPassword(userPassword))
			break;
		SetConsoleColor(4);
		cout << "   Invalid password. It must be 7 digit number." << endl;
		Sleep(3000);
	}

	// Ask user if they want to deposit initial amount
	ShowAppInfo();
	int balance{ 0 };
	cout << "\n   Would you like to deposit funds now?\n";
	while (true)
	{
		cout << "   Enter amount: ";
		SetConsoleColor(7);
		string tmp;
		getline(cin, tmp);
		try
		{
			balance = std::stoi(tmp); // Try to convert string to int
		}
		catch (const std::exception&)
		{
			SetConsoleColor(4);
			cout << "   Invalid value." << endl;
			Sleep(3000);
			continue;
		}
		if (user.AddBalance(balance))
			break;
	}

#pragma endregion

#pragma region Confirm and Create Account

	// At this stage, all details are valid. Now display all user info for confirmation.
	ShowAppInfo();
	SetConsoleTitleW(L"Bean Bank | Account Confirmation");
	cout << "\n   - Account Confirmation -\n" << "\n"
		<< "   Name: " << firstName << " " << lastName << "\n"
		<< "   Age: " << age << "\n"
		<< "   Gender: ";
	if (gender == "1")
		cout << "Male";
	if (gender == "2")
		cout << "Female";
	if (gender == "3")
		cout << "Other";
	cout << "\n   Phone Number: " << phoneNumber << "\n"
		<< "   Address: " << address << "\n"
		<< "   User ID: " << userId << endl;
	user.SetAccountNumber(User::GenerateAccountNumber());
	cout << "   Account Number: " << user.GetAccountNumber() << endl;
	cout << "   Password: " << userPassword << endl;
	SetConsoleColor(6);
	cout << "\n   Enter 1 to Create your Account. Enter 0 Otherwise." << endl;
	cout << "   CONSENT: ";
	string consent;
	getline(cin, consent);
	try
	{
		if (int ans = std::stoi(consent); ans != 1)
			return;
	}
	catch (const std::exception&) { return; }

	// TODO: IMPLEMENT ACTUAL ACCOUNT CREATION PROCEDURE HERE

	// Show success message
	ShowAppInfo();
	cout << endl;
	SetConsoleTitleW(L"Bean Bank | Success");
	cout << "   Account created successfully!\n\n"
		<< "   Name: " << firstName << " " << lastName << "\n"
		<< "   Age: " << age << "\n"
		<< "   Gender: ";
	if (gender == "1")
		cout << "Male";
	if (gender == "2")
		cout << "Female";
	if (gender == "3")
		cout << "Other";
	cout << "\n   Phone Number: " << phoneNumber << "\n"
		<< "   Address: " << address << "\n"
		<< "   User ID: " << userId << "\n"
		<< "   Account Number: " << user.GetAccountNumber() << "\n"
		<< "   Password: " << userPassword << "\n"
		<< "\n   Please note down your credentials.\n\n"
		<< "   Thank You!\n\n"
		<< "   Press any key to continue.";
	{
		PAUSE
	}

#pragma endregion
}

auto CheckBalanceWizard() -> void
{
	SetConsoleTitleA("Bean Bank | Check Balance");
	ShowAppInfo();
	cout << "\n   - Check Your Balance -";
	while (true)
	{
		SetConsoleColor(7);
		cout << "\n\n   Please Enter Your Account Number: ";
		string tmp; // Temporary string for storing account number
		getline(cin, tmp);
		cout << "   Please Enter Your Password: ";
		string pass; // Temporary string for user pass
		getline(cin, pass);
		class InvalidPasswordException : public std::exception { };
		class InvalidAccountNumberException : public std::exception { };
		class UserNotExistException : public std::exception { };
		try
		{
			// Try to convert account number and password to string
			const unsigned long long accountNumber = std::stoull(tmp);
			const int userPassword = std::stoi(pass);

			if (!User::ValidateAccountNumber(accountNumber))
				throw InvalidAccountNumberException();
			if (!User::ValidateUserPassword(userPassword))
				throw InvalidPasswordException();

			// TODO: IMPLEMENT BALANCE CHECK 
		}
		catch (UserNotExistException&)
		{
			SetConsoleColor(4);
			cout << "   User Not Found." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (InvalidPasswordException&)
		{
			SetConsoleColor(4);
			cout << "   Invalid Password." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (const std::exception& e)
		{
			if (strcmp(e.what(), "invalid stoi argument") == 0)
			{
				SetConsoleColor(4);
				cout << "   Invalid Input." << endl;
				Sleep(3000);
				SetConsoleColor(7);
			}
			if (strcmp(e.what(), "stoi argument out of range") == 0)
			{
				SetConsoleColor(4);
				cout << "   Invalid Input." << endl;
				Sleep(3000);
				SetConsoleColor(7);
			}
		}
	}
}

auto DepositFundsWizard() -> void
{
	SetConsoleTitleA("Bean Bank | Deposit Funds");
	ShowAppInfo();
	cout << "\n   - Deposit Funds -";
	while (true)
	{
		SetConsoleColor(7);
		cout << "\n\n   Enter Your Account Number: ";
		string tmp; // Temporary string for storing account number
		getline(cin, tmp);
		cout << "   Enter Your Password: ";
		string pass; // Temporary string for user pass
		getline(cin, pass);
		cout << "   Enter The Amount: ";
		string amt; // Temporary string for amount
		getline(cin, amt);

		class InvalidPasswordException : public std::exception { };
		class InvalidAccountNumberException : public std::exception { };
		class UserNotExistException : public std::exception { };

		try
		{
			// try to convert to string
			const unsigned long long accountNumber = std::stoull(tmp);
			const int userPassword = std::stoi(pass);
			const int amount = std::stoi(amt);

			if (!User::ValidateAccountNumber(accountNumber))
				throw InvalidAccountNumberException();
			if (!User::ValidateUserPassword(userPassword))
				throw InvalidPasswordException();

			// TODO: IMPLEMENT ACTUAL FUNDS DEPOSIT TO DATA FILE 

			SetConsoleColor(2);
			cout << "\n   Authentication Successful."
				<< "\n   Funds Deposited Successfully." << endl;

			// TODO: ALSO SHOW THE BALANCE HERE

			SetConsoleColor(7);
			cout << "\n   Press enter to return to main menu.";
			{
				CONSUME_NEWLINE_CHARACTER
			}
			return;

			// TODO: IMPLEMENT EXCEPTION CHECK
			// throw UserNotExistException();
		}

		catch (UserNotExistException&)
		{
			SetConsoleColor(4);
			cout << "   User Not Found." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (InvalidAccountNumberException&)
		{
			SetConsoleColor(4);
			cout << "   Invalid Account Number." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (InvalidPasswordException&)
		{
			SetConsoleColor(4);
			cout << "   Invalid Password." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (const std::exception& e)
		{
			if (strcmp(e.what(), "invalid stoi argument") == 0)
			{
				SetConsoleColor(4);
				cout << "   Invalid Input." << endl;
				Sleep(3000);
				SetConsoleColor(7);
			}
			if (strcmp(e.what(), "stoi argument out of range") == 0)
			{
				SetConsoleColor(4);
				cout << "   Invalid Input." << endl;
				Sleep(3000);
				SetConsoleColor(7);
			}
		}
	}
}

auto WithdrawFundsWizard() -> void
{
	SetConsoleTitleA("Bean Bank | Withdraw Funds");
	ShowAppInfo();
	cout << "\n   - Withdraw Funds -";
	while (true)
	{
		SetConsoleColor(7);
		cout << "\n\n   Enter Your Account Number: ";
		string tmp; // Temporary string for storing account number
		getline(cin, tmp);
		cout << "   Enter Your Password: ";
		string pass; // Temporary string for user pass
		getline(cin, pass);
		cout << "   Enter The Amount: ";
		string amt; // Temporary string for amount
		getline(cin, amt);

		class InvalidPasswordException : public std::exception { };
		class InvalidAccountNumberException : public std::exception { };
		class InsufficientBalanceException : public std::exception { };
		class UserNotExistException : public std::exception { };

		try
		{
			// try to convert to string
			const unsigned long long accountNumber = std::stoull(tmp);
			const int userPassword = std::stoi(pass);
			const int amount = std::stoi(amt);

			if (!User::ValidateAccountNumber(accountNumber))
				throw InvalidAccountNumberException();
			if (!User::ValidateUserPassword(userPassword))
				throw InvalidPasswordException();

			// TODO: IMPLEMENT ACTUAL FUNDS WITHDRAWAL TO DATA FILE 

			SetConsoleColor(2);
			cout << "\n   Authentication Successful."
				<< "\n   Funds Withdrawal Successful." << endl;
			// TODO: DON'T FORGET TO SHOW REMAINING FUNDS HERE
			//  << "\n   Updated Balance: " << userItr->GetBalance() << " INR"
			SetConsoleColor(7);
			cout << "\n   Press enter to return to main menu.";
			{
				CONSUME_NEWLINE_CHARACTER
			}
			return;

			// TODO check if user exists and handle exception
			//	throw UserNotExistException();
		}

		catch (UserNotExistException&)
		{
			SetConsoleColor(4);
			cout << "   User Not Found." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (InvalidAccountNumberException&)
		{
			SetConsoleColor(4);
			cout << "   Invalid Account Number." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (InvalidPasswordException&)
		{
			SetConsoleColor(4);
			cout << "   Invalid Password." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (InsufficientBalanceException&)
		{
			SetConsoleColor(4);
			cout << "\n   Transaction Failed."
				<< "\n   Insufficient Balance." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (const std::exception& e)
		{
			if (strcmp(e.what(), "invalid stoi argument") == 0)
			{
				SetConsoleColor(4);
				cout << "   Invalid Input." << endl;
				Sleep(3000);
				SetConsoleColor(7);
			}
			if (strcmp(e.what(), "stoi argument out of range") == 0)
			{
				SetConsoleColor(4);
				cout << "   Invalid Input." << endl;
				Sleep(3000);
				SetConsoleColor(7);
			}
		}
	}
}

auto CloseAccountWizard() -> void
{
	SetConsoleTitleA("Bean Bank |  Close Account");
	ShowAppInfo();
	cout << "\n   - Close Account -";
	while (true)
	{
		SetConsoleColor(7);
		cout << "\n\n   Enter Your Account Number: ";
		string tmp; // Temporary string for storing account number
		getline(cin, tmp);
		cout << "   Enter Your Password: ";
		string pass; // Temporary string for user pass
		getline(cin, pass);

		class InvalidPasswordException : public std::exception { };
		class InvalidAccountNumberException : public std::exception { };
		class UserNotExistException : public std::exception { };

		try
		{
			// Try to convert to string
			const unsigned long long accountNumber = std::stoull(tmp);
			const int userPassword = std::stoi(pass);

			if (!User::ValidateAccountNumber(accountNumber))
				throw InvalidAccountNumberException();
			if (!User::ValidateUserPassword(userPassword))
				throw InvalidPasswordException();

			// TODO: IMPLEMENT FUNDS ACCOUNT CLOSING  TO DATA FILE 

			Account::RemoveAccount();
			User::RemoveUser();
			Bank::RemoveUser();
			SetConsoleColor(2);
			cout << "\n   Authentication Successful."
				<< "\n   Account Closed Successfully." << endl;
			SetConsoleColor(7);
			cout << "\n   Press enter to return to main menu.";
			{
				CONSUME_NEWLINE_CHARACTER
			}
			return;

			// TODO: Check if user exists id exception occurs
			//	throw UserNotExistException();
		}

		catch (UserNotExistException&)
		{
			SetConsoleColor(4);
			cout << "   User Not Found." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (InvalidAccountNumberException&)
		{
			SetConsoleColor(4);
			cout << "   Invalid Account Number." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (InvalidPasswordException&)
		{
			SetConsoleColor(4);
			cout << "   Invalid Password." << endl;
			Sleep(3000);
			SetConsoleColor(7);
		}
		catch (const std::exception& e)
		{
			if (strcmp(e.what(), "invalid stoi argument") == 0)
			{
				SetConsoleColor(4);
				cout << "   Invalid Input." << endl;
				Sleep(3000);
				SetConsoleColor(7);
			}
		}
	}
}

auto ShowAllAccountsWizard() -> void
{
	ShowAppInfo();
	SetConsoleTitle(L"Bean Bank | All Accounts");
	cout << "\n   - All Accounts - \n" << endl;

	// TODO: IMPLEMENT SHOW ALL ACCOUNTS

	cout << "\n   " << Bank::GetTotalUserCount() << " In Total."
		<< "\n\n   Press enter to return to main menu." << endl;
	{
		PAUSE
	}
}
