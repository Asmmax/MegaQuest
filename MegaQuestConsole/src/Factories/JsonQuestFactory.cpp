#include "Factories/JsonQuestFactory.hpp"

#include "Generated/Item_gen.hpp"
#include "Generated/IParagraph_gen.hpp"
#include "Generated/ICaseContainer_gen.hpp"
#include "Generated/Inventory_gen.hpp"
#include "Generated/IAction_gen.hpp"

#include "Generated/FormBase_gen.hpp"
#include "Generated/ICondition_gen.hpp"
#include "Generated/Value_gen.hpp"

#include "Generated/Case_gen.hpp"
#include "Generated/TextString_gen.hpp"
#include "Generated/FormatedString_gen.hpp"
#include "Generated/ItemOrder_gen.hpp"
#include "Generated/ItemRecord_gen.hpp"

#include <fstream>
#include <iostream>

using namespace QuestCore;

JsonQuestFactory::JsonQuestFactory(const std::string& filename) :
    _isRed(false),
    _filename(filename)
{
    InitContainers();
}

IParagraph::Ptr JsonQuestFactory::GetParagraph(const std::string& rootKey)
{
    if (!Read()) {
        return nullptr;
    }

    return _paragraphs->Get(rootKey);
}

ICaseContainer::Ptr JsonQuestFactory::GetCaseContainer(const std::string& rootKey)
{
    if (!Read()) {
        return nullptr;
    }

    return _containers->Get(rootKey);
}

Inventory::Ptr JsonQuestFactory::GetInventory(const std::string& inventoryKey)
{
    if (!Read()) {
        return nullptr;
    }

    return _inventories->Get(inventoryKey);
}

void JsonQuestFactory::InitContainers()
{
    _items = std::make_shared<ItemContainer>("items");
    _paragraphs = std::make_shared<IParagraphContainer>("paragraphs");
    _containers = std::make_shared<ICaseContainerContainer>("containers");
    _inventories = std::make_shared<InventoryContainer>("inventories");
    _actions = std::make_shared<IActionContainer>("actions");

    _formBaseFactory = std::make_shared<FormBaseFactory>();
    _conditionFactory = std::make_shared<IConditionFactory>();
    _valueFactory = std::make_shared<ValueFactory>();

    _caseFactory = std::make_shared<CaseFactory>();
    _textFactory = std::make_shared<TextStringFactory>();
    _formatedTextFactory = std::make_shared<FormatedStringFactory>();
    _itemOrderFactory = std::make_shared<ItemOrderFactory>();
    _itemRecordFactory = std::make_shared<ItemRecordFactory>();

    InitItems();
    InitParagraphs();
    InitCaseContainers();
    InitInventories();
    InitActions();

    InitForms();
    InitConditions();
    InitValues();

    InitCases();
    InitTextStrings();
    InitFormatedStrings();
    InitItemOrders();
    InitItemRecords();
}

void JsonQuestFactory::InitItems()
{
    FactoryReader<FormatedString> formatedTextReader(_formatedTextFactory);
    PrimitiveReader<std::string> stringReader;
    PrimitiveReader<bool> boolReader;

    // Item

    PropertyReader<std::string, PrimitiveReader<std::string>>
        nameProperty("name", stringReader, std::string());

    PropertyReader<FormatedString, FactoryReader<FormatedString>>
        textProperty("text", formatedTextReader, FormatedString());

    PropertyReader<bool, PrimitiveReader<bool>>
        isNullableProperty("isNullable", boolReader, false);

    auto itemImpl = std::make_shared<ItemImpl>(ContainerInitializer<Item>(),
        nameProperty, textProperty, isNullableProperty);

    //Item

    auto itemContainer = std::dynamic_pointer_cast<ItemContainer>(_items);
    itemContainer->SetInheritors(
        ReaderImplRecord<ItemImpl>{ "Item", itemImpl }
    );
}

