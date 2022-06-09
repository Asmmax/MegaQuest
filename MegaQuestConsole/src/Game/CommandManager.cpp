#include "Game/CommandManager.hpp"
#include "Game/ICommand.hpp"
#include "IO/Logger.hpp"

using namespace Game;

CommandManager& CommandManager::Instance()
{
	static CommandManager commandManager;
	return commandManager;
}

void CommandManager::Register(const std::string& text, const ICommand::Ptr& command)
{
	_commands.emplace(text, command);
}

void CommandManager::Run(const std::string& command, const std::vector<std::string>& args)
{
	auto foundCommand = _commands.find(command);
	if (foundCommand == _commands.end()) {
		auto error = QuestCore::TextString::FromUtf8(u8"¬водить можно только цифру, Quit или Inventory!");
		IO::Logger::Instance().Log(error);
		return;
	}

	foundCommand->second->Run(args);
}