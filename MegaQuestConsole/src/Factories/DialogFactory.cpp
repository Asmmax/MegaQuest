#include "Factories/DialogFactory.hpp"
#include "Game/Dialogs/SimpleDialog.hpp"
#include "Game/Dialogs/SwitchDialog.hpp"
#include "Factories/IRootFactory.hpp"
#include "Game/SimpleButtonList.hpp"
#include "Game/Dialogs/InventoryDialog.hpp"
#include "Game/InventoryButtonList.hpp"

#include "Utils/Reader.hpp"

#include <fstream>
#include <iostream>
#include <assert.h>

DialogFactory::DialogFactory(const std::string& filename, const OutputPtr& output, const RootFactoryPtr& rootFactory):
    _isRed(false),
    _filename(filename),
    _output(output),
    _rootFactory(rootFactory)
{
}

void DialogFactory::Read()
{
    if (_isRed) {
        return;
    }

    _rootDialog = nullptr;

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

    auto foundIt = root.find("dialogs");
    if (foundIt != root.end()) {
        CreateDialogs(*foundIt);
    }

    foundIt = root.find("dialogs");
    if (foundIt != root.end()) {
        ReadDialogs(*foundIt);
    }

    foundIt = root.find("rootDialog");
    if (foundIt != root.end()) {
        ReadRootDialog(*foundIt);
    }

    _isRed = true;
}

void DialogFactory::CreateDialogs(const nlohmann::json& dialogsNode)
{
    if (!dialogsNode.is_array()) {
        return;
    }

    for (auto& jsonDialog : dialogsNode) {
        auto dialog = CreateDialog(jsonDialog);
        auto id = Utils::Read(jsonDialog, "key", std::string());
        _dialogs.emplace(id, dialog);
    }
}

Game::IDialog::Ptr DialogFactory::CreateDialog(const nlohmann::json& dialogNode)
{
    std::string typeId = Utils::Read(dialogNode, "type", std::string());
    if (typeId == "Simple") {

        auto paragraphId = Utils::Read(dialogNode, "paragraph", std::string());
        auto paragraph = _rootFactory->GetRootParagraph(paragraphId);

        auto containerId = Utils::Read(dialogNode, "container", std::string());
        auto container = _rootFactory->GetRootCaseContainer(containerId);

        auto intro = Utils::Read(dialogNode, "intro", QuestCore::TextString());
        return std::make_shared<Game::SimpleDialog>(_output, intro, paragraph, container);
    }
    else if (typeId == "Switch") {
        auto intro = Utils::Read(dialogNode, "intro", QuestCore::TextString());
        return std::make_shared<Game::SwitchDialog>(_output, intro);
    }
    else if (typeId == "Inventory") {
        auto inventoryId = Utils::Read(dialogNode, "inventory", std::string());
        auto inventory = _rootFactory->GetInventory(inventoryId);

        auto intro = Utils::Read(dialogNode, "intro", QuestCore::TextString());
        return std::make_shared<Game::InventoryDialog>(_output, intro, inventory);
    }

    return nullptr;
}

void DialogFactory::ReadDialogs(const nlohmann::json& dialogsNode)
{
    if (!dialogsNode.is_array()) {
        return;
    }

    for (auto& jsonDialog : dialogsNode) {
        auto id = Utils::Read(jsonDialog, "key", std::string());
        auto foundIt = _dialogs.find(id);
        if (foundIt != _dialogs.end()) {
            InitDialog(foundIt->second, jsonDialog);
        }
    }
}

