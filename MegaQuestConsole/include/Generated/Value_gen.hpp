#pragma once

#include "Value.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"
#include "Containers/Factory.hpp"

//SimpleValue

using SimpleValueImpl = FactoryImpl<std::shared_ptr<QuestCore::SimpleValue>,
    PropertyReader<int, PrimitiveReader>
>;

//InventoryValue

using InventoryValueImpl = FactoryImpl<std::shared_ptr<QuestCore::InventoryValue>,
    PropertyReader<std::shared_ptr<QuestCore::Item>, ContainerReader>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader>
>;

//Factories

using ValueFactory = Factory<std::shared_ptr<QuestCore::Value>, SimpleValueImpl, InventoryValueImpl>;
