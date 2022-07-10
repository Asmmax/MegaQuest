#pragma once

#include "Inventory.hpp"

#include "Containers/ContainerImpl.hpp"
#include "Containers/FactoryImpl.hpp"
#include "Containers/ContainerInitializer.hpp"

#include "Containers/Container.hpp"
#include "Containers/Factory.hpp"
#include "Containers/ContainerBinder.hpp"
#include "Containers/FactoryBinder.hpp"

#include "Containers/Utils.hpp"

//ItemRecord

using ItemRecordImpl = FactoryImpl<QuestCore::ItemRecord,
    std::shared_ptr<QuestCore::Item>,
    int
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
template<>
void FactoryBinder<QuestCore::ItemRecord>::BindImpl(const std::string& implName, const std::shared_ptr<ItemRecordImpl>& impl);

template<>
const std::shared_ptr<IFactory<QuestCore::ItemRecord>>& GlobalContext::GetFactory<QuestCore::ItemRecord>();

template <>
std::shared_ptr<IReaderStrategy<QuestCore::ItemRecord>> GetReader();

//Inventory

using InventoryInitializer = ContainerInitializer<QuestCore::Inventory>;

using InventoryImpl = ContainerImpl<QuestCore::Inventory,
    InventoryInitializer,
    std::vector<QuestCore::ItemRecord>
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
template<>
void ContainerBinder<QuestCore::Inventory>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::Inventory>>& GlobalContext::GetContainer<QuestCore::Inventory>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Inventory>>> GetReader();
