#pragma once
#include "TextString.hpp"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Game
{
	class ICommand;

	struct CommandRecord
	{
		std::string name;
		ICommand* command;
	};

	class CommandManager
	{
	public:
		CommandManager(const QuestCore::TextString& error);

		void RegisterCommands(const std::vector<CommandRecord>& commands);
		void Register(const std::string& text, ICommand* command);
		void Run(const std::string& command, const std::vector<std::string>& args);

	private:
		std::map<std::string, ICommand*> _commands;
		QuestCore::TextString _error;
	};
}
