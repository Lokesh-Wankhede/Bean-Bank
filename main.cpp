/**
 * Copyright: LogicalLokesh. All rights reserved.
 *
 * Note:  Bean Bank requires C++ standard 20 or above,
 *        and designed to work on Windows operating system.
 *
 * Author: LogicalLokesh (github.com/LogicalLokesh)
 * Date:   January 2023
**/

#include <Windows.h>
#pragma comment(lib, "version.lib")           // for version info in ShowAppInfo();
#include <iostream>
#include <string>
#include "User.h"
#include "Bank.h"
#include "Account.h"
#include "main.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;

int main()
{
	// Load the user_data, exit upon failure.
	if (!Bank::LoadUserDataFile())
		ExitWithMessage("Failed to load the user_data.");
	// Load the account_data, exit upon failure.
	if (!Bank::LoadUserAccountFile())
		ExitWithMessage("Failed to load the account_data.");
	// Sync and perform data binding.
	if (!Bank::BindUserData())
		ExitWithMessage("User data integrity violation.");

	string userChoice;
	do
	{
		ShowMenu();
		getline(cin, userChoice);

		// check if choice is empty, or accidentally clicked enter.
		if (!userChoice.length())
		{
			SetConsoleColor(6);
			cout << "\n   Please enter a valid choice.";
			userChoice.clear();
			Sleep(2000);
			continue;
		}
		if (userChoice == "1")
		{
			userChoice.clear();
			CheckBalanceWizard();
			continue;
		}
		if (userChoice == "2")
		{
			userChoice.clear();
			DepositFundsWizard();
			continue;
		}
		if (userChoice == "3")
		{
			userChoice.clear();
			WithdrawFundsWizard();
			continue;
		}
		if (userChoice == "4")
		{
			NewAccountWizard();
			userChoice.clear();
			continue;
		}
		if (userChoice == "5")
		{
			userChoice.clear();
			CloseAccountWizard();
			continue;
		}
		if (userChoice == "6")
		{
			userChoice.clear();
			ShowAllAccountsWizard();
			continue;
		}
		if (userChoice == "7")
		{
			userChoice.clear();
			ShowAppInfo();
			cout << "\n   Opening Support page in your browser!" << endl;
			Sleep(2000);
			// Use the ShellExecute function to open the URL
			ShellExecute(nullptr, L"open", L"https://logicallokesh.net/bean-bank/",
				nullptr, nullptr, SW_SHOWNORMAL);
			Sleep(2000);
			continue;
		}
		if (userChoice == "8")
			return 0;

		// User has entered invalid choice.
		SetConsoleColor(6);
		cout << "   Invalid Input, please enter your choice: (1, 2, 3, 4, 5, 6, 7, 8)";
		userChoice.clear();
		Sleep(2000);
	} while (true);
}

/**
 * \brief Changes the color of the console.
 *
 * \param colorCode (1 Blue) (2 Green) (3 Teal) (4 Red) (5 Purple) (6 Yellow) (7 White) (8 Grey)
 */
void SetConsoleColor(const uint8_t colorCode)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

/**
 * \brief Exit the program with custom message screen.
 *
 * \param message string to be displayed
 */
[[noreturn]] void ExitWithMessage(const string& message)
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

/**
 * \brief Clears the console screen.
 */
void ClearScreen()
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

/**
 * \brief Clears the console and shows application information and version info.
 */
void ShowAppInfo()
{
	ClearScreen();
	SetConsoleColor(3);
	cout << "\n   ------------ Bean Bank ------------";
	SetConsoleColor(2);
	wchar_t path[MAX_PATH];
	GetModuleFileName(nullptr, path, MAX_PATH);
	DWORD handle = 0;
	if (const DWORD size = GetFileVersionInfoSize(path, &handle))
	{
		const auto buffer = new char[size];
		if (GetFileVersionInfo(path, handle, size, buffer))
		{
			VS_FIXEDFILEINFO* fileInfo;
			UINT len;
			if (VerQueryValue(buffer, L"\\", reinterpret_cast<LPVOID*>(&fileInfo), &len))
			{
				const int major = HIWORD(fileInfo->dwProductVersionMS);
				const int minor = LOWORD(fileInfo->dwProductVersionMS);
				const int build = HIWORD(fileInfo->dwProductVersionLS);
				cout << "\n             Version: " << major << "." << minor << "." << build;
			}
		}
		delete[] buffer;
	}
	SetConsoleColor(3);
	cout << "\n     Crafted with ";
	SetConsoleColor(4);
	cout << static_cast<char>(3);
	SetConsoleColor(3);
	cout << " by LogicalLokesh" << endl;
	cout << "   -----------------------------------\n";
	SetConsoleColor(7);
}

