#pragma once
#include "Actions/Transfer.hpp"

#include "Inventory.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/PropertyReader.hpp"

using TransferImpl = ContainerImpl<QuestCore::Transfer,
    ContainerInitializer<QuestCore::Transfer>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>,
    PropertyReader<std::vector<QuestCore::ItemRecord>, FactoryReader<QuestCore::ItemRecord>>
>;

class TransferImpl_Binder
{
public:
    TransferImpl_Binder();

private:
    static TransferImpl_Binder instance;
};
