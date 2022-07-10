#include "Generated/Actions/Transfer_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

TransferImpl_Binder TransferImpl_Binder::instance;

TransferImpl_Binder::TransferImpl_Binder()
{
    auto impl = std::make_shared<TransferImpl>(
        TransferInitializer(
        )
        , CreateProperty<std::shared_ptr<QuestCore::Inventory>>("source", nullptr)
        , CreateProperty<std::shared_ptr<QuestCore::Inventory>>("target", nullptr)
        , CreateProperty<std::vector<QuestCore::ItemRecord>>("items", std::vector<QuestCore::ItemRecord>())
        );

    ContainerBinder<QuestCore::Transfer>().BindImpl("Transfer", impl);
    ContainerBinder<QuestCore::IAction>().BindImpl("Transfer", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::Transfer>::BindImpl(const std::string& implName, const std::shared_ptr<TransferImpl>& impl)
{
    BindImplWithCast<TransferContainer, TransferImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::Transfer>>& GlobalContext::GetContainer<QuestCore::Transfer>()
{
    static std::shared_ptr<ContainerBase<QuestCore::Transfer>>
        instancePtr = std::make_shared<TransferContainer>("actions");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Transfer>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::Transfer>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::Transfer>>>(container);
}
