#include "Generated/Inventory_gen.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

//ItemRecord

ItemRecordImpl_Binder ItemRecordImpl_Binder::instance;

ItemRecordImpl_Binder::ItemRecordImpl_Binder()
{
    auto impl = std::make_shared<ItemRecordImpl>(
        CreateProperty<std::shared_ptr<QuestCore::Item>>("item", nullptr)
        , CreateProperty<int>("count", 0)
        );

    FactoryBinder<QuestCore::ItemRecord>().BindImpl("ItemRecord", impl);
}

template<>
template<>
void FactoryBinder<QuestCore::ItemRecord>::BindImpl(const std::string& implName, const std::shared_ptr<ItemRecordImpl>& impl)
{
    BindImplWithCast<ItemRecordFactory, ItemRecordImpl>(implName, impl);
}

template<>
const std::shared_ptr<IFactory<QuestCore::ItemRecord>>& GlobalContext::GetFactory<QuestCore::ItemRecord>()
{
    static std::shared_ptr<IFactory<QuestCore::ItemRecord>>
        instancePtr = std::make_shared<ItemRecordFactory>();
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<QuestCore::ItemRecord>> GetReader()
{
    auto factory = GlobalContext::GetFactory<QuestCore::ItemRecord>();
    return std::make_shared<FactoryReader<QuestCore::ItemRecord>>(factory);
}


//Inventory

InventoryImpl_Binder InventoryImpl_Binder::instance;

InventoryImpl_Binder::InventoryImpl_Binder()
{
    auto impl = std::make_shared<InventoryImpl>(
        InventoryInitializer(
        )
        , CreateProperty<std::vector<QuestCore::ItemRecord>>("items", std::vector<QuestCore::ItemRecord>())
        );

    ContainerBinder<QuestCore::Inventory>().BindImpl("Inventory", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::Inventory>::BindImpl(const std::string& implName, const std::shared_ptr<InventoryImpl>& impl)
{
    BindImplWithCast<InventoryContainer, InventoryImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::Inventory>>& GlobalContext::GetContainer<QuestCore::Inventory>()
{
    static std::shared_ptr<ContainerBase<QuestCore::Inventory>>
        instancePtr = std::make_shared<InventoryContainer>("inventories");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Inventory>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::Inventory>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::Inventory>>>(container);
}
