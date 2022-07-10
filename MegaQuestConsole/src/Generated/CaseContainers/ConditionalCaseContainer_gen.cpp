#include "Generated/CaseContainers/ConditionalCaseContainer_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

ConditionalCaseContainerImpl_Binder ConditionalCaseContainerImpl_Binder::instance;

ConditionalCaseContainerImpl_Binder::ConditionalCaseContainerImpl_Binder()
{
    auto impl = std::make_shared<ConditionalCaseContainerImpl>(
        ConditionalCaseContainerInitializer(
        )
        , CreateProperty<std::shared_ptr<QuestCore::ICaseContainer>>("thenContainer", nullptr)
        , CreateProperty<std::shared_ptr<QuestCore::ICaseContainer>>("elseContainer", nullptr)
        , CreateProperty<std::vector<std::shared_ptr<QuestCore::ICondition>>>("conditions", std::vector<std::shared_ptr<QuestCore::ICondition>>())
        );

    ContainerBinder<QuestCore::ConditionalCaseContainer>().BindImpl("ConditionalCaseContainer", impl);
    ContainerBinder<QuestCore::ICaseContainer>().BindImpl("ConditionalCaseContainer", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::ConditionalCaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<ConditionalCaseContainerImpl>& impl)
{
    BindImplWithCast< ConditionalCaseContainerContainer, ConditionalCaseContainerImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::ConditionalCaseContainer>>& GlobalContext::GetContainer<QuestCore::ConditionalCaseContainer>()
{
    static std::shared_ptr<ContainerBase<QuestCore::ConditionalCaseContainer>>
        instancePtr = std::make_shared<ConditionalCaseContainerContainer>("containers");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ConditionalCaseContainer>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::ConditionalCaseContainer>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::ConditionalCaseContainer>>>(container);
}
