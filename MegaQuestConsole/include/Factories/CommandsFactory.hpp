#pragma once
#include "json.hpp"
#include "TextString.hpp"
#include <memory>

class DialogFactory;

namespace Game
{
	class ICommand;
	class CommandManager;
}

class CommandsFactory
{
	using CommandPtr = std::shared_ptr<Game::ICommand>;
	using CommandManagerPtr = std::shared_ptr<Game::CommandManager>;
	using DialogFactoryPtr = std::shared_ptr<DialogFactory>;

public:
	CommandsFactory(const std::string& filename, const DialogFactoryPtr& dialogFactory);
	CommandManagerPtr GetCommandManager();

private:
	void Read();
	std::map<std::string, CommandPtr> ReadCommands(const nlohmann::json& commandsNode, const CommandManagerPtr& commandManager);
	CommandPtr ReadCommand(const nlohmann::json& commandNode, const CommandManagerPtr& commandManager);

private:
	bool _isRed;
	std::string _filename;
	DialogFactoryPtr _dialogFactory;
	CommandManagerPtr _commandManager;
};
