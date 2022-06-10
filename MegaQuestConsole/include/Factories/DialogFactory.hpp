#pragma once
#include "json.hpp"
#include "TextString.hpp"
#include <vector>
#include <memory>

class IRootFactory;

namespace Game 
{
	class IOutput;
	class IDialog;
	class ICommand;
	class IButtonList;
	class CommandManager;
}

class DialogFactory
{
	using OutputPtr = std::shared_ptr<Game::IOutput>;
	using DialogPtr = std::shared_ptr<Game::IDialog>;
	using CommandPtr = std::shared_ptr<Game::ICommand>;
	using ButtonListPtr = std::shared_ptr<Game::IButtonList>;
	using RootFactoryPtr = std::shared_ptr<IRootFactory>;
	using CommandManagerPtr = std::shared_ptr<Game::CommandManager>;

public:
	DialogFactory(const std::string& filename, const OutputPtr& output, const RootFactoryPtr& rootFactory);
	DialogPtr GetDialog();
	CommandManagerPtr GetCommandManager();

private:
	void Read();
	void CreateDialogs(const nlohmann::json& dialogsNode);
	DialogPtr CreateDialog(const nlohmann::json& dialogNode);
	void ReadDialogs(const nlohmann::json& dialogsNode);
	void InitDialog(const DialogPtr& dialog, const nlohmann::json& dialogNode);
	void ReadCommandManager(const nlohmann::json& managerNode);
	std::map<std::string, CommandPtr> ReadCommands(const nlohmann::json& commandsNode, const CommandManagerPtr& commandManager);
	CommandPtr ReadCommand(const nlohmann::json& commandNode, const CommandManagerPtr& commandManager);
	void ReadRootDialog(const nlohmann::json& rootNode);

	std::vector<std::pair<std::string, ButtonListPtr>> ReadButtonLists(const nlohmann::json& buttonsNode, const DialogPtr& dialog);
	ButtonListPtr ReadButtonList(const nlohmann::json& buttonsNode, const DialogPtr& dialog);

private:
	bool _isRed;
	std::string _filename;
	OutputPtr _output;
	RootFactoryPtr _rootFactory;
	CommandManagerPtr _commandManager;
	std::map<std::string, DialogPtr> _dialogs;
	DialogPtr _rootDialog;
};
