#include "Factories/CommandsFactory.hpp"

#include "Game/CommandManager.hpp"

#include "Containers/GlobalContext.hpp"
#include "Containers/GlobalRootReader.hpp"

#include <fstream>
#include <iostream>

CommandsFactory::CommandsFactory(const std::string& filename) :
    _isRed(false),
    _filename(filename)
{
}

Game::CommandManager::Ptr CommandsFactory::GetCommandManager()
{
    if (!Read()) {
        return nullptr;
    }

    return GlobalContext::GetContainer<Game::CommandManager>()->Get("main_commands");
}

bool CommandsFactory::Read()
{
    if (_isRed) {
        return true;
    }

    std::fstream file;
    file.open(_filename, std::ios::in);
    if (!file.is_open()) {
        return false;
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
        return false;
    }

    GlobalRootReader::Instance().AddRoot(root);

    _isRed = true;
    return true;
}
