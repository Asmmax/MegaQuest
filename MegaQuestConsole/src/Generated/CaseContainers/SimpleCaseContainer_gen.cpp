#include "Generated/CaseContainers/SimpleCaseContainer_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

SimpleCaseContainerImpl_Binder SimpleCaseContainerImpl_Binder::instance;

SimpleCaseContainerImpl_Binder::SimpleCaseContainerImpl_Binder()
{
    auto impl = std::make_shared<SimpleCaseContainerImpl>(
        SimpleCaseContainerInitializer(
        )
        , CreateProperty<std::vector<QuestCore::Case>>("cases", std::vector<QuestCore::Case>())
        );

    ContainerBinder<QuestCore::SimpleCaseContainer>().BindImpl("SimpleCaseContainer", impl);
    ContainerBinder<QuestCore::ICaseContainer>().BindImpl("SimpleCaseContainer", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::SimpleCaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<SimpleCaseContainerImpl>& impl)
{
    BindImplWithCast< SimpleCaseContainerContainer, SimpleCaseContainerImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::SimpleCaseContainer>>& GlobalContext::GetContainer<QuestCore::SimpleCaseContainer>()
{
    static std::shared_ptr<ContainerBase<QuestCore::SimpleCaseContainer>>
        instancePtr = std::make_shared<SimpleCaseContainerContainer>("containers");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::SimpleCaseContainer>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::SimpleCaseContainer>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::SimpleCaseContainer>>>(container);
}
