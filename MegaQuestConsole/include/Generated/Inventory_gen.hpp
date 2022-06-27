#pragma once

#include "Inventory.hpp"

#include "Containers/ContainerImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Container.hpp"
#include "Containers/ContainerInitializer.hpp"

//Inventory

using InventoryImpl = ContainerImpl<QuestCore::Inventory,
    ContainerInitializer<QuestCore::Inventory>,
    PropertyReader<std::vector<QuestCore::ItemRecord>, FactoryReader<QuestCore::ItemRecord>>
>;

//Containers

using InventoryContainer = Container<QuestCore::Inventory, InventoryImpl>;
