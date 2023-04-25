// Copyright (c) LogicalLokesh, All rights reserved.
//
// Description: Exceptions for Bean Bank.
//
// Author:      @LogicalLokesh - https://github.com/LogicalLokesh

#pragma once

#include "Logger.h"

#include <exception>
#include <string>

using std::string;
using std::exception;


/**
 * \brief Mother of all exceptions.
 * Use this class as the base for all of our the custom exceptions.
 */
class CoreException : public exception
{
public:
	explicit CoreException(string message, string name)
		: Message(std::move(message))
	{
		LOGGER->critical("[CoreException] Exception thrown: {}. Reason: {}", name, Message);
	}

	[[nodiscard]] auto what() const noexcept -> const char* override { return Message.c_str(); }

private:
	string Message;
};

class DatabaseInitializationException final : public CoreException
{
public:
	explicit DatabaseInitializationException(string message)
		: CoreException(std::move(message), "DatabaseInitializationException") {}
};

class UserNotFoundException final : public CoreException
{
public:
	explicit UserNotFoundException(string message)
		: CoreException(std::move(message), "UserNotFoundException") {}
};

class UserPasswordNotFoundException final : public CoreException
{
public:
	explicit UserPasswordNotFoundException(string message)
		: CoreException(std::move(message), "UserPasswordNotFoundException") {}
};