void JsonQuestFactory::InitParagraphs()
{
    ContainerReader<std::shared_ptr<IParagraph>> paragraphReader(_paragraphs);
    ContainerReader<std::shared_ptr<Inventory>> inventoryContainerReader(_inventories);
    FactoryReader<std::shared_ptr<ICondition>> conditionalReader(_conditionFactory);
    FactoryReader<TextString> textFactoryReader(_textFactory);
    FactoryReader<FormatedString> formatedTextReader(_formatedTextFactory);
    FactoryReader<ItemOrder> itemOrderReader(_itemOrderFactory);

    //ConditionalParagraph

    PropertyReader<std::shared_ptr<IParagraph>, ContainerReader<std::shared_ptr<IParagraph>>>
        thenParagraphReader("thenParagraph", paragraphReader, nullptr);

    PropertyReader<std::shared_ptr<IParagraph>, ContainerReader<std::shared_ptr<IParagraph>>>
        elseParagraphReader("elseParagraph", paragraphReader, nullptr);

    PropertyReader<std::vector<std::shared_ptr<ICondition>>, FactoryReader<std::shared_ptr<ICondition>>>
        conditionsReader("conditions", conditionalReader, std::vector<std::shared_ptr<ICondition>>());

    auto conditionalParagraphImpl = std::make_shared<ConditionalParagraphImpl>(
        ContainerInitializer<ConditionalParagraph>(),
        thenParagraphReader, elseParagraphReader, conditionsReader);

    //InventoryParagraph

    PropertyReader<FormatedString, FactoryReader<FormatedString>>
        prefixReader("prefix", formatedTextReader, FormatedString());

    PropertyReader<TextString, FactoryReader<TextString>>
        gapReader("gap", textFactoryReader, TextString());

    PropertyReader<FormatedString, FactoryReader<FormatedString>>
        postfixReader("postfix", formatedTextReader, FormatedString());

    PropertyReader<std::shared_ptr<Inventory>, ContainerReader<std::shared_ptr<Inventory>>>
        inventoryReader("inventory", inventoryContainerReader, nullptr);

    PropertyReader<std::vector<ItemOrder>, FactoryReader<ItemOrder>>
        itemOrdersReader("itemOrders", itemOrderReader, std::vector<ItemOrder>());

    auto inventoryParagraphImpl = std::make_shared<InventoryParagraphImpl>(
        ContainerInitializer<InventoryParagraph>(),
        prefixReader, gapReader, postfixReader, inventoryReader, itemOrdersReader);

    // ParagraphGroup

    PropertyReader<std::vector<std::shared_ptr<IParagraph>>, ContainerReader<std::shared_ptr<IParagraph>>>
        childrenReader("children", paragraphReader, std::vector<std::shared_ptr<IParagraph>>());

    auto paragraphGroupImpl = std::make_shared<ParagraphGroupImpl>(
        ContainerInitializer<ParagraphGroup>(),
        childrenReader, gapReader);

    // ParagraphStateMachine

    MethodInitializer<ParagraphStateMachine, std::shared_ptr<IParagraph>, ContainerReader<std::shared_ptr<IParagraph>>>
        stateInitializer("state", paragraphReader, nullptr,
            [](const std::shared_ptr<ParagraphStateMachine>& element, const std::shared_ptr<IParagraph>& arg) {
                element->SetState(arg);
            });

    ParagraphStateMachineInitializer paragraphStateMachineInitializer(stateInitializer);
    auto paragraphStateMachineImpl = std::make_shared<ParagraphStateMachineImpl>(
        paragraphStateMachineInitializer);

    // TextParagraph

    PropertyReader<TextString, FactoryReader<TextString>>
        textReader("text", textFactoryReader, TextString());

    auto textParagraphImpl = std::make_shared<TextParagraphImpl>(
        ContainerInitializer<TextParagraph>(),
        textReader);

    //IParagraph

    auto paragraphContainer = std::dynamic_pointer_cast<IParagraphContainer>(_paragraphs);
    paragraphContainer->SetInheritors(
        ReaderImplRecord<ConditionalParagraphImpl>{ "ConditionalParagraph", conditionalParagraphImpl },
        ReaderImplRecord<InventoryParagraphImpl>{ "InventoryParagraph", inventoryParagraphImpl },
        ReaderImplRecord<ParagraphGroupImpl>{ "ParagraphGroup", paragraphGroupImpl },
        ReaderImplRecord<ParagraphStateMachineImpl>{ "ParagraphStateMachine", paragraphStateMachineImpl },
        ReaderImplRecord<TextParagraphImpl>{ "TextParagraph", textParagraphImpl }
    );
}

