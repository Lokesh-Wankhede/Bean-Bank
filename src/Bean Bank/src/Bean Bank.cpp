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
#include "BankingService.h"
#include "CoreException.h"
#include "DatabaseManager.h"
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
		// show home page
		OpenHomePage();

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
			if (OpenUserDashboard()) continue;
			return 0;
		case 2:
			OpenNewAccountWizard();
			break;
		case 3:
			OpenSupportPage();
			break;
		case 4:
			cout << "\n   Quit\n\n";
			// user has decided to exit the program
			return 0;
		case 9:
			DatabaseManager::GetInstance().InitializeDatabase();
			if (!DatabaseManager::GetInstance().ConstructDataTemplate())
				cout << "failed";
			break;

		case 555:
			if (!ExportLog())
				cout << "\n   Failed to export the log!\n\n";
			cout << "\n   Log successfully exported to your desktop.\n\n";
			break;

		default:
			// if user enters something other than a valid choice, they need their glasses
			cout << "\n   Invalid input, please enter a valid choice.\n\n";
		}

		// wait for two seconds
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
	LOGGER->error("Unplanned shutdown, exiting.");
	// export the log to the desktop
	ExportLog();
	cout << "\n\n   A log has been exported to your desktop.\n"
		"   Please send this log to:\n"
		"   Website: logicallokesh.net\\contact\n"
		"   E-mail:  support@logicallokesh.net\n"
		"   Your feedback is really appreciated.\n"
		"   Thank You.\n\n"
		"   Press enter to exit.";
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
		' ',
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

template <typename ValidationFn>
auto GetUserInput(const string& prompt, ValidationFn validateFn) -> string
{
	string userInput;
	while (true)
	{
		// prompt user for input
		cout << "\n   " << prompt << ": ";
		getline(cin, userInput);

		// check if user wants to exit
		if (userInput == "0")
			return "";

		// validate input
		if (validateFn(userInput))
			return userInput;
		cout << "\n   Invalid input.\n";
	}
}

auto GetUserInputNoValidation(const string& prompt) -> string
{
	string userInput;
	while (true)
	{
		// prompt user for input
		cout << "\n   " << prompt << ": ";
		getline(cin, userInput);

		// check if input is empty
		if (userInput.empty())
		{
			cout << "\n   Invalid input.\n";
			continue;
		}

		// check if user wants to exit
		if (userInput == "0")
			return "";

		return userInput;
	}
}


