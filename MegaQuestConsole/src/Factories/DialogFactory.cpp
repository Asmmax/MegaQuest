#include "Factories/DialogFactory.hpp"

#include "Game/Model.hpp"
#include "Game/IButtonList.hpp"
#include "Game/IDialog.hpp"

#include "Containers/GlobalContext.hpp"
#include "Containers/GlobalRootReader.hpp"

#include <fstream>
#include <iostream>
#include <assert.h>

DialogFactory::DialogFactory(const std::string& filename):
    _isRed(false),
    _filename(filename)
{
}

Game::Model::Ptr DialogFactory::GetModel()
{
    if (!Read()) {
        return nullptr;
    }

    return GlobalContext::GetContainer<Game::Model>()->Get("root_model");
}

Game::IDialog::Ptr DialogFactory::GetDialog(const std::string& id)
{
    if (!Read()) {
        return nullptr;
    }

    return GlobalContext::GetContainer<Game::IDialog>()->Get(id);
}

Game::IButtonList::Ptr DialogFactory::GetButtonList(const std::string& id)
{
    if (!Read()) {
        return nullptr;
    }

    return GlobalContext::GetContainer<Game::IButtonList>()->Get(id);
}


bool DialogFactory::Read()
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
