#include "Factories/JsonRoomFactory.hpp"
#include "ParagraphStateMachine.hpp"
#include "SimpleRoom.hpp"
#include "TextParagraph.hpp"
#include "ParagraphChanging.hpp"
#include "AutoActionSwitcher.hpp"
#include "ActionGroup.hpp"
#include "GiftReceiving.hpp"
#include "ItemInfo.hpp"
#include "Forms.hpp"

#include <fstream>
#include <iostream>

using namespace QuestCore;

JsonRoomFactory::JsonRoomFactory(const std::string& filename, const std::shared_ptr<Inventory>& playerInventory) :
    _filename(filename),
    _playerInventory(playerInventory)
{
}

using namespace std;

std::shared_ptr<IRoom> JsonRoomFactory::GetRoom()
{
    std::fstream file;
    file.open(_filename, std::ios::in);
    if (!file.is_open()) {
        return nullptr;
    }
    
    std::string input;
    std::string line;
    while (std::getline(file, line)) {
        input+= line + "\n";
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
        return nullptr;
    }

    auto foundIt = root.find("itemInfos");
    if (foundIt != root.end()) {
        ReadItems(*foundIt);
    }

    foundIt = root.find("paragraphs");
    if (foundIt != root.end()) {
        CreateParagraphs(*foundIt);
        ReadParagraphs(*foundIt);
    }

    auto startParagraph = GetRootParagraph();
    auto road = std::make_shared<SimpleRoom>(TextString::FromUtf8(u8"Custom"), startParagraph);
    return road;
}

void JsonRoomFactory::ReadItems(const nlohmann::json& itemsNode)
{
    if (!itemsNode.is_array()) {
        return;
    }

    for (auto& jsonItemInfo : itemsNode) {
        auto isNullable = Read<bool>(jsonItemInfo, "isNullable", false);
        auto id = Read<std::string>(jsonItemInfo, "id", std::string());
        auto itemInfo = std::make_shared<QuestCore::ItemInfo>(isNullable);
        auto res = _items.emplace(id, itemInfo);

        if (!res.second) {
            continue;
        }

        auto foundIt = jsonItemInfo.find("forms");
        if (foundIt != jsonItemInfo.end()) {
            ReadForms(*foundIt, itemInfo);
        }
    }
}

void JsonRoomFactory::ReadForms(const nlohmann::json& formsNode, const std::shared_ptr<QuestCore::ItemInfo>& itemInfo)
{
    if (!formsNode.is_array()) {
        return;
    }

    for (auto& jsonForm : formsNode) {
        auto form = ReadForm(jsonForm);
        itemInfo->AddForm(form);
    }
}

std::shared_ptr<QuestCore::FormBase> JsonRoomFactory::ReadForm(const nlohmann::json& formNode)
{
    std::string typeId = Read(formNode, "type", std::string());
    if(typeId == "SpecificForm") {
        std::vector<int> counts = Read(formNode, "counts", std::vector<int>());
        TextString text = Read(formNode, "text", TextString());
        return std::make_shared<SpecificForm>(counts, text);
    } 
    else if (typeId == "TailForm") {
        std::vector<int> digits = Read(formNode, "digits", std::vector<int>());
        int notation = Read(formNode, "notation", 10);
        TextString text = Read(formNode, "text", TextString());
        return std::make_shared<TailForm>(notation, digits, text);
    }
    else if (typeId == "DefaultForm") {
        TextString text = Read(formNode, "text", TextString());
        return std::make_shared<FormBase>(text);
    }

    return nullptr;
}

void JsonRoomFactory::CreateParagraphs(const nlohmann::json& paragraphsNode)
{
    if (!paragraphsNode.is_array()) {
        return;
    }

    for (auto& jsonParagraph : paragraphsNode) {
        auto paragraph = CreateParagraph(jsonParagraph);
        auto id = Read<std::string>(jsonParagraph, "id", std::string());
        auto res = _paragraphs.emplace(id, paragraph);
    }
}

void JsonRoomFactory::ReadParagraphs(const nlohmann::json& paragraphsNode)
{
    if (!paragraphsNode.is_array()) {
        return;
    }

    for (auto& jsonParagraph : paragraphsNode) {
        auto id = Read<std::string>(jsonParagraph, "id", std::string());
        auto foundIt = _paragraphs.find(id);
        if (foundIt != _paragraphs.end()) {
            InitParagraph(foundIt->second, jsonParagraph);
        }
    }
}

std::shared_ptr<QuestCore::IParagraph> JsonRoomFactory::CreateParagraph(const nlohmann::json& paragraphNode)
{
    std::string typeId = Read(paragraphNode, "type", std::string());
    if (typeId == "ParagraphStateMachine") {
        return std::make_shared<ParagraphStateMachine>();
    }
    else if (typeId == "TextParagraph") {
        TextString text = Read(paragraphNode, "text", TextString());
        return std::make_shared<TextParagraph>(text);
    }

    return nullptr;
}

