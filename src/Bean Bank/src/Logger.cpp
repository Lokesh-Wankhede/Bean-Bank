// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Logger for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

// ReSharper disable CppClangTidyBugproneNarrowingConversions

#include "Logger.h"
#include <fstream>
#include <iostream>
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
	// set the log pattern: [YYYY-MM-DD HH:MM:SS.microseconds] [log level] message.
	LOGGER->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
	LOGGER->set_level(spdlog::level::trace);
	LOGGER->debug("Logger Initialized.");
}

auto ExportLog() -> bool
{
	// get the path of the desktop
	PWSTR path = nullptr;
	if (const HRESULT result = SHGetKnownFolderPath(FOLDERID_Desktop, 0, nullptr, &path); result !=
		S_OK)
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

	// name of the log in the format - [name] [version] .log
	const std::wstring logName = L"Bean Bank v" + std::to_wstring(Major) + L'.' +
		std::to_wstring(Minor) + L'.' + std::to_wstring(Build) + L".log";
	const std::wstring logPath = desktopPath + L"\\" + logName;

	try
	{
		// create the logFile and dump the trace
		std::ofstream logFile(logPath);
		logFile << "- Bean Bank Log & Error Report - \n"
			"- Version: " << Major << '.' << Minor << '.' << Build << " -\n\n"
			<< "This file contains the errors and logs that Bean Bank occurred during the runtime.\n"
			<< "\n\n-------------------- Start of BackTrace --------------------\n\n"
			<< memorySink->LogBuffer()->str() <<
			"\n\n-------------------- End of BackTrace --------------------\n\n" <<
			"Goodbye." << std::endl;
		logFile.close();
	}
	catch (const std::exception&)
	{
		return false;
	}

	return true;
}
