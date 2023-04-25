// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: The Logger for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/base_sink.h"

// a custom memory sink for spdlog.
class MemorySink final : public spdlog::sinks::base_sink<std::mutex>
{
public:
	MemorySink();
	auto LogBuffer() const->std::shared_ptr<std::stringstream>;

protected:
	auto sink_it_(const spdlog::details::log_msg& msg) -> void override;
	auto flush_() -> void override;

private:
	std::shared_ptr<std::stringstream> MBuffer;
};


/**
 * \brief This just sets the format, level and starting of a log. and does not actually initialize the logger.
 */
auto InitializeLogger() -> void;

/**
 * \brief Exports the current back trace of the log to the desktop.
 * \return true if successful, false otherwise.
 */
auto ExportLog() -> bool;

extern std::shared_ptr<MemorySink> memorySink;
extern const std::shared_ptr<spdlog::logger> LOGGER;
