#include "Generated/Inventory_gen.hpp"

//ItemRecord

ItemRecordImpl_Binder ItemRecordImpl_Binder::instance;

ItemRecordImpl_Binder::ItemRecordImpl_Binder()
{
    auto itemContainer = GlobalContext::GetContainer<QuestCore::Item>();
    ContainerReader<std::shared_ptr<QuestCore::Item>> itemReader(itemContainer);

    PrimitiveReader<int> intReader;

    PropertyReader<std::shared_ptr<QuestCore::Item>, ContainerReader>
        itemProperty("item", itemReader, nullptr);

    PropertyReader<int, PrimitiveReader>
        countProperty("count", intReader, 0);

    auto itemRecordImpl = std::make_shared<ItemRecordImpl>(itemProperty, countProperty);

    if (auto itemRecordFactory = std::dynamic_pointer_cast<ItemRecordFactory>(GlobalContext::GetFactory<QuestCore::ItemRecord>())) {
        itemRecordFactory->SetInheritor<ItemRecordImpl>(
            ReaderImplRecord<ItemRecordImpl>{ "ItemRecord", itemRecordImpl });
    }
}

template<>
const std::shared_ptr<IFactory<QuestCore::ItemRecord>>& GlobalContext::GetFactory<QuestCore::ItemRecord>()
{
    static std::shared_ptr<IFactory<QuestCore::ItemRecord>>
        instancePtr = std::make_shared<ItemRecordFactory>();
    return instancePtr;
}


//Inventory

InventoryImpl_Binder InventoryImpl_Binder::instance;

InventoryImpl_Binder::InventoryImpl_Binder()
{
    auto itemRecordFactory = GlobalContext::GetFactory<QuestCore::ItemRecord>();
    FactoryReader<QuestCore::ItemRecord> itemRecordReader(itemRecordFactory);

    PropertyReader<std::vector<QuestCore::ItemRecord>, FactoryReader>
        itemsProperty("items", itemRecordReader, std::vector<QuestCore::ItemRecord>());

    auto inventoryImpl = std::make_shared<InventoryImpl>(
        ContainerInitializer<QuestCore::Inventory>(),
        itemsProperty);

    if (auto inventoryContainer = std::dynamic_pointer_cast<InventoryContainer>(GlobalContext::GetContainer<QuestCore::Inventory>())) {
        inventoryContainer->SetInheritor<InventoryImpl>(
            ReaderImplRecord<InventoryImpl>{ "Inventory", inventoryImpl });
    }
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::Inventory>>& GlobalContext::GetContainer<QuestCore::Inventory>()
{
    static std::shared_ptr<ContainerBase<QuestCore::Inventory>>
        instancePtr = std::make_shared<InventoryContainer>("inventories");
    return instancePtr;
}
