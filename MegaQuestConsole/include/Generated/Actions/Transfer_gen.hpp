#pragma once
#include "Actions/Transfer.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/PropertyReader.hpp"

using TransferImpl = ContainerImpl<QuestCore::Transfer,
    ContainerInitializer<QuestCore::Transfer>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>,
    PropertyReader<std::vector<QuestCore::ItemRecord>, FactoryReader>
>;

class TransferImpl_Binder
{
public:
    TransferImpl_Binder();

private:
    static TransferImpl_Binder instance;
};
