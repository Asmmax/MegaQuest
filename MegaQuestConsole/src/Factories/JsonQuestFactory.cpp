#include "Factories/JsonQuestFactory.hpp"
#include "IParagraph.hpp"
#include "ICaseContainer.hpp"
#include "Inventory.hpp"

#include "Containers/GlobalContext.hpp"
#include "Containers/GlobalRootReader.hpp"

#include <fstream>
#include <iostream>

using namespace QuestCore;

JsonQuestFactory::JsonQuestFactory(const std::string& filename) :
    _isRed(false),
    _filename(filename)
{
}

IParagraph::Ptr JsonQuestFactory::GetParagraph(const std::string& rootKey)
{
    if (!Read()) {
        return nullptr;
    }

    return GlobalContext::GetContainer<IParagraph>()->Get(rootKey);
}

ICaseContainer::Ptr JsonQuestFactory::GetCaseContainer(const std::string& rootKey)
{
    if (!Read()) {
        return nullptr;
    }

    return GlobalContext::GetContainer<ICaseContainer>()->Get(rootKey);
}

Inventory::Ptr JsonQuestFactory::GetInventory(const std::string& inventoryKey)
{
    if (!Read()) {
        return nullptr;
    }

    return GlobalContext::GetContainer<Inventory>()->Get(inventoryKey);
}

bool JsonQuestFactory::Read()
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
