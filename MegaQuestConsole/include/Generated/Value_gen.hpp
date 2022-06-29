#pragma once

#include "Value.hpp"

#include "Item.hpp"
#include "Inventory.hpp"

#include "Containers/FactoryImpl.hpp"
#include "Containers/PropertyReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ReaderStrategy/PrimitiveReader.hpp"

#include "Containers/Factory.hpp"
#include "Containers/GlobalContext.hpp"

//SimpleValue

using SimpleValueImpl = FactoryImpl<std::shared_ptr<QuestCore::SimpleValue>,
    PropertyReader<int, PrimitiveReader<int>>
>;

class SimpleValueImpl_Binder
{
public:
    SimpleValueImpl_Binder();

private:
    static SimpleValueImpl_Binder instance;
};

//InventoryValue

using InventoryValueImpl = FactoryImpl<std::shared_ptr<QuestCore::InventoryValue>,
    PropertyReader<std::shared_ptr<QuestCore::Item>, ContainerReader<std::shared_ptr<QuestCore::Item>>>,
    PropertyReader<std::shared_ptr<QuestCore::Inventory>, ContainerReader<std::shared_ptr<QuestCore::Inventory>>>
>;

class InventoryValueImpl_Binder
{
public:
    InventoryValueImpl_Binder();

private:
    static InventoryValueImpl_Binder instance;
};

//Value

using ValueFactory = Factory<std::shared_ptr<QuestCore::Value>, SimpleValueImpl, InventoryValueImpl>;

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Value>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::Value>>();
