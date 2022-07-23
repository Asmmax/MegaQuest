#include "Game/CommandManager.hpp"
#include "Game/ICommand.hpp"
#include "IO/Logger.hpp"

using namespace Game;

CommandManager::CommandManager(const QuestCore::TextString& error):
	_error(error)
{
}

void CommandManager::RegisterCommands(const std::vector<CommandRecord>& commands)
{
	for (auto& commandRecord : commands)
	{
		Register(commandRecord.name, commandRecord.command);
	}
}

void CommandManager::Register(const std::string& text, const ICommand::Ptr& command)
{
	_commands.emplace(text, command);
}

void CommandManager::Run(const std::string& command, const std::vector<std::string>& args)
{
	auto foundCommand = _commands.find(command);
	if (foundCommand == _commands.end()) {
		IO::Logger::Instance().Log(_error);
		return;
	}

	foundCommand->second->Run(args);
}
