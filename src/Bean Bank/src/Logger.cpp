// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Logger for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

// ReSharper disable CppClangTidyBugproneNarrowingConversions

#include "Logger.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <ShlObj.h> // for getting the path of the desktop
#include <sstream>
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
	// set the log pattern: [YYYY-MM-DD HH:MM:SS.microseconds] [log level] message.
	LOGGER->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
	LOGGER->set_level(spdlog::level::trace);
	LOGGER->info("Logger Initialized.");
}

auto ExportLog() -> bool
{
	SECURITY_ATTRIBUTES saAttr{};
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = nullptr;

	HANDLE hChildStdOutRd = nullptr;
	HANDLE hChildStdOutWr = nullptr;

	if (!CreatePipe(&hChildStdOutRd, &hChildStdOutWr, &saAttr, 0))
	{
		std::cerr << "Error creating pipe" << std::endl;
		return false;
	}

	// Ensure the read handle to the pipe for STDOUT is not inherited.
	if (!SetHandleInformation(hChildStdOutRd, HANDLE_FLAG_INHERIT, 0))
	{
		std::cerr << "Error setting handle information" << std::endl;
		return false;
	}

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdOutput = hChildStdOutWr;
	si.hStdError = hChildStdOutWr;

	if (!CreateProcessA(
		R"(C:\Windows\System32\systeminfo.exe)", // command line
		nullptr, // command line arguments
		nullptr, // process handle not inheritable
		nullptr, // thread handle not inheritable
		TRUE, // handles are inherited
		0, // creation flags
		nullptr, // use parent's environment block
		nullptr, // use parent's starting directory
		&si, // pointer to STARTUPINFO structure
		&pi // pointer to PROCESS_INFORMATION structure
	))
	{
		std::cerr << "Error creating process" << std::endl;
		return false;
	}

	CloseHandle(hChildStdOutWr);

	constexpr int bufferSize = 8096;
	char buffer[bufferSize]{};
	DWORD bytesRead;
	std::stringstream systemInfo;

	while (ReadFile(hChildStdOutRd, buffer, bufferSize - 1, &bytesRead, nullptr) != 0 && bytesRead
		!= 0)
	{
		buffer[bytesRead] = '\0';
		systemInfo << buffer;
	}

	// cleanup
	CloseHandle(hChildStdOutRd);

	// get the path of the desktop
	PWSTR path = nullptr;
	if (HRESULT result = SHGetKnownFolderPath(FOLDERID_Desktop, 0, nullptr, &path); result != S_OK)
	{
		// TODO: Throw an exception here instead of printing error
		std::cerr << "Failed to get desktop path" << std::endl;
		return false;
	}

	// get the version info of Bean Bank
	const auto [Major, Minor, Build] = GetVersionInfo();

	// convert the desktop path to wide string
	std::wstring desktopPath(path);
	// let the path lead to salvation.. (no memory leaks)
	CoTaskMemFree(path);

	// name of the log in the format - [name] [version] .log
	std::wstring logName = L"Bean Bank v" + std::to_wstring(Major) + L'.' +
		std::to_wstring(Minor) + L'.' + std::to_wstring(Build) + L".log";
	std::wstring logPath = desktopPath + L"\\" + logName;
	std::wcout << "Log path: " << logPath << std::endl;

	// TODO: WHAT IF THE FILE HANDLING THROWS AN ERROR?
	// TODO: HANDLE THE EXCEPTIONS!

	// create the logFile
	std::ofstream logFile(logPath);
	logFile << "- Bean Bank Log & Error Report - \n"
		"- Version: " << Major << '.' << Minor << '.' << Build << " -\n\n" <<
		"This file contains the errors and logs that Bean Bank occurred during the runtime.\n\n"
		"Client System Info: \n" <<
		systemInfo.str() << std::endl;
	logFile << "\n\n-------------------- Start of BackTrace --------------------\n\n"
		<< memorySink->LogBuffer()->str() <<
		"\n\n-------------------- End of BackTrace --------------------\n\n" <<
		"Goodbye." << std::endl;
	logFile.close();
	return true;
}
