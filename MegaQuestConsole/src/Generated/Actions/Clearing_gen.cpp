#include "Generated/Actions/Clearing_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

ClearingImpl_Binder ClearingImpl_Binder::instance;

ClearingImpl_Binder::ClearingImpl_Binder()
{
    auto impl = std::make_shared<ClearingImpl>(
        ClearingInitializer(
        )
        , CreateProperty<std::shared_ptr<QuestCore::Inventory>>("inventory", nullptr)
        );

    ContainerBinder<QuestCore::Clearing>().BindImpl("Clearing", impl);
    ContainerBinder<QuestCore::IAction>().BindImpl("Clearing", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::Clearing>::BindImpl(const std::string& implName, const std::shared_ptr<ClearingImpl>& impl)
{
    BindImplWithCast<ClearingContainer, ClearingImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::Clearing>>& GlobalContext::GetContainer<QuestCore::Clearing>()
{
    static std::shared_ptr<ContainerBase<QuestCore::Clearing>>
        instancePtr = std::make_shared<ClearingContainer>("actions");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Clearing>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::Clearing>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::Clearing>>>(container);
}
