#pragma once

#include "Item.hpp"

#include "Containers/ContainerImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/ContainerInitializer.hpp"

#include "Containers/Container.hpp"
#include "Containers/GlobalContext.hpp"

//Item

using ItemImpl = ContainerImpl<QuestCore::Item,
    ContainerInitializer<QuestCore::Item>,
    PropertyReader<std::string, PrimitiveReader<std::string>>,
    PropertyReader<QuestCore::FormatedString, FactoryReader<QuestCore::FormatedString>>,
    PropertyReader<bool, PrimitiveReader<bool>>
>;

class ItemImpl_Binder
{
public:
    ItemImpl_Binder();

private:
    static ItemImpl_Binder instance;
};

using ItemContainer = Container<QuestCore::Item, ItemImpl>;

template<>
const std::shared_ptr<ContainerBase<QuestCore::Item>>& GlobalContext::GetContainer<QuestCore::Item>();