void JsonRoomFactory::InitParagraph(const std::shared_ptr<QuestCore::IParagraph>& paragraph, const nlohmann::json& paragraphNode)
{
    std::string typeId = Read(paragraphNode, "type", std::string());
    if (typeId == "ParagraphStateMachine") {
        auto stateMachine = std::static_pointer_cast<QuestCore::ParagraphStateMachine>(paragraph);
        std::string target = Read(paragraphNode, "target", std::string());
        auto foundIt = _paragraphs.find(target);
        assert(foundIt != _paragraphs.end());

        if (foundIt != _paragraphs.end()) {
            stateMachine->SetState(foundIt->second);
        }
    }
    else if (typeId == "TextParagraph") {
        auto foundIt = paragraphNode.find("actions");
        if (foundIt != paragraphNode.end()) {
            auto actions = ReadActions(*foundIt);
            for (auto& action : actions) {
                paragraph->GetActionContainer().AddAction(action);
            }
        }
    }
}

std::vector<std::shared_ptr<QuestCore::IAction>> JsonRoomFactory::ReadActions(const nlohmann::json& actionsNode)
{
    std::vector<std::shared_ptr<QuestCore::IAction>> result;

    if (!actionsNode.is_array()) {
        return result;
    }

    for (auto& jsonAction : actionsNode) {
        auto action = ReadAction(jsonAction);
        result.push_back(action);
    }
    return result;
}

std::shared_ptr<QuestCore::IAction> JsonRoomFactory::ReadAction(const nlohmann::json& actionNode)
{
    std::string typeId = Read(actionNode, "type", std::string());
    if (typeId == "StateChanging") {

        std::string stateMachineId = Read(actionNode, "stateMachine", std::string());
        auto foundIt = _paragraphs.find(stateMachineId);
        assert(foundIt != _paragraphs.end());
        if (foundIt == _paragraphs.end()) {
            return nullptr;
        }

        auto stateMachine = std::dynamic_pointer_cast<QuestCore::ParagraphStateMachine>(foundIt->second);
        assert(stateMachine);
        if (!stateMachine) {
            return nullptr;
        }

        std::string target = Read(actionNode, "target", std::string());
        foundIt = _paragraphs.find(target);
        assert(foundIt != _paragraphs.end());
        if (foundIt == _paragraphs.end()) {
            return nullptr;
        }

        TextString text = Read(actionNode, "text", TextString());

        return std::make_shared<QuestCore::ParagraphChanging>(text, stateMachine, foundIt->second);
    }
    else if (typeId == "AutoActionSwitcher") {
        auto autoSwitcher = std::make_shared<QuestCore::AutoActionSwitcher>();
        auto foundIt = actionNode.find("actions");
        if (foundIt != actionNode.end()) {
            auto actions = ReadActions(*foundIt);
            for (auto& action : actions) {
                autoSwitcher->AddAction(action);
            }
        }

        auto actions = autoSwitcher->GetActions();

        size_t _switch = Read<int>(actionNode, "switch", 0);
        assert(_switch < actions.size());
        if (_switch < actions.size()) {
            autoSwitcher->Switch(actions[_switch]);
        }

        size_t _final = Read<int>(actionNode, "final", 0);
        assert(_final < actions.size());
        if (_final < actions.size()) {
            autoSwitcher->SetFinalAction(actions[_final]);
        }

        return autoSwitcher;
    }
    else if (typeId == "ActionGroup") {
        TextString text = Read(actionNode, "text", TextString());

        auto actionGroup = std::make_shared<QuestCore::ActionGroup>(text);
        auto foundIt = actionNode.find("actions");
        if (foundIt != actionNode.end()) {
            auto actions = ReadActions(*foundIt);
            for (auto& action : actions) {
                actionGroup->AddAction(action);
            }
        }
        return actionGroup;
    }
    else if (typeId == "GiftReceiving") {

        std::shared_ptr<QuestCore::Inventory> inventory;
        std::string inventoryId = Read(actionNode, "inventory", std::string());
        if (inventoryId == "player") {
            inventory = _playerInventory;
        }

        TextString text = Read(actionNode, "text", TextString());

        auto gift = std::make_shared<QuestCore::GiftReceiving>(text, inventory);
        
        auto foundIt = actionNode.find("items");
        assert(foundIt != actionNode.end());
        if (foundIt != actionNode.end()) {
            auto items = ReadGiftItems(*foundIt);
            for (auto& item : items) {
                gift->AddThings(item.first, item.second);
            }
        }

        return gift;
    }

    return nullptr;
}

std::map<std::shared_ptr<QuestCore::ItemInfo>, int> JsonRoomFactory::ReadGiftItems(const nlohmann::json& itemsNode)
{
    std::map<std::shared_ptr<QuestCore::ItemInfo>, int> result;
    
    if (!itemsNode.is_array()) {
        return result;
    }

    for (auto& jsonItem : itemsNode) {
        auto item = ReadGiftItem(jsonItem);
        result.insert(item);
    }

    return result;
}

std::pair<std::shared_ptr<QuestCore::ItemInfo>, int> JsonRoomFactory::ReadGiftItem(const nlohmann::json& itemNode)
{
    std::pair<std::shared_ptr<QuestCore::ItemInfo>, int> item;
    std::string id = Read(itemNode, "id", std::string());

    auto foundIt = _items.find(id);
    assert(foundIt != _items.end());
    if (foundIt == _items.end()) {
        return item;
    }

    item.first = foundIt->second;

    int count = Read(itemNode, "count", 0);
    item.second = count;

    return item;
}

std::shared_ptr<QuestCore::IParagraph> JsonRoomFactory::GetRootParagraph()
{
    auto foundIt = _paragraphs.find("root");
    if (foundIt != _paragraphs.end()) {
        return foundIt->second;
    }
    return std::shared_ptr<QuestCore::IParagraph>();
}