void JsonQuestFactory::InitCaseContainers()
{
    ContainerReader<std::shared_ptr<ICaseContainer>> caseContainerReader(_containers);
    FactoryReader<std::shared_ptr<ICondition>> conditionalReader(_conditionFactory);
    FactoryReader<Case> caseReader(_caseFactory);

    // CaseContainerGroup

    PropertyReader<std::vector<std::shared_ptr<ICaseContainer>>, ContainerReader<std::shared_ptr<ICaseContainer>>>
        childrenReader("children", caseContainerReader, std::vector<std::shared_ptr<ICaseContainer>>());

    auto caseContainerGroupImpl = std::make_shared<CaseContainerGroupImpl>(
        ContainerInitializer<CaseContainerGroup>(),
        childrenReader);

    // CaseContainerStateMachine

    MethodInitializer<CaseContainerStateMachine, std::shared_ptr<ICaseContainer>, ContainerReader<std::shared_ptr<ICaseContainer>>>
        stateInitializer("state", caseContainerReader, nullptr,
            [](const std::shared_ptr<CaseContainerStateMachine>& element, const std::shared_ptr<ICaseContainer>& arg) {
                element->SetState(arg);
            });

    CaseContainerStateMachineInitializer caseContainerStateMachineInitializer(stateInitializer);
    auto caseContainerStateMachineImpl = std::make_shared<CaseContainerStateMachineImpl>(
        caseContainerStateMachineInitializer);

    //ConditionalCaseContainer

    PropertyReader<std::shared_ptr<ICaseContainer>, ContainerReader<std::shared_ptr<ICaseContainer>>>
        thenContainerReader("thenContainer", caseContainerReader, nullptr);

    PropertyReader<std::shared_ptr<ICaseContainer>, ContainerReader<std::shared_ptr<ICaseContainer>>>
        elseContainerReader("elseContainer", caseContainerReader, nullptr);

    PropertyReader<std::vector<std::shared_ptr<ICondition>>, FactoryReader<std::shared_ptr<ICondition>>>
        conditionsReader("conditions", conditionalReader, std::vector<std::shared_ptr<ICondition>>());

    auto conditionalCaseContainerImpl = std::make_shared<ConditionalCaseContainerImpl>(
        ContainerInitializer<ConditionalCaseContainer>(),
        thenContainerReader, elseContainerReader, conditionsReader);

    // SimpleCaseContainer

    PropertyReader<std::vector<Case>, FactoryReader<Case>>
        casesReader("cases", caseReader, std::vector<Case>());

    auto simpleCaseContainerImpl = std::make_shared<SimpleCaseContainerImpl>(
        ContainerInitializer<SimpleCaseContainer>(),
        casesReader);

    //ICaseContainer

    auto caseContainerContainer = std::dynamic_pointer_cast<ICaseContainerContainer>(_containers);
    caseContainerContainer->SetInheritors(
        ReaderImplRecord<CaseContainerGroupImpl>{ "CaseContainerGroup", caseContainerGroupImpl },
        ReaderImplRecord<CaseContainerStateMachineImpl>{ "CaseContainerStateMachine", caseContainerStateMachineImpl },
        ReaderImplRecord<ConditionalCaseContainerImpl>{ "ConditionalCaseContainer", conditionalCaseContainerImpl },
        ReaderImplRecord<SimpleCaseContainerImpl>{ "SimpleCaseContainer", simpleCaseContainerImpl }
    );
}

void JsonQuestFactory::InitInventories()
{
    FactoryReader<ItemRecord> itemRecordReader(_itemRecordFactory);

    // Inventory

    PropertyReader<std::vector<ItemRecord>, FactoryReader<ItemRecord>>
        itemsProperty("items", itemRecordReader, std::vector<ItemRecord>());

    auto inventoryImpl = std::make_shared<InventoryImpl>(
        ContainerInitializer<Inventory>(),
        itemsProperty);

    //Inventory

    auto inventoryContainer = std::dynamic_pointer_cast<InventoryContainer>(_inventories);
    inventoryContainer->SetInheritors(
        ReaderImplRecord<InventoryImpl>{ "Inventory", inventoryImpl }
    );
}

