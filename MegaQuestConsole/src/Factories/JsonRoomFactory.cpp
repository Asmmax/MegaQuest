#include "Factories/JsonRoomFactory.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"
#include "SimpleRoom.hpp"
#include "Paragraphs/TextParagraph.hpp"
#include "Actions/ParagraphChanging.hpp"
#include "Actions/ActionGroup.hpp"
#include "Actions/GiftReceiving.hpp"
#include "Item.hpp"
#include "Forms.hpp"
#include "Inventory.hpp"
#include "Paragraphs/InventoryParagraph.hpp"
#include "Paragraphs/ParagraphGroup.hpp"
#include "CaseContainer.hpp"

#include <fstream>
#include <iostream>

using namespace QuestCore;

JsonRoomFactory::JsonRoomFactory(const std::string& filename) :
    _filename(filename)
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

    auto foundIt = root.find("hotKeys");
    if (foundIt != root.end()) {
        ReadHotKeys(*foundIt);
    }

    foundIt = root.find("items");
    if (foundIt != root.end()) {
        ReadItems(*foundIt);
    }

    foundIt = root.find("inventories");
    if (foundIt != root.end()) {
        ReadInventory(*foundIt);
    }

    foundIt = root.find("paragraphs");
    if (foundIt != root.end()) {
        CreateParagraphs(*foundIt);
        ReadParagraphs(*foundIt);
    }

    auto startParagraph = GetRootParagraph();
    auto road = std::make_shared<SimpleRoom>(startParagraph, _hotKeys);
    return road;
}

void JsonRoomFactory::ReadHotKeys(const nlohmann::json& keysNode)
{
    if (!keysNode.is_array()) {
        return;
    }

    for (auto& jsonKey : keysNode) {
        auto key = jsonKey.get<std::string>();
        _hotKeys.push_back(key);
    }

    auto lastIt = std::unique(_hotKeys.begin(), _hotKeys.end());
    _hotKeys.erase(lastIt, _hotKeys.end());
}

void JsonRoomFactory::ReadItems(const nlohmann::json& itemsNode)
{
    if (!itemsNode.is_array()) {
        return;
    }

    for (auto& jsonItem : itemsNode) {
        auto isNullable = Read<bool>(jsonItem, "isNullable", false);
        auto id = Read<std::string>(jsonItem, "id", std::string());

        FormatedString forms;
        auto foundIt = jsonItem.find("text");
        if (foundIt != jsonItem.end()) {
            ReadForms(*foundIt, forms);
        }

        auto item = std::make_shared<QuestCore::Item>(forms, isNullable);
        _items.emplace(id, item);
    }
}

