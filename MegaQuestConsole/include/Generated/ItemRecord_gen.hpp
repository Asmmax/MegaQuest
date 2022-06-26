#pragma once

#include "Inventory.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/Factory.hpp"

namespace QuestCore
{
    class Item;
}

//ItemRecord

using ItemRecordImpl = FactoryImpl<QuestCore::ItemRecord,
    PropertyReader<std::shared_ptr<QuestCore::Item>, ContainerReader>,
    PropertyReader<int, PrimitiveReader>
>;

//Factories

using ItemRecordFactory = Factory<QuestCore::ItemRecord, ItemRecordImpl>;