/**
 * \brief Clears the console and shows the main menu.
 */
void ShowMenu()
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

/**
 * \brief Creates a new user account.
 */
void NewAccountWizard()
{
	User user;
	string firstName, lastName, address;
	int age = 0, userId = 0, userPassword = 0;
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
			user.SetGender(Male);
		if (gender == "2")
			user.SetGender(Female);
		if (gender == "3")
			user.SetGender(Other);
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
		cout << "   Invalid address. It must be must be greater than 2 or less than 150 characters." << endl;
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
	int balance = 0;
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
	catch (const std::exception&)
	{
		return;
	}

	vUsers.push_back(user);
	Bank::WriteUserDataFile(user);
	// Create an account with null values first. because the order
	// of the data may change future.
	AccountDetailsT account{ NULL,NULL,NULL,NULL };
	account.AccountNumber = user.GetAccountNumber();
	account.UserId = userId;
	account.UserPassword = userPassword;
	account.Balance = balance;
	Bank::WriteAccountDataFile(account);

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

/**
 * \brief Check user balance wizard.
 */
void CheckBalanceWizard()
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
		class InvalidPasswordException : public std::exception
		{
		};
		class InvalidAccountNumberException : public std::exception
		{
		};
		class UserNotExistException : public std::exception
		{
		};
		try
		{
			// Try to convert account number and password to string
			const unsigned long long accountNumber = std::stoi(tmp);
			const int userPassword = std::stoi(pass);

			if (!User::ValidateAccountNumber(accountNumber))
				throw InvalidAccountNumberException();
			if (!User::ValidateUserPassword(userPassword))
				throw InvalidPasswordException();

			auto userItr = vUsers.begin();

			// Try to iterate over vUsers with given credentials to add funds.
			for (userItr = vUsers.begin(); userItr != vUsers.end(); ++userItr)
			{
				if (userItr->GetAccountNumber() == accountNumber)
				{
					if (userItr->GetUserPassword() != userPassword)
						throw InvalidPasswordException();

					SetConsoleColor(2);
					cout << "\n   Authentication Successful."
						<< "\n\n   Your Balance is: ";
					cout << userItr->GetBalance() << " INR" << endl;
					SetConsoleColor(7);
					cout << "\n   Press enter to return to main menu.";
					{
						CONSUME_NEWLINE_CHARACTER
					}
					return;
				}
			}

			// Check if user exists in vUsers.
			if (userItr == vUsers.end())
				throw UserNotExistException();
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

/**
 * \brief Wizard for depositing funds.
 */
void DepositFundsWizard()
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

		class InvalidPasswordException : public std::exception
		{
		};
		class InvalidAccountNumberException : public std::exception
		{
		};
		class UserNotExistException : public std::exception
		{
		};

		try
		{
			// try to convert to string
			const unsigned long long accountNumber = std::stoi(tmp);
			const int userPassword = std::stoi(pass);
			const int amount = std::stoi(amt);

			if (!User::ValidateAccountNumber(accountNumber))
				throw InvalidAccountNumberException();
			if (!User::ValidateUserPassword(userPassword))
				throw InvalidPasswordException();

			auto userItr = vUsers.begin();

			// Try to iterate over vUsers with given credentials to add funds.
			for (userItr = vUsers.begin(); userItr != vUsers.end(); ++userItr)
			{
				if (userItr->GetAccountNumber() == accountNumber)
				{
					if (userItr->GetUserPassword() != userPassword)
						throw InvalidPasswordException();
					userItr->AddBalance(amount);
					if (!Bank::SyncUserAccountData())
						throw;
					if (!Bank::WriteAccountDataFile())
						throw;

					SetConsoleColor(2);
					cout << "\n   Authentication Successful."
						<< "\n   Funds Deposited Successfully." << endl;
					cout << "\n   Updated Balance: " << userItr->GetBalance() << " INR" << endl;
					SetConsoleColor(7);
					cout << "\n   Press enter to return to main menu.";
					{
						CONSUME_NEWLINE_CHARACTER
					}
					return;
				}
			}

			// Check if user exists in vUsers.
			if (userItr == vUsers.end())
				throw UserNotExistException();
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

/**
 * \brief Wizard for withdrawing funds.
 */
void WithdrawFundsWizard()
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

		class InvalidPasswordException : public std::exception
		{
		};
		class InvalidAccountNumberException : public std::exception
		{
		};
		class InsufficientBalanceException : public std::exception
		{
		};
		class UserNotExistException : public std::exception
		{
		};

		try
		{
			// try to convert to string
			const unsigned long long accountNumber = std::stoi(tmp);
			const int userPassword = std::stoi(pass);
			const int amount = std::stoi(amt);

			if (!User::ValidateAccountNumber(accountNumber))
				throw InvalidAccountNumberException();
			if (!User::ValidateUserPassword(userPassword))
				throw InvalidPasswordException();

			auto userItr = vUsers.begin();

			for (userItr = vUsers.begin(); userItr != vUsers.end(); ++userItr)
			{
				if (userItr->GetAccountNumber() == accountNumber)
				{
					if (userItr->GetUserPassword() != userPassword)
						throw InvalidPasswordException();
					if (!userItr->WithdrawBalance(amount))
						throw InsufficientBalanceException();
					if (!Bank::SyncUserAccountData())
						throw;
					if (!Bank::WriteAccountDataFile())
						throw;

					SetConsoleColor(2);
					cout << "\n   Authentication Successful."
						<< "\n   Funds Withdrawal Successful." << endl;
					cout << "\n   Updated Balance: " << userItr->GetBalance() << " INR" << endl;
					SetConsoleColor(7);
					cout << "\n   Press enter to return to main menu.";
					{
						CONSUME_NEWLINE_CHARACTER
					}
					return;
				}
			}

			// check if user exists in vUsers.
			if (userItr == vUsers.end())
				throw UserNotExistException();
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

/**
 * \brief Wizard for closing an account.
 */
void CloseAccountWizard()
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

		class InvalidPasswordException : public std::exception
		{
		};
		class InvalidAccountNumberException : public std::exception
		{
		};
		class UserNotExistException : public std::exception
		{
		};

		try
		{
			// Try to convert to string
			const unsigned long long accountNumber = std::stoi(tmp);
			const int userPassword = std::stoi(pass);

			if (!User::ValidateAccountNumber(accountNumber))
				throw InvalidAccountNumberException();
			if (!User::ValidateUserPassword(userPassword))
				throw InvalidPasswordException();

			auto userItr = vUsers.begin();

			for (userItr = vUsers.begin(); userItr != vUsers.end(); ++userItr)
			{
				if (userItr->GetAccountNumber() == accountNumber)
				{
					if (userItr->GetUserPassword() != userPassword)
						throw InvalidPasswordException();

					// Iterate over vUsers vector to find the user
					userItr = std::ranges::find_if(vUsers, [&](const User& user)
						{
							return user.GetAccountNumber() == accountNumber;
						});
					if (userItr != vUsers.end())
					{
						// Calculate the index of the user.
						const long long i = std::distance(vUsers.begin(), userItr);
						vUsers.erase(vUsers.begin() + static_cast<int>(i));

						// Iterate over vAccountDetails vector to find the user.
						if (auto accountItr = std::ranges::find_if(vAccountDetails,
							[&](const AccountDetailsT& account)
							{
								return account.AccountNumber == accountNumber;
							}); accountItr != vAccountDetails.end())
						{
							// Erase the user from vAccountDetails vector.
							const long long k = std::distance(vAccountDetails.begin(), accountItr);
							vAccountDetails.erase(vAccountDetails.begin() + static_cast<int>(k));
						}
					}

					if (!Bank::SyncUserAccountData())
						throw;
					if (!Bank::WriteAccountDataFile())
						throw;
					if (!Bank::WriteUserDataFile())
						throw;
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
				}
			}

			// Check if user exists in vUsers.
			if (userItr == vUsers.end())
				throw UserNotExistException();
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

/**
 * \brief Wizard for displaying basic info of all users.
 */
void ShowAllAccountsWizard()
{
	ShowAppInfo();
	SetConsoleTitle(L"Bean Bank | All Accounts");
	cout << "\n   - All Accounts - \n" << endl;

	for (const auto& user : vUsers)
	{
		cout << "   Name: " << user.GetFirstName() << " " << user.GetLastName()
			<< " \n   Age: " << user.GetAge() << "   User ID: " << user.GetUserId()
			<< "\n   Phone Number: " << user.GetPhoneNumber()
			<< "\n   Address: " << user.GetAddress() << "\n\n";
	}
	cout << "\n   " << Bank::GetTotalUserCount() << " In Total."
		<< "\n\n   Press enter to return to main menu." << endl;
	{
		PAUSE
	}
}
