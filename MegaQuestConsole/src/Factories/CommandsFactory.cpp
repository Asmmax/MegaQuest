#include "Factories/CommandsFactory.hpp"

#include "Factories/DialogFactory.hpp"
#include "Game/CommandManager.hpp"
#include "Game/Commands/AliasCommand.hpp"
#include "Game/Commands/QuitCommand.hpp"
#include "Game/Commands/ChoiceCommand.hpp"
#include "Game/Commands/ForceChoiceCommand.hpp"

#include "Utils/Reader.hpp"

#include <fstream>
#include <iostream>
#include <assert.h>

CommandsFactory::CommandsFactory(const std::string& filename, const DialogFactoryPtr& dialogFactory) :
    _isRed(false),
    _filename(filename),
    _dialogFactory(dialogFactory)
{
}

void CommandsFactory::Read()
{
    if (_isRed) {
        return;
    }

    _commandManager = nullptr;

    std::fstream file;
    file.open(_filename, std::ios::in);
    if (!file.is_open()) {
        return;
    }

    std::string input;
    std::string line;
    while (std::getline(file, line)) {
        input += line + "\n";
    }

    file.close();

    nlohmann::json root;
    try
    {
        root = nlohmann::json::parse(input);
    }
    catch (nlohmann::json::parse_error& ex)
    {
        std::cerr << ex.what() << std::endl;
        return;
    }

    auto commandError = Utils::Read(root, "error", QuestCore::TextString());
    _commandManager = std::make_shared<Game::CommandManager>(commandError);

    auto foundIt = root.find("commands");
    if (foundIt != root.end()) {
        auto commands = ReadCommands(*foundIt, _commandManager);
        for (auto& command : commands) {
            _commandManager->Register(command.first, command.second);
        }
    }

    _isRed = true;
}

std::map<std::string, Game::ICommand::Ptr> CommandsFactory::ReadCommands(const nlohmann::json& commandsNode, const CommandManagerPtr& commandManager)
{
    std::map<std::string, Game::ICommand::Ptr> result;

    if (!commandsNode.is_array()) {
        return result;
    }

    for (auto& jsonCommand : commandsNode) {
        auto command = ReadCommand(jsonCommand, commandManager);
        auto commandId = Utils::Read(jsonCommand, "command", std::string());
        result.emplace(commandId, command);
    }

    return result;
}

Game::ICommand::Ptr CommandsFactory::ReadCommand(const nlohmann::json& commandNode, const CommandManagerPtr& commandManager)
{
    std::string typeId = Utils::Read(commandNode, "type", std::string());
    if (typeId == "Alias") {
        auto alias = Utils::Read(commandNode, "alias", std::string());
        return std::make_shared<Game::AliasCommand>(commandManager, alias);
    }
    else if (typeId == "Quit") {
        return std::make_shared<Game::QuitCommand>();
    }
    else if (typeId == "Choice") {
        auto error = Utils::Read(commandNode, "error", QuestCore::TextString());
        auto buttonGroup = Utils::Read(commandNode, "buttonGroup", std::string());
        auto dialogId = Utils::Read(commandNode, "dialog", std::string());

        auto dialog = _dialogFactory->GetDialog(dialogId);
        assert(dialog);
        if (!dialog) {
            return nullptr;
        }

        return std::make_shared<Game::ChoiceCommand>(dialog, buttonGroup, error);
    }
    else if (typeId == "ForceChoice") {
        auto buttonGroup = Utils::Read(commandNode, "buttonGroup", std::string());
        auto dialogId = Utils::Read(commandNode, "dialog", std::string());

        auto dialog = _dialogFactory->GetDialog(dialogId);
        assert(dialog);
        if (!dialog) {
            return nullptr;
        }

        auto choice = Utils::Read<int>(commandNode, "choice", 0);
        return std::make_shared<Game::ForceChoiceCommand>(dialog, buttonGroup, choice);
    }

    return nullptr;
}

Game::CommandManager::Ptr CommandsFactory::GetCommandManager()
{
    Read();
    return _commandManager;
}
