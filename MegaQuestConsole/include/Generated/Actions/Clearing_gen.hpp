#pragma once
#include "Actions/Clearing.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/PropertyReader.hpp"

using ClearingImpl = ContainerImpl<QuestCore::Clearing,
    ContainerInitializer<QuestCore::Clearing>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>
>;

class ClearingImpl_Binder
{
public:
    ClearingImpl_Binder();

private:
    static ClearingImpl_Binder instance;
};
