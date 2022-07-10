#include "Generated/Actions/Copying_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

CopyingImpl_Binder CopyingImpl_Binder::instance;

CopyingImpl_Binder::CopyingImpl_Binder()
{
    auto impl = std::make_shared<CopyingImpl>(
        CopyingInitializer(
        )
        , CreateProperty<std::shared_ptr<QuestCore::Inventory>>("source", nullptr)
        , CreateProperty<std::shared_ptr<QuestCore::Inventory>>("target", nullptr)
        );

    ContainerBinder<QuestCore::Copying>().BindImpl("Copying", impl);
    ContainerBinder<QuestCore::IAction>().BindImpl("Copying", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::Copying>::BindImpl(const std::string& implName, const std::shared_ptr<CopyingImpl>& impl)
{
    BindImplWithCast<CopyingContainer, CopyingImpl>(implName, impl);
}


template<>
const std::shared_ptr<ContainerBase<QuestCore::Copying>>& GlobalContext::GetContainer<QuestCore::Copying>()
{
    static std::shared_ptr<ContainerBase<QuestCore::Copying>>
        instancePtr = std::make_shared<CopyingContainer>("actions");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::Copying>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::Copying>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::Copying>>>(container);
}