void JsonQuestFactory::InitActions()
{
    ContainerReader<std::shared_ptr<IParagraph>> paragraphReader(_paragraphs);
    ContainerReader<std::shared_ptr<IParagraph>, std::shared_ptr<ParagraphStateMachine>> paragraphStateMachineReader(_paragraphs);
    ContainerReader<std::shared_ptr<ICaseContainer>> containerReader(_containers);
    ContainerReader<std::shared_ptr<ICaseContainer>, std::shared_ptr<CaseContainerStateMachine>> containerStateMachineReader(_containers);
    ContainerReader<std::shared_ptr<Inventory>> inventoryReader(_inventories);

    FactoryReader<ItemRecord> itemRecordReader(_itemRecordFactory);

    //CaseContainerSwitching

    MethodInitializer<CaseContainerSwitching, std::shared_ptr<CaseContainerStateMachine>, ContainerReader<std::shared_ptr<ICaseContainer>, std::shared_ptr<CaseContainerStateMachine>>>
        caseContainerStateMachineInitializer("stateMachine", containerStateMachineReader, nullptr,
            [](const std::shared_ptr<CaseContainerSwitching>& element, const std::shared_ptr<CaseContainerStateMachine>& arg) {
                element->SetStateMachine(arg);
            });

    MethodInitializer<CaseContainerSwitching, std::shared_ptr<ICaseContainer>, ContainerReader<std::shared_ptr<ICaseContainer>>>
        caseContainerInitializer("nextContainer", containerReader, nullptr,
            [](const std::shared_ptr<CaseContainerSwitching>& element, const std::shared_ptr<ICaseContainer>& arg) {
                element->SetNextContainer(arg);
            });

    ContainerSwitchingInitializer containerSwitchingInitializer(caseContainerStateMachineInitializer, caseContainerInitializer);
    auto caseContainerSwitchingImpl = std::make_shared<CaseContainerSwitchingImpl>(containerSwitchingInitializer);

    //ParagraphSwitching

    MethodInitializer<ParagraphSwitching, std::shared_ptr<ParagraphStateMachine>, ContainerReader<std::shared_ptr<IParagraph>, std::shared_ptr<ParagraphStateMachine>>>
        paragraphStateMachineInitializer("stateMachine", paragraphStateMachineReader, nullptr,
            [](const std::shared_ptr<ParagraphSwitching>& element, const std::shared_ptr<ParagraphStateMachine>& arg) {
                element->SetStateMachine(arg);
            });

    MethodInitializer<ParagraphSwitching, std::shared_ptr<IParagraph>, ContainerReader<std::shared_ptr<IParagraph>>>
        paragraphInitializer("nextParagraph", paragraphReader, nullptr,
            [](const std::shared_ptr<ParagraphSwitching>& element, const std::shared_ptr<IParagraph>& arg) {
                element->SetNextParagraph(arg);
            });

    ParagraphSwitchingInitializer paragraphSwitchingInitializer(paragraphStateMachineInitializer, paragraphInitializer);
    auto paragraphSwitchingImpl = std::make_shared<ParagraphSwitchingImpl>(paragraphSwitchingInitializer);

    // Clearing

    PropertyReader<std::shared_ptr<Inventory>, ContainerReader<std::shared_ptr<Inventory>>>
        inventoryProperty("inventory", inventoryReader, nullptr);

    auto clearingImpl = std::make_shared<ClearingImpl>(ContainerInitializer<Clearing>(), inventoryProperty);

    // Copying

    PropertyReader<std::shared_ptr<Inventory>, ContainerReader<std::shared_ptr<Inventory>>>
        inventorySourceProperty("source", inventoryReader, nullptr);

    PropertyReader<std::shared_ptr<Inventory>, ContainerReader<std::shared_ptr<Inventory>>>
        inventoryTargetProperty("target", inventoryReader, nullptr);

    auto copyingImpl = std::make_shared<CopyingImpl>(ContainerInitializer<Copying>(),
        inventorySourceProperty, inventoryTargetProperty);

    // Transfer

    PropertyReader<std::vector<ItemRecord>, FactoryReader<ItemRecord>>
        itemsProperty("items", itemRecordReader, std::vector<ItemRecord>());

    auto transferImpl = std::make_shared<TransferImpl>(ContainerInitializer<Transfer>(),
        inventorySourceProperty, inventoryTargetProperty, itemsProperty);


    //IAction
    auto actionContainer = std::dynamic_pointer_cast<IActionContainer>(_actions);
    actionContainer->SetInheritors(
        ReaderImplRecord<CaseContainerSwitchingImpl>{ "CaseContainerSwitching", caseContainerSwitchingImpl },
        ReaderImplRecord<ParagraphSwitchingImpl>{ "ParagraphSwitching", paragraphSwitchingImpl },
        ReaderImplRecord<ClearingImpl>{ "Clearing", clearingImpl },
        ReaderImplRecord<CopyingImpl>{ "Copying", copyingImpl },
        ReaderImplRecord<TransferImpl>{ "Transfer", transferImpl }
    );
}

