#pragma once

#include "Inventory.hpp"

#include "Containers/ContainerImpl.hpp"
#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/ContainerInitializer.hpp"

#include "Containers/Container.hpp"
#include "Containers/Factory.hpp"
#include "Containers/GlobalContext.hpp"

//ItemRecord

using ItemRecordImpl = FactoryImpl<QuestCore::ItemRecord,
    PropertyReader<std::shared_ptr<QuestCore::Item>, ContainerReader>,
    PropertyReader<int, PrimitiveReader>
>;

class ItemRecordImpl_Binder
{
public:
    ItemRecordImpl_Binder();

private:
    static ItemRecordImpl_Binder instance;
};

using ItemRecordFactory = Factory<QuestCore::ItemRecord, ItemRecordImpl>;

template<>
const std::shared_ptr<IFactory<QuestCore::ItemRecord>>& GlobalContext::GetFactory<QuestCore::ItemRecord>();

//Inventory

using InventoryImpl = ContainerImpl<QuestCore::Inventory,
    ContainerInitializer<QuestCore::Inventory>,
    PropertyReader<std::vector<QuestCore::ItemRecord>, FactoryReader>
>;

class InventoryImpl_Binder
{
public:
    InventoryImpl_Binder();

private:
    static InventoryImpl_Binder instance;
};

using InventoryContainer = Container<QuestCore::Inventory, InventoryImpl>;

template<>
const std::shared_ptr<ContainerBase<QuestCore::Inventory>>& GlobalContext::GetContainer<QuestCore::Inventory>();
