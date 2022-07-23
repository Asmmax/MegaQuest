#pragma once
#include "TextString.hpp"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Game
{
	class ICommand;

	/// @serializable
	struct CommandRecord
	{
		using CommandPtr = std::shared_ptr<ICommand>;

		std::string name;
		CommandPtr command;
	};

	/// @serializable @shared commandManagers
	class CommandManager
	{
		using CommandPtr = std::shared_ptr<ICommand>;
	public:
		using Ptr = std::shared_ptr<CommandManager>;

		CommandManager(const QuestCore::TextString& error);

		/// @inject
		void RegisterCommands(const std::vector<CommandRecord>& commands);
		void Register(const std::string& text, const CommandPtr& command);
		void Run(const std::string& command, const std::vector<std::string>& args);

	private:
		std::map<std::string, CommandPtr> _commands;
		QuestCore::TextString _error;
	};
}
