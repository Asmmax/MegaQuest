#pragma once

#include "Value.hpp"

#include "Containers/FactoryImpl.hpp"

#include "Containers/Factory.hpp"
#include "Containers/FactoryBinder.hpp"

#include "Containers/Utils.hpp"

//SimpleValue

using SimpleValueImpl = FactoryImpl<std::shared_ptr<QuestCore::SimpleValue>,
    int
>;

class SimpleValueImpl_Binder
{
public:
    SimpleValueImpl_Binder();

private:
    static SimpleValueImpl_Binder instance;
};

using SimpleValueFactory = Factory<std::shared_ptr<QuestCore::SimpleValue>, SimpleValueImpl>;

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::SimpleValue>>::BindImpl(const std::string& implName, const std::shared_ptr<SimpleValueImpl>& impl);

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::SimpleValue>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::SimpleValue>>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::SimpleValue>>> GetReader();

//InventoryValue

using InventoryValueImpl = FactoryImpl<std::shared_ptr<QuestCore::InventoryValue>,
    std::shared_ptr<QuestCore::Item>,
    std::shared_ptr<QuestCore::Inventory>
>;

class InventoryValueImpl_Binder
{
public:
    InventoryValueImpl_Binder();

private:
    static InventoryValueImpl_Binder instance;
};

using InventoryValueFactory = Factory<std::shared_ptr<QuestCore::InventoryValue>, InventoryValueImpl>;

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::InventoryValue>>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryValueImpl>& impl);

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::InventoryValue>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::InventoryValue>>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::InventoryValue>>> GetReader();

//Value

using ValueFactory = Factory<std::shared_ptr<QuestCore::Value>, SimpleValueImpl, InventoryValueImpl>;

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::Value>>::BindImpl(const std::string& implName, const std::shared_ptr<SimpleValueImpl>& impl);

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::Value>>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryValueImpl>& impl);

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Value>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::Value>>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Value>>> GetReader();
