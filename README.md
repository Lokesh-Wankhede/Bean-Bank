# Bean Bank

![Logo](https://github.com/LogicalLokesh/Bean-Bank/blob/master/Resources/images/Bean%20Bank%20Github%20Template.png?raw=false)

## Welcome to Bean Bank - A Simple Banking Application Written in Modern C++

### Description

Welcome to the Bean Bank!
The bank that's here to help you save your beans and grow your wealth.
With our state-of-the-art banking system, written in the latest
and greatest version of C++, you can be sure that your beans are in safe hands.
We've got all the features you need, like account creation, depositing
and withdrawing funds, checking your balance and even closing your
account (just in case you need to escape from the bean-holding life).
And with our top-notch security features, you can be sure that your
beans will be safe from even the most determined bean thieves.
So why wait? Open an account with Bean Bank today and start saving your beans!

## Authors

[@LogicalLokesh](https://www.github.com/LogicalLokesh)

### Status -

![Windows Build](https://img.shields.io/github/actions/workflow/status/LogicalLokesh/Bean-Bank/msbuild.yml?label=Windows%20Build&logo=windows11&logoColor=blue)
![GitHub Repo Size](https://img.shields.io/github/repo-size/LogicalLokesh/Bean-Bank?label=Repository%20Size&logo=Github&style=plastic)
![Latest Release](https://img.shields.io/github/v/release/LogicalLokesh/Bean-Bank?color=blue&label=Latest%20Release&style=plastic)
![Last Commit](https://img.shields.io/github/last-commit/LogicalLokesh/Bean-Bank?color=darkcyan&label=Last%20Commit&style=plastic)
![License](https://img.shields.io/github/license/LogicalLokesh/Bean-Bank?label=License&style=plastic)

## Tech Stack

**Client:** Windows.h, WinAPI

**Server:** Local, Self Hosted

## Features

- Account Creation
- Account Deletion
- Deposit Funds
- Withdraw Funds
- Check Balance
- Robust User Input Validation
- Standard Password Protection
- Colored Output
- Full screen mode
- Standalone & Portable
- Fully Off-line

## Limitations

- Windows Only.

## Documentation

### **Notes -**

Whenever you start the application first time, Bean Bank will create two files - user_data.txt & account_data.txt in the current directory.
These are user data files, which are required for working of the application.

**Deleting these files will remove all data stored withing the app!**

App will report error if there it finds integrity violation of the data within the files. So please do not modify the files, they are only for examining purposes.

### **How To Use -**

You can select what you want to do using the choices given at the main menu.
Just enter number of the choices and a wizard will help you to the process your transaction.
You can create, close, and check accounts of all users.
You can also check your balance, add funds, or withdraw your funds from your account.
It offers standard password protection for your account.

### **Common Problems and Solutions -**

Application itself is very stable, but you may encounter some bugs or errors, feel free to report them.

- If you get "User data integrity violation" error, this means that the files containing the user data are damaged or tempered. It mostly happens when you edit the file manually.
- To fix this issue, either delete these files (user_data.txt and account_data.txt). Note that this will delete all user accounts and their data. Application will create them automatically upon next startup.
- User data files must be in the same directory where the Application executable is located. Otherwise Application will not be able to read the data.

## License

[GNU Affero General Public License v3.0](https://choosealicense.com/licenses/agpl-3.0/)

## Support

For support, email logicallokesh@outlok.in

You can also reach me by:

[Instagram](https://instagram.com/logicallokesh)

[Website](https://logicallokesh.net)
