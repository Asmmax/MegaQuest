#include "Factories/JsonQuestFactory.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"
#include "Paragraphs/TextParagraph.hpp"
#include "Paragraphs/InventoryParagraph.hpp"
#include "Paragraphs/ParagraphGroup.hpp"
#include "Paragraphs/ConditionalParagraph.hpp"
#include "CaseContainers/CaseContainerStateMachine.hpp"
#include "CaseContainers/SimpleCaseContainer.hpp"
#include "CaseContainers/CaseContainerGroup.hpp"
#include "CaseContainers/ConditionalCaseContainer.hpp"
#include "Item.hpp"
#include "Forms.hpp"
#include "Inventory.hpp"
#include "Value.hpp"
#include "Conditions/Comparison.hpp"
#include "Actions/ParagraphSwitching.hpp"
#include "Actions/CaseContainerSwitching.hpp"
#include "Actions/Transfer.hpp"
#include "Actions/Clearing.hpp"
#include "Actions/Copying.hpp"
#include "QuestBase.hpp"
#include "Factories/ITextViewFactory.hpp"
#include "Factories/IButtonPanelFactory.hpp"

#include <fstream>
#include <iostream>

using namespace QuestCore;

JsonQuestFactory::JsonQuestFactory(const std::string& filename) :
    _filename(filename)
{
}

std::shared_ptr<QuestCore::QuestBase> JsonQuestFactory::GetQuest(const std::shared_ptr<ITextViewFactory>& textViewFactory,
const std::shared_ptr<IButtonPanelFactory>& buttonsFactory)
{
    if (!Read()) {
        return nullptr;
    }

    std::vector<QuestCore::Root> roots;
    for (auto& input : _inputs) {
        QuestCore::Root root;
        root.paragraph = input.second.paragraph;
        root.caseContainer = input.second.caseContainer;
        root.textView = textViewFactory->GetTextView(input.first);
        root.buttons = buttonsFactory->GetButtonPanel(input.first);
        roots.push_back(root);
    }

    return std::make_shared<QuestCore::QuestBase>(roots);
}

bool JsonQuestFactory::Read()
{
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
    }

    foundIt = root.find("containers");
    if (foundIt != root.end()) {
        CreateContainers(*foundIt);
    }

    foundIt = root.find("paragraphs");
    if (foundIt != root.end()) {
        ReadParagraphs(*foundIt);
    }

    foundIt = root.find("containers");
    if (foundIt != root.end()) {
        ReadContainers(*foundIt);
    }

    foundIt = root.find("inputs");
    if (foundIt != root.end()) {
        ReadInputs(*foundIt);
    }

    return true;
}

void JsonQuestFactory::ReadHotKeys(const nlohmann::json& keysNode)
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

void JsonQuestFactory::ReadInputs(const nlohmann::json& inputsNode)
{
    if (!inputsNode.is_array()) {
        return;
    }

    for (auto& jsonInput : inputsNode) {
        std::string key = Read(jsonInput, "key", std::string());
        
        std::string paragraphId = Read(jsonInput, "paragraph", std::string());
        std::string containerId = Read(jsonInput, "container", std::string());

        auto paragraphIt = _paragraphs.find(paragraphId);
        assert(paragraphIt != _paragraphs.end());
        if (paragraphIt == _paragraphs.end()){
            continue;
        }

        auto containerIt = _containers.find(containerId);
        assert(containerIt != _containers.end());
        if (containerIt == _containers.end()) {
            continue;
        }

        _inputs.emplace(key, Node{ paragraphIt->second, containerIt->second });
    }
}

void JsonQuestFactory::ReadItems(const nlohmann::json& itemsNode)
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

        auto item = std::make_shared<QuestCore::Item>(id, forms, isNullable);
        _items.emplace(id, item);
    }
}

void JsonQuestFactory::ReadForms(const nlohmann::json& formStrNode, FormatedString& forms)
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

std::shared_ptr<QuestCore::FormBase> JsonQuestFactory::ReadForm(const nlohmann::json& formNode)
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

void JsonQuestFactory::ReadInventory(const nlohmann::json& inventoriesNode)
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