void JsonQuestFactory::InitForms()
{
    FactoryReader<TextString> textFactoryReader(_textFactory);
    PrimitiveReader<int> intReader;

    // FormBase

    PropertyReader<TextString, FactoryReader<TextString>>
        textProperty("text", textFactoryReader, TextString());

    auto formBaseImpl = std::make_shared<FormBaseImpl>(textProperty);

    // SpecificForm

    PropertyReader<std::vector<int>, PrimitiveReader<int>>
        countsProperty("counts", intReader, std::vector<int>());

    auto specificFormImpl = std::make_shared<SpecificFormImpl>(countsProperty, textProperty);

    // TailForm

    PropertyReader<int, PrimitiveReader<int>>
        notationProperty("notation", intReader, 0);

    PropertyReader<std::vector<int>, PrimitiveReader<int>>
        digitsProperty("digits", intReader, std::vector<int>());

    auto tailFormImpl = std::make_shared<TailFormImpl>(notationProperty, digitsProperty, textProperty);

    //FormBase

    auto formBaseFactory = std::dynamic_pointer_cast<FormBaseFactory>(_formBaseFactory);
    formBaseFactory->SetInheritors(
        ReaderImplRecord<FormBaseImpl>{ "FormBase", formBaseImpl },
        ReaderImplRecord<SpecificFormImpl>{ "SpecificForm", specificFormImpl },
        ReaderImplRecord<TailFormImpl>{ "TailForm", tailFormImpl }
    );
}

void JsonQuestFactory::InitConditions()
{
    FactoryReader<std::shared_ptr<Value>> valueReader(_valueFactory);

    EnumReader<Operation> operationEnumReader(std::map<std::string, Operation>{
        { "None", Operation::None },
        { "Less", Operation::Less },
        { "Greater", Operation::Greater },
        { "Equal", Operation::Equal },
        { "NotLess", Operation::NotLess },
        { "NotGreater", Operation::NotGreater },
        { "NotEqual", Operation::NotEqual }
    });

    // Comparison

    PropertyReader<std::shared_ptr<Value>, FactoryReader<std::shared_ptr<Value>>>
        leftProperty("left", valueReader, nullptr);

    PropertyReader<std::shared_ptr<Value>, FactoryReader<std::shared_ptr<Value>>>
        rightProperty("right", valueReader, nullptr);

    PropertyReader<Operation, EnumReader<Operation>>
        operationReader("op", operationEnumReader, Operation::None);

    auto comparisonImpl = std::make_shared<ComparisonImpl>(leftProperty, rightProperty, operationReader);

    //ICondition

    auto conditionFactory = std::dynamic_pointer_cast<IConditionFactory>(_conditionFactory);
    conditionFactory->SetInheritors(
        ReaderImplRecord<ComparisonImpl>{ "Comparison", comparisonImpl }
    );
}

void JsonQuestFactory::InitValues()
{
    PrimitiveReader<int> intReader;
    ContainerReader<std::shared_ptr<Item>> itemContainerReader(_items);
    ContainerReader<std::shared_ptr<Inventory>> inventoryContainerReader(_inventories);

    //SimpleValue

    PropertyReader<int, PrimitiveReader<int>>
        valueReader("value", intReader, 0);

    auto simpleValueImpl = std::make_shared<SimpleValueImpl>(valueReader);

    //InventoryValue

    PropertyReader<std::shared_ptr<Item>, ContainerReader<std::shared_ptr<Item>>>
        itemReader("item", itemContainerReader, nullptr);

    PropertyReader<std::shared_ptr<Inventory>, ContainerReader<std::shared_ptr<Inventory>>>
        inventoryReader("inventory", inventoryContainerReader, nullptr);

    auto inventoryValueImpl = std::make_shared<InventoryValueImpl>(itemReader, inventoryReader);

    //Value

    auto valueFactory = std::dynamic_pointer_cast<ValueFactory>(_valueFactory);
    valueFactory->SetInheritors(
        ReaderImplRecord<SimpleValueImpl>{ "SimpleValue", simpleValueImpl },
        ReaderImplRecord<InventoryValueImpl>{ "InventoryValue", inventoryValueImpl }
    );
}

