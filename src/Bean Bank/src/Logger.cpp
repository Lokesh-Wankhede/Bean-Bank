// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Logger for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

// ReSharper disable CppClangTidyBugproneNarrowingConversions

#include "Logger.h"
#include <fstream>
#include <iostream>
#include <Lmcons.h> // for UNLEN
#include <ShlObj.h> // for getting the path of the desktop
#include <Windows.h>
#include "Bean Bank.h"

std::shared_ptr<MemorySink> memorySink = std::make_shared<MemorySink>();
const std::shared_ptr<spdlog::logger> LOGGER = std::make_shared<spdlog::logger>("Logger",
	memorySink);

MemorySink::MemorySink()
	: MBuffer(std::make_shared<std::stringstream>()) {}

auto MemorySink::LogBuffer() const -> std::shared_ptr<std::stringstream> { return MBuffer; }

auto MemorySink::sink_it_(const spdlog::details::log_msg& msg) -> void
{
	spdlog::memory_buf_t formatted;
	formatter_->format(msg, formatted);
	MBuffer->write(formatted.data(), formatted.size());
}

auto MemorySink::flush_() -> void {}

auto InitializeLogger() -> void
{
	// set the log pattern: [YYYY-MM-DD HH:MM:SS] [log level] message.
	LOGGER->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
	LOGGER->set_level(spdlog::level::trace);
	LOGGER->debug("[Logger] [InitializeLogger] Logger Initialized.");
}

auto ExportLog() -> bool
{
	// get the path of the desktop
	PWSTR path = nullptr;
	if (SHGetKnownFolderPath(FOLDERID_Desktop, 0, nullptr, &path) != S_OK)
	{
		std::cerr << "Failed to get desktop path" << std::endl;
		return false;
	}

	// get the version info of Bean Bank
	const auto [Major, Minor, Build] = GetVersionInfo();

	// convert the desktop path to wide string
	const std::wstring desktopPath(path);
	// let the path lead to salvation.. (no memory leaks)
	CoTaskMemFree(path);

	// Get the current date and time
	SYSTEMTIME time;
	GetLocalTime(&time);

	// Get the user name
	wchar_t userName[UNLEN + 1];
	DWORD userNameSize = UNLEN + 1;
	GetUserNameW(userName, &userNameSize);

	// Get the host name
	wchar_t hostName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD hostNameSize = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerNameW(hostName, &hostNameSize);

	// Build the log name with the date, time, user name, and host name
	const std::wstring logName = L"Bean_Bank_" + std::to_wstring(time.wYear) + L"-" +
		std::to_wstring(time.wMonth) + L"-" + std::to_wstring(time.wDay) + L"_" + std::to_wstring(time.wHour) +
		L"-" + std::to_wstring(time.wMinute) + L"-" + std::to_wstring(time.wSecond) +
		L"_" + std::wstring(userName) + L"_" + std::wstring(hostName) + L".log";

	const std::wstring logPath = desktopPath + L"\\" + logName;

	try
	{
		// create the logFile and dump the trace
		std::ofstream logFile(logPath);
		logFile << "- Bean Bank Log & Horror Report - \n"
			"- Version: " << Major << '.' << Minor << '.' << Build << " -\n\n"
			<< "This file contains the errors and logs that Bean Bank occurred during the runtime.\n"
			<< "\n\n-------------------- Start of BackTrace --------------------\n\n"
			<< memorySink->LogBuffer()->str() <<
			"\n\n-------------------- End of BackTrace --------------------\n\n" <<
			"End of report, Goodbye." << std::endl;
		logFile.close();
	}
	catch (const std::exception&) { return false; }

	return true;
}