void JsonQuestFactory::CreateParagraphs(const nlohmann::json& paragraphsNode)
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

void JsonQuestFactory::ReadParagraphs(const nlohmann::json& paragraphsNode)
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

std::shared_ptr<QuestCore::IParagraph> JsonQuestFactory::CreateParagraph(const nlohmann::json& paragraphNode)
{
    std::string typeId = Read(paragraphNode, "type", std::string());
    if (typeId == "StateMachine") {
        return std::make_shared<ParagraphStateMachine>();
    }
    else if (typeId == "Text") {
        TextString text = Read(paragraphNode, "text", TextString());
        return std::make_shared<TextParagraph>(text);
    }
    else if (typeId == "Inventory") {
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
    else if (typeId == "Group"){
        TextString gap = Read(paragraphNode, "gap", TextString());
        return std::make_shared<ParagraphGroup>(gap);
    }
    else if (typeId == "Condition") {
        return std::make_shared<ConditionalParagraph>();
    }

    return nullptr;
}

void JsonQuestFactory::InitParagraph(const std::shared_ptr<QuestCore::IParagraph>& paragraph, const nlohmann::json& paragraphNode)
{
    std::string typeId = Read(paragraphNode, "type", std::string());
    if (typeId == "StateMachine") {
        auto stateMachine = std::static_pointer_cast<ParagraphStateMachine>(paragraph);
        std::string target = Read(paragraphNode, "target", std::string());
        auto foundIt = _paragraphs.find(target);
        assert(foundIt != _paragraphs.end());

        if (foundIt != _paragraphs.end()) {
            stateMachine->SetState(foundIt->second);
        }
    }
    else if (typeId == "Inventory") {
        auto inventory = std::static_pointer_cast<InventoryParagraph>(paragraph);
        auto foundIt = paragraphNode.find("itemOrders");
        if (foundIt != paragraphNode.end()) {
            auto orders = ReadItemOrders(*foundIt);
            for (auto& order : orders) {
                inventory->SetItemOrder(order.first, order.second);
            }
        }
    }
    else if (typeId == "Group") {
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
    else if (typeId == "Condition") {
        auto conditional = std::static_pointer_cast<ConditionalParagraph>(paragraph);

        std::string thenParagraph = Read(paragraphNode, "then", std::string());
        if (!thenParagraph.empty()) {
            auto foundIt = _paragraphs.find(thenParagraph);
            assert(foundIt != _paragraphs.end());

            if (foundIt != _paragraphs.end()) {
                conditional->SetThenParagraph(foundIt->second);
            }
        }

        std::string elseParagraph = Read(paragraphNode, "else", std::string());
        if (!elseParagraph.empty()) {
            auto foundIt = _paragraphs.find(elseParagraph);
            assert(foundIt != _paragraphs.end());

            if (foundIt != _paragraphs.end()) {
                conditional->SetElseParagraph(foundIt->second);
            }
        }

        auto foundIt = paragraphNode.find("conditions");
        if (foundIt != paragraphNode.end()) {
            auto conditions = ReadConditions(*foundIt);
            for (auto& condition : conditions) {
                conditional->AddCondition(condition);
            }
        }
    }
}

void JsonQuestFactory::CreateContainers(const nlohmann::json& containersNode)
{
    if (!containersNode.is_array()) {
        return;
    }

    for (auto& jsonContainer : containersNode) {
        auto container = CreateContainer(jsonContainer);
        auto id = Read<std::string>(jsonContainer, "id", std::string());
        auto res = _containers.emplace(id, container);
    }
}

void JsonQuestFactory::ReadContainers(const nlohmann::json& containersNode)
{
    if (!containersNode.is_array()) {
        return;
    }

    for (auto& jsonContainer : containersNode) {
        auto id = Read<std::string>(jsonContainer, "id", std::string());
        auto foundIt = _containers.find(id);
        if (foundIt != _containers.end()) {
            InitContainer(foundIt->second, jsonContainer);
        }
    }
}

std::shared_ptr<QuestCore::ICaseContainer> JsonQuestFactory::CreateContainer(const nlohmann::json& containerNode)
{
    std::string typeId = Read(containerNode, "type", std::string());
    if (typeId == "StateMachine") {
        return std::make_shared<CaseContainerStateMachine>();
    }
    else if (typeId == "Simple") {
        return std::make_shared<SimpleCaseContainer>();
    }
    else if (typeId == "Group") {
        return std::make_shared<CaseContainerGroup>();
    }
    else if (typeId == "Condition") {
        return std::make_shared<ConditionalCaseContainer>();
    }

    return nullptr;
}

void JsonQuestFactory::InitContainer(const std::shared_ptr<QuestCore::ICaseContainer>& container, const nlohmann::json& containerNode)
{
    std::string typeId = Read(containerNode, "type", std::string());
    if (typeId == "StateMachine") {
        auto stateMachine = std::static_pointer_cast<CaseContainerStateMachine>(container);
        std::string target = Read(containerNode, "target", std::string());
        auto foundIt = _containers.find(target);
        assert(foundIt != _containers.end());

        if (foundIt != _containers.end()) {
            stateMachine->SetState(foundIt->second);
        }
    }
    else if (typeId == "Simple") {
        auto simple = std::static_pointer_cast<SimpleCaseContainer>(container);

        auto foundIt = containerNode.find("cases");
        if (foundIt != containerNode.end()) {
            auto& casesNode = *foundIt;
            if (!casesNode.is_array()) {
                return;
            }

            for (auto& jsonCase : casesNode) {
                std::string key = Read(jsonCase, "key", std::string());
                auto _case = ReadCase(jsonCase);
                if (_case.actions.empty()) {
                    continue;
                }

                if (key.empty()) {
                    simple->AddCase(_case);
                }
                else {
                    simple->AddCase(key, _case);
                }

            }
        }
    }
    else if (typeId == "Group") {
        auto group = std::static_pointer_cast<CaseContainerGroup>(container);

        auto foundIt = containerNode.find("containers");
        if (foundIt != containerNode.end()) {
            auto& childrenNode = *foundIt;
            if (!childrenNode.is_array()) {
                return;
            }

            for (auto& jsonChild : childrenNode) {
                auto containerId = jsonChild.get<std::string>();
                auto containerIt = _containers.find(containerId);
                assert(containerIt != _containers.end());

                if (containerIt != _containers.end()) {
                    group->AddCaseContainer(containerIt->second);
                }

            }
        }
    }
    else if (typeId == "Condition") {
        auto conditional = std::static_pointer_cast<ConditionalCaseContainer>(container);

        std::string thenContainer = Read(containerNode, "then", std::string());
        if (!thenContainer.empty()) {
            auto foundIt = _containers.find(thenContainer);
            assert(foundIt != _containers.end());

            if (foundIt != _containers.end()) {
                conditional->SetThenContainer(foundIt->second);
            }
        }

        std::string elseContainer = Read(containerNode, "else", std::string());
        if (!elseContainer.empty()) {
            auto foundIt = _containers.find(elseContainer);
            assert(foundIt != _containers.end());

            if (foundIt != _containers.end()) {
                conditional->SetElseContainer(foundIt->second);
            }
        }

        auto foundIt = containerNode.find("conditions");
        if (foundIt != containerNode.end()) {
            auto conditions = ReadConditions(*foundIt);
            for (auto& condition : conditions) {
                conditional->AddCondition(condition);
            }
        }
    }
}

std::vector<std::shared_ptr<QuestCore::IAction>> JsonQuestFactory::ReadActions(const nlohmann::json& actionsNode)
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

Case JsonQuestFactory::ReadCase(const nlohmann::json& caseNode)
{
    Case _case;

    auto foundIt = caseNode.find("actions");
    if (foundIt == caseNode.end()) {
        return _case;
    }

    _case.actions = ReadActions(*foundIt);
    _case.name = Read(caseNode, "text", TextString());

    return _case;
}

std::shared_ptr<QuestCore::IAction> JsonQuestFactory::ReadAction(const nlohmann::json& actionNode)
{
    std::string typeId = Read(actionNode, "type", std::string());
    if (typeId == "ParagraphSwitching") {

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

        return std::make_shared<QuestCore::ParagraphSwitching>(stateMachine, foundIt->second);
    }
    else if (typeId == "CasesSwitching") {

        std::string stateMachineId = Read(actionNode, "stateMachine", std::string());
        auto foundIt = _containers.find(stateMachineId);
        assert(foundIt != _containers.end());
        if (foundIt == _containers.end()) {
            return nullptr;
        }

        auto stateMachine = std::dynamic_pointer_cast<QuestCore::CaseContainerStateMachine>(foundIt->second);
        assert(stateMachine);
        if (!stateMachine) {
            return nullptr;
        }

        std::string target = Read(actionNode, "target", std::string());
        foundIt = _containers.find(target);
        assert(foundIt != _containers.end());
        if (foundIt == _containers.end()) {
            return nullptr;
        }

        return std::make_shared<QuestCore::CaseContainerSwitching>(stateMachine, foundIt->second);
    }
    else if (typeId == "Transfer") {

        std::shared_ptr<QuestCore::Inventory> source;
        std::string sourceId = Read(actionNode, "source", std::string());

        if (!sourceId.empty()) {
            auto foundItSource = _inventories.find(sourceId);
            assert(foundItSource != _inventories.end());

            if (foundItSource != _inventories.end()) {
                source = foundItSource->second;
            }
        }

        std::shared_ptr<QuestCore::Inventory> target;
        std::string targetId = Read(actionNode, "target", std::string());

        if (!targetId.empty()) {
            auto foundItTarget = _inventories.find(targetId);
            assert(foundItTarget != _inventories.end());

            if (foundItTarget != _inventories.end()) {
                target = foundItTarget->second;
            }
        }

        auto transfer = std::make_shared<Transfer>(source, target);
        
        auto foundIt = actionNode.find("items");
        if (foundIt != actionNode.end()) {
            auto items = ReadGiftItems(*foundIt);
            for (auto& item : items) {
                transfer->AddThings(item.first, item.second);
            }
        }

        return transfer;
    }
    else if (typeId == "Clearing") {

        std::shared_ptr<QuestCore::Inventory> inventory;
        std::string inventoryId = Read(actionNode, "inventory", std::string());

        auto foundItInventory = _inventories.find(inventoryId);
        assert(foundItInventory != _inventories.end());

        if (foundItInventory != _inventories.end()) {
            inventory = foundItInventory->second;
        }

        return std::make_shared<Clearing>(inventory);
    }
    else if (typeId == "Copying") {

        std::shared_ptr<QuestCore::Inventory> source;
        std::string sourceId = Read(actionNode, "source", std::string());

        auto foundItSource = _inventories.find(sourceId);
        assert(foundItSource != _inventories.end());

        if (foundItSource != _inventories.end()) {
            source = foundItSource->second;
        }

        std::shared_ptr<QuestCore::Inventory> target;
        std::string targetId = Read(actionNode, "target", std::string());

        auto foundItTarget = _inventories.find(targetId);
        assert(foundItTarget != _inventories.end());

        if (foundItTarget != _inventories.end()) {
            target = foundItTarget->second;
        }

        return std::make_shared<Copying>(source, target);
    }

    return nullptr;
}

std::vector<std::shared_ptr<QuestCore::ICondition>> JsonQuestFactory::ReadConditions(const nlohmann::json& conditionsNode)
{
    std::vector<std::shared_ptr<QuestCore::ICondition>> result;

    if (!conditionsNode.is_array()) {
        return result;
    }

    for (auto& jsonCondition : conditionsNode) {
        auto condition = ReadCondition(jsonCondition);
        result.push_back(condition);
    }
    return result;
}

std::shared_ptr<QuestCore::ICondition> JsonQuestFactory::ReadCondition(const nlohmann::json& conditionNode)
{
    std::string typeId = Read(conditionNode, "type", std::string());
    if (typeId == "Comparison") {

        auto leftPtr = std::shared_ptr<Value>();
        auto foundIt = conditionNode.find("left");
        if (foundIt != conditionNode.end()) {
            leftPtr = ReadValue(*foundIt);
        }
        assert(leftPtr);

        auto rightPtr = std::shared_ptr<Value>();
        foundIt = conditionNode.find("right");
        if (foundIt != conditionNode.end()) {
            rightPtr = ReadValue(*foundIt);
        }
        assert(rightPtr);

        Operation op = Operation::None;
        auto foundOpIt = conditionNode.find("operation");
        if (foundOpIt != conditionNode.end()) {
            op = ReadOperation(*foundOpIt);
        }

        return std::make_shared<QuestCore::Comparison>(leftPtr, rightPtr, op);
    }

    return nullptr;
}

std::shared_ptr<QuestCore::Value> JsonQuestFactory::ReadValue(const nlohmann::json& valueNode)
{
    std::string typeId = Read(valueNode, "type", std::string());
    if (typeId == "Simple") {
        int value = Read(valueNode, "value", 0);
        return std::make_shared<SimpleValue>(value);
    }
    else if (typeId == "Inventory") {
        
        std::shared_ptr<QuestCore::Item> item;
        std::string itemId = Read(valueNode, "item", std::string());
        auto foundIt = _items.find(itemId);
        assert(foundIt != _items.end());
        if (foundIt != _items.end()) {
            item = foundIt->second;
        }
        
        std::shared_ptr<QuestCore::Inventory> inventory;
        std::string inventoryId = Read(valueNode, "inventory", std::string());
        auto foundInventoryIt = _inventories.find(inventoryId);
        assert(foundInventoryIt != _inventories.end());
        if (foundInventoryIt != _inventories.end()) {
            inventory = foundInventoryIt->second;
        }
        
        return std::make_shared<InventoryValue>(item, inventory);
    }

    return nullptr;
}

QuestCore::Operation JsonQuestFactory::ReadOperation(const nlohmann::json& opNode)
{
    std::string opType = opNode.get<std::string>();

    if (opType == "Less") {
        return Operation::Less;
    }
    else if (opType == "Greater") {
        return Operation::Greater;
    }
    else if (opType == "Equal") {
        return Operation::Equal;
    }
    else if (opType == "NotLess") {
        return Operation::NotLess;
    }
    else if (opType == "NotGreater") {
        return Operation::NotGreater;
    }
    else if (opType == "NotEqual") {
        return Operation::NotEqual;
    }

    return Operation::None;
}

std::vector<std::pair<std::shared_ptr<QuestCore::Item>, int>> JsonQuestFactory::ReadGiftItems(const nlohmann::json& itemsNode)
{
    std::vector<std::pair<std::shared_ptr<QuestCore::Item>, int>> result;
    
    if (!itemsNode.is_array()) {
        return result;
    }

    for (auto& jsonItem : itemsNode) {
        auto item = ReadGiftItem(jsonItem);
        result.push_back(item);
    }

    return result;
}

std::pair<std::shared_ptr<QuestCore::Item>, int> JsonQuestFactory::ReadGiftItem(const nlohmann::json& itemNode)
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

std::vector<std::pair<std::shared_ptr<QuestCore::Item>, int>> JsonQuestFactory::ReadItemOrders(const nlohmann::json& itemsNode)
{
    std::vector<std::pair<std::shared_ptr<QuestCore::Item>, int>> result;

    if (!itemsNode.is_array()) {
        return result;
    }

    for (auto& jsonItem : itemsNode) {
        auto item = ReadItemOrder(jsonItem);
        result.push_back(item);
    }

    return result;
}

std::pair<std::shared_ptr<QuestCore::Item>, int> JsonQuestFactory::ReadItemOrder(const nlohmann::json& itemNode)
{
    std::pair<std::shared_ptr<QuestCore::Item>, int> item;
    std::string id = Read(itemNode, "id", std::string());

    auto foundIt = _items.find(id);
    assert(foundIt != _items.end());
    if (foundIt == _items.end()) {
        return item;
    }

    item.first = foundIt->second;

    int count = Read(itemNode, "order", 0);
    item.second = count;

    return item;
}
