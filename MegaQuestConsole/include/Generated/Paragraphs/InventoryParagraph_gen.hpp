#pragma once
#include "Paragraphs/InventoryParagraph.hpp"

#include "Item.hpp"
#include "Inventory.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/FactoryImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"

#include "Containers/Factory.hpp"
#include "Containers/GlobalContext.hpp"

//ItemOrder

using ItemOrderImpl = FactoryImpl<QuestCore::ItemOrder,
    PropertyReader<std::shared_ptr<QuestCore::Item>, ContainerReader<std::shared_ptr<QuestCore::Item>>>,
    PropertyReader<int, PrimitiveReader<int>>
>;

class ItemOrderImpl_Binder
{
public:
    ItemOrderImpl_Binder();

private:
    static ItemOrderImpl_Binder instance;
};

using ItemOrderFactory = Factory<QuestCore::ItemOrder, ItemOrderImpl>;

template<>
const std::shared_ptr<IFactory<QuestCore::ItemOrder>>& GlobalContext::GetFactory<QuestCore::ItemOrder>();

//InventoryParagraph

using InventoryParagraphImpl = ContainerImpl<QuestCore::InventoryParagraph,
    ContainerInitializer<QuestCore::InventoryParagraph>,
    PropertyReader<QuestCore::FormatedString, FactoryReader<QuestCore::FormatedString>>,
    PropertyReader<QuestCore::TextString, FactoryReader<QuestCore::TextString>>,
    PropertyReader<QuestCore::FormatedString, FactoryReader<QuestCore::FormatedString>>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>,
    PropertyReader<std::vector<QuestCore::ItemOrder>, FactoryReader<QuestCore::ItemOrder>>
>;

class InventoryParagraphImpl_Binder
{
public:
    InventoryParagraphImpl_Binder();

private:
    static InventoryParagraphImpl_Binder instance;
};