void JsonRoomFactory::ReadForms(const nlohmann::json& formStrNode, FormatedString& forms)
{
    auto foundIt = formStrNode.find("forms");
    if (foundIt == formStrNode.end()) {
        return;
    }

    auto& formsNode = *foundIt;

    if (!formsNode.is_array()) {
        return;
    }

    for (auto& jsonForm : formsNode) {
        auto form = ReadForm(jsonForm);
        forms.AddForm(form);
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

void JsonRoomFactory::ReadInventory(const nlohmann::json& inventoriesNode)
{
    if (!inventoriesNode.is_array()) {
        return;
    }

    for (auto& jsonInventory : inventoriesNode) {
        auto id = Read<std::string>(jsonInventory, "id", std::string());

        auto inventory = std::make_shared<QuestCore::Inventory>();
        _inventories.emplace(id, inventory);

        auto foundIt = jsonInventory.find("items");
        if (foundIt != jsonInventory.end()) {
            auto items = ReadGiftItems(*foundIt);
            for (auto& item : items) {
                inventory->PutItem(item.first, item.second);
            }
        }
    }
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
    else if (typeId == "InventoryParagraph") {
        std::shared_ptr<QuestCore::Inventory> inventory;
        std::string inventoryId = Read(paragraphNode, "inventory", std::string());

        auto foundItInventory = _inventories.find(inventoryId);
        assert(foundItInventory != _inventories.end());

        if (foundItInventory != _inventories.end()) {
            inventory = foundItInventory->second;
        }

        FormatedString prefix;
        auto foundIt = paragraphNode.find("prefix");
        if (foundIt != paragraphNode.end()) {
            ReadForms(*foundIt, prefix);
        }

        FormatedString postfix;
        foundIt = paragraphNode.find("postfix");
        if (foundIt != paragraphNode.end()) {
            ReadForms(*foundIt, postfix);
        }

        TextString gap = Read(paragraphNode, "gap", TextString());

        return std::make_shared<InventoryParagraph>(prefix, gap, postfix, inventory);
    }
    else if (typeId == "ParagraphGroup"){
        TextString gap = Read(paragraphNode, "gap", TextString());
        return std::make_shared<ParagraphGroup>(gap);
    }

    return nullptr;
}

void JsonRoomFactory::InitParagraph(const std::shared_ptr<QuestCore::IParagraph>& paragraph, const nlohmann::json& paragraphNode)
{
    std::string typeId = Read(paragraphNode, "type", std::string());
    if (typeId == "ParagraphStateMachine") {
        auto stateMachine = std::static_pointer_cast<ParagraphStateMachine>(paragraph);
        std::string target = Read(paragraphNode, "target", std::string());
        auto foundIt = _paragraphs.find(target);
        assert(foundIt != _paragraphs.end());

        if (foundIt != _paragraphs.end()) {
            stateMachine->SetState(foundIt->second);
        }
    }
    else if (typeId == "TextParagraph") {
        auto foundIt = paragraphNode.find("cases");
        if (foundIt != paragraphNode.end()) {
            ReadCases(*foundIt, paragraph->GetCaseContainer());
        }
    }
    else if (typeId == "InventoryParagraph") {
        auto foundIt = paragraphNode.find("cases");
        if (foundIt != paragraphNode.end()) {
            ReadCases(*foundIt, paragraph->GetCaseContainer());
        }
    }
    else if (typeId == "ParagraphGroup") {
        auto group = std::static_pointer_cast<ParagraphGroup>(paragraph);

        auto foundIt = paragraphNode.find("paragraphs");
        if (foundIt != paragraphNode.end()) {
            auto& childrenNode = *foundIt;
            if (!childrenNode.is_array()) {
                return;
            }

            for (auto& jsonChild : childrenNode) {
                auto paragraphId = jsonChild.get<std::string>();
                auto paragraphIt = _paragraphs.find(paragraphId);
                assert(paragraphIt != _paragraphs.end());

                if (paragraphIt != _paragraphs.end()) {
                    group->AddParagraph(paragraphIt->second);
                }

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

void JsonRoomFactory::ReadCases(const nlohmann::json& casesNode, QuestCore::CaseContainer& cases)
{
    if (!casesNode.is_array()) {
        return;
    }

    for (auto& jsonCase : casesNode) {

        auto foundIt = jsonCase.find("action");
        if (foundIt == jsonCase.end()) {
            continue;
        }

        TextString text = Read(jsonCase, "text", TextString());
        auto action = ReadAction(*foundIt);
        Case _case{ text, action };

        std::string key = Read(jsonCase, "key", std::string());
        if (key.empty()) {
            cases.AddCase(_case);
        }
        else {
            assert(std::find(_hotKeys.begin(), _hotKeys.end(), key) != _hotKeys.end());
            cases.AddCase(key, _case);
        }
    }
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

        return std::make_shared<QuestCore::ParagraphChanging>(stateMachine, foundIt->second);
    }
    else if (typeId == "ActionGroup") {
        auto actionGroup = std::make_shared<QuestCore::ActionGroup>();
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

        auto foundItInventory = _inventories.find(inventoryId);
        assert(foundItInventory != _inventories.end());

        if (foundItInventory != _inventories.end()) {
            inventory = foundItInventory->second;
        }

        auto gift = std::make_shared<QuestCore::GiftReceiving>(inventory);
        
        auto foundIt = actionNode.find("items");
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

std::map<std::shared_ptr<QuestCore::Item>, int> JsonRoomFactory::ReadGiftItems(const nlohmann::json& itemsNode)
{
    std::map<std::shared_ptr<QuestCore::Item>, int> result;
    
    if (!itemsNode.is_array()) {
        return result;
    }

    for (auto& jsonItem : itemsNode) {
        auto item = ReadGiftItem(jsonItem);
        result.insert(item);
    }

    return result;
}

std::pair<std::shared_ptr<QuestCore::Item>, int> JsonRoomFactory::ReadGiftItem(const nlohmann::json& itemNode)
{
    std::pair<std::shared_ptr<QuestCore::Item>, int> item;
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
