#include "Factories/DialogFactory.hpp"
#include "Game/Dialogs/SimpleDialog.hpp"
#include "Game/Dialogs/SwitchDialog.hpp"
#include "Factories/IRootFactory.hpp"
#include "Game/ButtonLists/SimpleButtonList.hpp"
#include "Game/Dialogs/InventoryDialog.hpp"
#include "Game/ButtonLists/InventoryButtonList.hpp"
#include "Game/ButtonLists/SwitchButtonList.hpp"

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

    foundIt = root.find("buttonLists");
    if (foundIt != root.end()) {
        CreateButtonLists(*foundIt);
    }

    foundIt = root.find("dialogs");
    if (foundIt != root.end()) {
        ReadDialogs(*foundIt);
    }

    foundIt = root.find("buttonLists");
    if (foundIt != root.end()) {
        ReadButtonLists(*foundIt);
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
        auto id = Utils::Read(jsonDialog, "id", std::string());
        _dialogs.emplace(id, dialog);
    }
}

Game::IDialog::Ptr DialogFactory::CreateDialog(const nlohmann::json& dialogNode)
{
    std::string typeId = Utils::Read(dialogNode, "type", std::string());
    if (typeId == "Simple") {

        auto paragraphId = Utils::Read(dialogNode, "paragraph", std::string());
        auto paragraph = _rootFactory->GetParagraph(paragraphId);

        auto intro = Utils::Read(dialogNode, "intro", QuestCore::TextString());
        return std::make_shared<Game::SimpleDialog>(_output, intro, paragraph);
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
        auto id = Utils::Read(jsonDialog, "id", std::string());
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
            auto buttonGroups = ReadButtonGroups(*buttonsJsonIt);
            for (auto buttonGroup : buttonGroups) {
                simpleDialog->AddButtonList(buttonGroup);
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

        auto buttonsJsonIt = dialogNode.find("buttonGroups");
        if (buttonsJsonIt != dialogNode.end()) {
            auto buttonGroups = ReadButtonGroups(*buttonsJsonIt);
            for (auto buttonGroup : buttonGroups) {
                switchDialog->AddButtonList(buttonGroup);
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
            auto buttonGroups = ReadButtonGroups(*buttonsJsonIt);
            for (auto buttonGroup : buttonGroups) {
                inventoryDialog->AddButtonList(buttonGroup);
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

void DialogFactory::CreateButtonLists(const nlohmann::json& buttonListsNode)
{
    if (!buttonListsNode.is_array()) {
        return;
    }

    for (auto& jsonButonList : buttonListsNode) {
        auto butonList = CreateButtonList(jsonButonList);
        auto id = Utils::Read(jsonButonList, "id", std::string());
        _buttonLists.emplace(id, butonList);
    }
}

Game::IButtonList::Ptr DialogFactory::CreateButtonList(const nlohmann::json& buttonListNode)
{
    std::string typeId = Utils::Read(buttonListNode, "type", std::string());
    if (typeId == "Simple") {

        auto containerId = Utils::Read(buttonListNode, "container", std::string());
        auto container = _rootFactory->GetCaseContainer(containerId);

        bool show = Utils::Read<bool>(buttonListNode, "show", false);

        auto error = Utils::Read(buttonListNode, "error", QuestCore::TextString());
        return std::make_shared<Game::SimpleButtonList>(_output, error, show, container);
    }
    else if (typeId == "Inventory") {

        auto inventoryId = Utils::Read(buttonListNode, "inventory", std::string());
        auto inventory = _rootFactory->GetInventory(inventoryId);

        auto error = Utils::Read(buttonListNode, "error", QuestCore::TextString());

        std::vector<int> counts;

        auto foundIt = buttonListNode.find("counts");
        if (foundIt != buttonListNode.end()) {
            for (auto& count : *foundIt) {
                counts.push_back(count.get<int>());
            }
        }

        auto putMessage = Utils::Read(buttonListNode, "put", QuestCore::TextString());
        auto throwMessage = Utils::Read(buttonListNode, "throw", QuestCore::TextString());

        return std::make_shared<Game::InventoryButtonList>(_output, error, inventory, counts, putMessage, throwMessage);
    }
    else if (typeId == "Switch") {
        return std::make_shared<Game::SwitchButtonList>();
    }

    return nullptr;
}

void DialogFactory::ReadButtonLists(const nlohmann::json& buttonListsNode)
{
    if (!buttonListsNode.is_array()) {
        return;
    }

    for (auto& jsonButtonList : buttonListsNode) {
        auto id = Utils::Read(jsonButtonList, "id", std::string());
        auto foundIt = _buttonLists.find(id);
        if (foundIt != _buttonLists.end()) {
            InitButtonList(foundIt->second, jsonButtonList);
        }
    }
}

void DialogFactory::InitButtonList(const Game::IButtonList::Ptr& buttonList, const nlohmann::json& buttonListNode)
{
    std::string typeId = Utils::Read(buttonListNode, "type", std::string());
    if (typeId == "Simple") {
        auto simpleButtonList = std::dynamic_pointer_cast<Game::SimpleButtonList>(buttonList);

    }
    else if (typeId == "Inventory") {

        auto inventoryButtonList = std::dynamic_pointer_cast<Game::InventoryButtonList>(buttonList);
    }
    else if (typeId == "Switch") {
        auto swicthButtonList = std::dynamic_pointer_cast<Game::SwitchButtonList>(buttonList);

        auto foundIt = buttonListNode.find("targets");
        if (foundIt == buttonListNode.end()) {
            return;
        }

        for (auto& jsonButons : *foundIt) {
            auto buttonListId = jsonButons.get<std::string>();
            auto foundIt = _buttonLists.find(buttonListId);
            assert(foundIt != _buttonLists.end());
            if (foundIt == _buttonLists.end()) {
                continue;
            }

            swicthButtonList->AddButtonList(foundIt->second);
        }

    }
}

std::vector<Game::IButtonList::Ptr> DialogFactory::ReadButtonGroups(const nlohmann::json& buttonGroupsNode)
{
    std::vector<Game::IButtonList::Ptr> result;

    if (!buttonGroupsNode.is_array()) {
        return result;
    }

    for (auto& jsonButons : buttonGroupsNode) {
        auto buttonListId = jsonButons.get<std::string>();
        auto foundIt = _buttonLists.find(buttonListId);
        assert(foundIt != _buttonLists.end());
        if (foundIt == _buttonLists.end()) {
            continue;
        }

        result.push_back(foundIt->second);
    }

    return result;
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

Game::IButtonList::Ptr DialogFactory::GetButtonList(const std::string& id)
{
    Read();
    auto foundIt = _buttonLists.find(id);
    if (foundIt == _buttonLists.end()) {
        return nullptr;
    }
    return foundIt->second;
}
