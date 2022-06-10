#pragma once
#include "TextString.hpp"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Game
{
	class ICommand;

	class CommandManager
	{
		using CommandPtr = std::shared_ptr<ICommand>;
	public:
		using Ptr = std::shared_ptr<CommandManager>;

		CommandManager(const QuestCore::TextString& error);

		void Register(const std::string& text, const CommandPtr& command);
		void Run(const std::string& command, const std::vector<std::string>& args);

	private:
		std::map<std::string, CommandPtr> _commands;
		QuestCore::TextString _error;
	};
}
