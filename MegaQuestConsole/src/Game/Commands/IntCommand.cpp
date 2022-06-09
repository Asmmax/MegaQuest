#include "Game/Commands/IntCommand.hpp"
#include "IO/Logger.hpp"
#include <assert.h>
#include <iostream>

using namespace Game;

IntCommand::IntCommand(const QuestCore::TextString& error):
	_error(error)
{
}

void IntCommand::Run(const std::vector<std::string>& args)
{
	assert(!args.empty());

	try
	{
		int intArg = 0;
		if (!args.empty()) {
			intArg = std::stoi(args.front());
		}

		Run(intArg);
	}
	catch (const std::invalid_argument& /*ex*/) {
		Error();
	}
}

void IntCommand::Error()
{
	IO::Logger::Instance().Log(_error);
}
