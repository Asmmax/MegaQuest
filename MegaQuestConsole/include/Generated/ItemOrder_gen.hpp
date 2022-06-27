#pragma once

#include "Paragraphs/InventoryParagraph.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/Factory.hpp"

namespace QuestCore
{
    class Item;
}

//ItemOrder

using ItemOrderImpl = FactoryImpl<QuestCore::ItemOrder,
    PropertyReader<std::shared_ptr<QuestCore::Item>, ContainerReader<std::shared_ptr<QuestCore::Item>>>,
    PropertyReader<int, PrimitiveReader<int>>
>;

//Factories

using ItemOrderFactory = Factory<QuestCore::ItemOrder, ItemOrderImpl>;
