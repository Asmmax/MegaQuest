#include "Generated/Value_gen.hpp"

//SimpleValue

SimpleValueImpl_Binder SimpleValueImpl_Binder::instance;

SimpleValueImpl_Binder::SimpleValueImpl_Binder()
{
    PrimitiveReader<int> intReader;

    PropertyReader<int, PrimitiveReader<int>>
        valueReader("value", intReader, 0);

    auto simpleValueImpl = std::make_shared<SimpleValueImpl>(valueReader);

    if (auto valueFactory = std::dynamic_pointer_cast<ValueFactory>(GlobalContext::GetFactory<std::shared_ptr<QuestCore::Value>>())) {
        valueFactory->SetInheritor<SimpleValueImpl>(
            ReaderImplRecord<SimpleValueImpl>{ "SimpleValue", simpleValueImpl });
    }
}

//InventoryValue

InventoryValueImpl_Binder InventoryValueImpl_Binder::instance;

InventoryValueImpl_Binder::InventoryValueImpl_Binder()
{
    auto itemContainer = GlobalContext::GetContainer<QuestCore::Item>();
    ContainerReader<std::shared_ptr<QuestCore::Item>> itemContainerReader(itemContainer);

    auto inventoryContainer = GlobalContext::GetContainer<QuestCore::Inventory>();
    ContainerReader<std::shared_ptr<QuestCore::Inventory>> inventoryContainerReader(inventoryContainer);

    PropertyReader<std::shared_ptr<QuestCore::Item>, ContainerReader<std::shared_ptr<QuestCore::Item>>>
        itemReader("item", itemContainerReader, nullptr);

    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>
        inventoryReader("inventory", inventoryContainerReader, nullptr);

    auto inventoryValueImpl = std::make_shared<InventoryValueImpl>(itemReader, inventoryReader);

    if (auto valueFactory = std::dynamic_pointer_cast<ValueFactory>(GlobalContext::GetFactory<std::shared_ptr<QuestCore::Value>>())) {
        valueFactory->SetInheritor<InventoryValueImpl>(
            ReaderImplRecord<InventoryValueImpl>{ "InventoryValue", inventoryValueImpl });
    }
}

//Value

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Value>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::Value>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Value>>>
        instancePtr = std::make_shared<ValueFactory>();
    return instancePtr;
}