void JsonQuestFactory::InitCases()
{
    FactoryReader<TextString> textFactoryReader(_textFactory);
    ContainerReader<std::shared_ptr<IAction>> actionReader(_actions);

    // Case

    PropertyReader<TextString, FactoryReader<TextString>>
        nameProperty("name", textFactoryReader, TextString());

    PropertyReader<std::vector<std::shared_ptr<IAction>>, ContainerReader<std::shared_ptr<IAction>>>
        actionsProperty("actions", actionReader, std::vector<std::shared_ptr<IAction>>());

    auto caseImpl = std::make_shared<CaseImpl>(nameProperty, actionsProperty);

    //Case
    auto caseFactory = std::dynamic_pointer_cast<CaseFactory>(_caseFactory);
    caseFactory->SetInheritors(
        ReaderImplRecord<CaseImpl>{ "Case", caseImpl }
    );
}

void JsonQuestFactory::InitTextStrings()
{
    PrimitiveReader<std::string> stringReader;

    // TextString

    PropertyReader<std::string, PrimitiveReader<std::string>>
        u8Property("u8", stringReader, std::string());

    auto textStringImpl = std::make_shared<TextStringImpl>(u8Property);

    //TextString
    auto textStringFactory = std::dynamic_pointer_cast<TextStringFactory>(_textFactory);
    textStringFactory->SetInheritors(
        ReaderImplRecord<TextStringImpl>{ "TextString", textStringImpl }
    );
}

void JsonQuestFactory::InitFormatedStrings()
{
    FactoryReader<std::shared_ptr<FormBase>> formBaseReader(_formBaseFactory);

    // FormatedString

    PropertyReader<std::vector<std::shared_ptr<FormBase>>, FactoryReader<std::shared_ptr<FormBase>>>
        formsProperty("forms", formBaseReader, std::vector<std::shared_ptr<FormBase>>());

    auto formatedStringImpl = std::make_shared<FormatedStringImpl>(formsProperty);

    //FormatedString
    auto formatedStringFactory = std::dynamic_pointer_cast<FormatedStringFactory>(_formatedTextFactory);
    formatedStringFactory->SetInheritors(
        ReaderImplRecord<FormatedStringImpl>{ "FormatedString", formatedStringImpl }
    );
}

void JsonQuestFactory::InitItemOrders()
{
    ContainerReader<std::shared_ptr<Item>> itemReader(_items);
    PrimitiveReader<int> intReader;

    // ItemOrder

    PropertyReader<std::shared_ptr<Item>, ContainerReader<std::shared_ptr<Item>>>
        itemProperty("item", itemReader, nullptr);

    PropertyReader<int, PrimitiveReader<int>>
        orderProperty("order", intReader, 0);

    auto itemOrderImpl = std::make_shared<ItemOrderImpl>(itemProperty, orderProperty);

    //ItemOrder
    auto itemOrderFactory = std::dynamic_pointer_cast<ItemOrderFactory>(_itemOrderFactory);
    itemOrderFactory->SetInheritors(
        ReaderImplRecord<ItemOrderImpl>{ "ItemOrder", itemOrderImpl }
    );
}

void JsonQuestFactory::InitItemRecords()
{
    ContainerReader<std::shared_ptr<Item>> itemReader(_items);
    PrimitiveReader<int> intReader;

    // ItemRecord

    PropertyReader<std::shared_ptr<Item>, ContainerReader<std::shared_ptr<Item>>>
        itemProperty("item", itemReader, nullptr);

    PropertyReader<int, PrimitiveReader<int>>
        countProperty("count", intReader, 0);

    auto itemRecordImpl = std::make_shared<ItemRecordImpl>(itemProperty, countProperty);

    //ItemRecord
    auto itemRecordFactory = std::dynamic_pointer_cast<ItemRecordFactory>(_itemRecordFactory);
    itemRecordFactory->SetInheritors(
        ReaderImplRecord<ItemRecordImpl>{ "ItemRecord", itemRecordImpl }
    );
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

    _items->AddRoot(root);
    _inventories->AddRoot(root);
    _paragraphs->AddRoot(root);
    _containers->AddRoot(root);
    _actions->AddRoot(root);

    _items->CreateAll();
    _inventories->CreateAll();
    _actions->CreateAll();
    _paragraphs->CreateAll();
    _containers->CreateAll();

    _items->InitAll();
    _inventories->InitAll();
    _actions->InitAll();
    _paragraphs->InitAll();
    _containers->InitAll();

    _isRed = true;
    return true;
}
