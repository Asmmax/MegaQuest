#pragma once

#include "Item.hpp"

#include "Containers/ContainerImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Container.hpp"
#include "Containers/ContainerInitializer.hpp"

namespace QuestCore
{
    class FormatedString;
}

//Item

using ItemImpl = ContainerImpl<QuestCore::Item,
    ContainerInitializer<QuestCore::Item>,
    PropertyReader<std::string, PrimitiveReader<std::string>>,
    PropertyReader<QuestCore::FormatedString, FactoryReader<QuestCore::FormatedString>>,
    PropertyReader<bool, PrimitiveReader<bool>>
>;

//Containers

using ItemContainer = Container<QuestCore::Item, ItemImpl>;
