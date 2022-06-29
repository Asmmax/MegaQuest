#pragma once
#include "Actions/Copying.hpp"

#include "Inventory.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/PropertyReader.hpp"

using CopyingImpl = ContainerImpl<QuestCore::Copying,
    ContainerInitializer<QuestCore::Copying>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>
>;

class CopyingImpl_Binder
{
public:
    CopyingImpl_Binder();

private:
    static CopyingImpl_Binder instance;
};
