#include "Generated/Value_gen.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"

//SimpleValue

SimpleValueImpl_Binder SimpleValueImpl_Binder::instance;

SimpleValueImpl_Binder::SimpleValueImpl_Binder()
{
    auto impl = std::make_shared<SimpleValueImpl>(
        CreateProperty<int>("value", 0)
        );

    FactoryBinder<std::shared_ptr<QuestCore::SimpleValue>>().BindImpl("SimpleValue", impl);
    FactoryBinder<std::shared_ptr<QuestCore::Value>>().BindImpl("SimpleValue", impl);
}

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::SimpleValue>>::BindImpl(const std::string& implName, const std::shared_ptr<SimpleValueImpl>& impl)
{
    BindImplWithCast<SimpleValueFactory, SimpleValueImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::SimpleValue>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::SimpleValue>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::SimpleValue>>>
        instancePtr = std::make_shared<SimpleValueFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::SimpleValue>>> GetReader()
{
    auto factory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::SimpleValue>>();
    return std::make_shared<FactoryReader<std::shared_ptr<QuestCore::SimpleValue>>>(factory);
}

//InventoryValue

InventoryValueImpl_Binder InventoryValueImpl_Binder::instance;

InventoryValueImpl_Binder::InventoryValueImpl_Binder()
{
    auto impl = std::make_shared<InventoryValueImpl>(
        CreateProperty<std::shared_ptr<QuestCore::Item>>("item", nullptr)
        , CreateProperty<std::shared_ptr<QuestCore::Inventory>>("inventory", nullptr)
        );

    FactoryBinder<std::shared_ptr<QuestCore::InventoryValue>>().BindImpl("InventoryValue", impl);
    FactoryBinder<std::shared_ptr<QuestCore::Value>>().BindImpl("InventoryValue", impl);
}

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::InventoryValue>>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryValueImpl>& impl)
{
    BindImplWithCast<InventoryValueFactory, InventoryValueImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::InventoryValue>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::InventoryValue>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::InventoryValue>>>
        instancePtr = std::make_shared<InventoryValueFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::InventoryValue>>> GetReader()
{
    auto factory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::InventoryValue>>();
    return std::make_shared<FactoryReader<std::shared_ptr<QuestCore::InventoryValue>>>(factory);
}

//Value

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::Value>>::BindImpl(const std::string& implName, const std::shared_ptr<SimpleValueImpl>& impl)
{
    BindImplWithCast<ValueFactory, SimpleValueImpl>(implName, impl);
}

template<>
template<>
void FactoryBinder<std::shared_ptr<QuestCore::Value>>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryValueImpl>& impl)
{
    BindImplWithCast<ValueFactory, InventoryValueImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Value>>>& GlobalContext::GetFactory<std::shared_ptr<QuestCore::Value>>()
{
    static std::shared_ptr<IFactory<std::shared_ptr<QuestCore::Value>>>
        instancePtr = std::make_shared<ValueFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Value>>> GetReader()
{
    auto factory = GlobalContext::GetFactory<std::shared_ptr<QuestCore::Value>>();
    return std::make_shared<FactoryReader<std::shared_ptr<QuestCore::Value>>>(factory);
}