void DialogFactory::InitDialog(const Game::IDialog::Ptr& dialog, const nlohmann::json& dialogNode)
{
    std::string typeId = Utils::Read(dialogNode, "type", std::string());
    if (typeId == "Simple") {
        auto simpleDialog = std::dynamic_pointer_cast<Game::SimpleDialog>(dialog);
        auto buttonsJsonIt = dialogNode.find("buttonGroups");
        if (buttonsJsonIt != dialogNode.end()) {
            auto buttonLists = ReadButtonLists(*buttonsJsonIt, simpleDialog);
            for (auto buttonList : buttonLists) {
                simpleDialog->AddButtonList(buttonList.first, buttonList.second);
            }
        }
    }
    else if (typeId == "Switch") {
        auto switchDialog = std::dynamic_pointer_cast<Game::SwitchDialog>(dialog);
        
        std::vector<std::string> dialogs;
        auto foundIt = dialogNode.find("dialogs");
        if (foundIt != dialogNode.end()) {
            for (auto& elem : *foundIt) {
                dialogs.push_back(elem.get<std::string>());
            }
        }

        for (auto dialogId : dialogs) {
            auto foundSubDialog = _dialogs.find(dialogId);
            assert(foundSubDialog != _dialogs.end());
            if (foundSubDialog != _dialogs.end()) {
                switchDialog->AddDialog(foundSubDialog->second);
            }
        }
    }
    else if (typeId == "Inventory") {
        auto inventoryDialog = std::dynamic_pointer_cast<Game::InventoryDialog>(dialog);
        auto buttonsJsonIt = dialogNode.find("buttonGroups");
        if (buttonsJsonIt != dialogNode.end()) {
            auto buttonLists = ReadButtonLists(*buttonsJsonIt, inventoryDialog);
            for (auto buttonList : buttonLists) {
                inventoryDialog->AddButtonList(buttonList.first, buttonList.second);
            }
        }
    }
}

void DialogFactory::ReadRootDialog(const nlohmann::json& rootNode)
{
    auto dialogId = rootNode.get<std::string>();

    auto foundIt = _dialogs.find(dialogId);
    assert(foundIt != _dialogs.end());
    if (foundIt != _dialogs.end()) {
        _rootDialog = foundIt->second;
    }
}

std::vector<std::pair<std::string, Game::IButtonList::Ptr>> DialogFactory::ReadButtonLists(const nlohmann::json& buttonsNode, const DialogPtr& dialog)
{
    std::vector<std::pair<std::string, Game::IButtonList::Ptr>> result;

    if (!buttonsNode.is_array()) {
        return result;
    }

    for (auto& jsonButons : buttonsNode) {
        auto butonList = ReadButtonList(jsonButons, dialog);
        auto id = Utils::Read(jsonButons, "actionKey", std::string());
        result.emplace_back(id, butonList);
    }

    return result;
}

Game::IButtonList::Ptr DialogFactory::ReadButtonList(const nlohmann::json& buttonsNode, const DialogPtr& dialog)
{
    std::string typeId = Utils::Read(buttonsNode, "type", std::string());
    if (typeId == "Simple") {

        auto error = Utils::Read(buttonsNode, "error", QuestCore::TextString());
        return std::make_shared<Game::SimpleButtonList>(dialog, error);
    }
    else if (typeId == "Inventory") {

        auto inventoryId = Utils::Read(buttonsNode, "inventory", std::string());
        auto inventory = _rootFactory->GetInventory(inventoryId);

        auto error = Utils::Read(buttonsNode, "error", QuestCore::TextString());

        std::vector<int> counts;

        auto foundIt = buttonsNode.find("counts");
        if (foundIt != buttonsNode.end()) {
            for (auto& count : *foundIt) {
                counts.push_back(count.get<int>());
            }
        }

        auto putMessage = Utils::Read(buttonsNode, "put", QuestCore::TextString());
        auto throwMessage = Utils::Read(buttonsNode, "throw", QuestCore::TextString());

        return std::make_shared<Game::InventoryButtonList>(dialog, error, inventory, counts, putMessage, throwMessage);
    }
    
    return nullptr;
}

Game::IDialog::Ptr DialogFactory::GetRootDialog()
{
    Read();
    return _rootDialog;
}

Game::IDialog::Ptr DialogFactory::GetDialog(const std::string& id)
{
    Read();
    auto foundIt = _dialogs.find(id);
    if (foundIt == _dialogs.end()) {
        return nullptr;
    }
    return foundIt->second;
}
