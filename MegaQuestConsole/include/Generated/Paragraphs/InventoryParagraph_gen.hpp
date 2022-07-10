#pragma once
#include "Paragraphs/InventoryParagraph.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/FactoryImpl.hpp"

#include "Containers/Factory.hpp"
#include "Containers/Container.hpp"
#include "Containers/FactoryBinder.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

//ItemOrder

using ItemOrderImpl = FactoryImpl<QuestCore::ItemOrder,
    std::shared_ptr<QuestCore::Item>,
    int
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
template<>
void FactoryBinder<QuestCore::ItemOrder>::BindImpl(const std::string& implName, const std::shared_ptr<ItemOrderImpl>& impl);

template<>
const std::shared_ptr<IFactory<QuestCore::ItemOrder>>& GlobalContext::GetFactory<QuestCore::ItemOrder>();

template <>
std::shared_ptr<IReaderStrategy<QuestCore::ItemOrder>> GetReader();

//InventoryParagraph

using InventoryParagraphInitializer = ContainerInitializer<QuestCore::InventoryParagraph>;

using InventoryParagraphImpl = ContainerImpl<QuestCore::InventoryParagraph,
    InventoryParagraphInitializer,
    QuestCore::FormatedString, 
    QuestCore::TextString, 
    QuestCore::FormatedString,
    std::shared_ptr<QuestCore::Inventory>,
    std::vector<QuestCore::ItemOrder>
>;

class InventoryParagraphImpl_Binder
{
public:
    InventoryParagraphImpl_Binder();

private:
    static InventoryParagraphImpl_Binder instance;
};

using InventoryParagraphContainer = Container<QuestCore::InventoryParagraph, InventoryParagraphImpl>;

template<>
template<>
void ContainerBinder<QuestCore::InventoryParagraph>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryParagraphImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::InventoryParagraph>>& GlobalContext::GetContainer<QuestCore::InventoryParagraph>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::InventoryParagraph>>> GetReader();