auto OpenSupportPage() -> void
{
	cout << "\n   Opening Support page in your browser!\n\n";
	ShellExecute(nullptr, L"open", L"https://logicallokesh.net",
		nullptr, nullptr, SW_SHOWNORMAL);
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

auto OpenHomePage() -> void
{
	SetConsoleTitleW(L"Bean Bank");
	ClearScreen();
	ShowAppInfo();
	cout << "\n   Welcome to the Bean Bank!\n"
		"\n   Home\n\n"
		"   1. User Login\n"
		"   2. Open New Account\n"
		"   3. Support\n"
		"   4. Quit\n\n"
		"   Enter your choice: ";
}

auto OpenUserDashboard() -> bool
{
	string userChoice;
	int choice;

	do
	{
		SetConsoleTitleW(L"Bean Bank");
		ClearScreen();
		ShowAppInfo();
		cout << "\n   User Dashboard\n\n"
			"   1. Check Balance\n"
			"   2. Deposit Funds\n"
			"   3. Withdrawal\n"
			"   4. Update Profile\n"
			"   5. Close Your Account\n"
			"   6. Support\n"
			"   7. Log Out\n"
			"   8. Quit\n\n"
			"   Enter your choice: ";

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

		switch (choice)
		{
		case 1:
			cout << "   Check Balance" << endl;
			break;
		case 2:
			cout << "   Deposit funds" << endl;
			break;
		case 3:
			cout << "   Withdraw" << endl;
			break;
		case 4:
			cout << "   Update Profile" << endl;
			break;
		case 5:
			cout << "   Close Your Account" << endl;
			break;
		case 6:
			OpenSupportPage();
			break;

		case 7: return true; // log out
		case 8: return false; // exit

		default:
			// if user enters something other than a valid choice, they need their glasses
			cout << "\n   Invalid input, please enter a valid choice.\n\n";
		}

		// wait for two seconds
		Sleep(2000);
	} while (true);
}

auto OpenNewAccountWizard() -> void
{
	User user;

	ShowAppInfo();
	SetConsoleTitleW(L"Bean Bank | Open New Account");
	cout << "\n   - Open New Account - \n\n\n"
		"   Enter 0 to cancel & return to home." << endl;

	// get first name
	const string firstName = GetUserInput("First name", User::ValidateName);
	if (firstName.empty())
		return;
	user.SetFirstName(firstName);

	// get middle name
	const string middleName = GetUserInput("Middle name", User::ValidateName);
	if (middleName.empty())
		return;
	user.SetMiddleName(middleName);

	// get last name
	const string lastName = GetUserInput("Last name", User::ValidateName);
	if (lastName.empty())
		return;
	user.SetLastName(lastName);

	// get age
	while (true)
	{
		const string ageStr = GetUserInputNoValidation("Age");
		if (ageStr.empty())
			return;
		try
		{
			const int age = stoi(ageStr);

			// check if user is minor
			if (age < 18)
			{
				cout << "\n   You must be 18 years old to open an account.\n"
					"   Press enter to continue...";
				{
					PAUSE
				}
				return;
			}

			if (User::ValidateAge(age))
			{
				user.SetAge(age);
				break;
			}

			cout << "\n   Invalid Input." << endl;
		}
		catch (exception&) { cout << "\n   Invalid Input." << endl; }
	}

	// get address
	const string address = GetUserInput("Address", User::ValidateAddress);
	if (address.empty())
		return;
	user.SetAddress(address);

	// get phone number
	const string phoneNumberStr = GetUserInput("Phone Number", User::ValidatePhoneNumberStr);
	if (phoneNumberStr.empty())
		return;
	const unsigned long long phoneNumber = stoll(phoneNumberStr);
	user.SetPhoneNumber(phoneNumber);

	// get gender
	while (true)
	{
		const string genderStr = GetUserInputNoValidation("Gender (1:Male, 2:Female, 3:Other)");
		if (genderStr.empty())
			return;
		try
		{
			const int genderParsedInt = stoi(genderStr);
			if (genderParsedInt == 1)
				if (user.SetGender(GenderT::Male))
					break;
			if (genderParsedInt == 2)
				if (user.SetGender(GenderT::Female))
					break;
			if (genderParsedInt == 3)
				if (user.SetGender(GenderT::Other))
					break;
			cout << "\n   Invalid Input." << endl;
		}
		catch (exception&) { cout << "\n   Invalid Input." << endl; }
	}

	// get userId
	const string userId = GetUserInput("User ID", User::ValidateUserId);
	if (userId.empty())
		return;
	user.SetUserId(userId);

	// get userPassword
	const string userPassword = GetUserInput("User Password", User::ValidateUserPassword);
	if (userPassword.empty())
		return;
	user.SetUserPassword(userPassword);

	// get mpin
	while (true)
	{
		const string mPinStr = GetUserInputNoValidation(
			"(You will use this MPIN for performing any type of transactions)\n   6 Digit MPIN");
		if (mPinStr.empty())
			return;
		try
		{
			if (const int mPin = stoi(mPinStr); User::ValidateMPin(mPin))
			{
				user.SetMPin(mPin);
				break;
			}

			cout << "\n   Invalid Input." << endl;
		}
		catch (exception&) { cout << "\n   Invalid Input." << endl; }
	}

	// perform checkup
	if (User::IsValid(user))
		cout << "\n   user is valid! LOL";
}
