#include "Generated/CaseContainers/CaseContainerGroup_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

CaseContainerGroupImpl_Binder CaseContainerGroupImpl_Binder::instance;

CaseContainerGroupImpl_Binder::CaseContainerGroupImpl_Binder()
{
    auto impl = std::make_shared<CaseContainerGroupImpl>(
        CaseContainerGroupInitializer(
        )
        , CreateProperty<std::vector<std::shared_ptr<QuestCore::ICaseContainer>>>("children", std::vector<std::shared_ptr<QuestCore::ICaseContainer>>())
        );

    ContainerBinder<QuestCore::CaseContainerGroup>().BindImpl("CaseContainerGroup", impl);
    ContainerBinder<QuestCore::ICaseContainer>().BindImpl("CaseContainerGroup", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::CaseContainerGroup>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerGroupImpl>& impl)
{
    BindImplWithCast<CaseContainerGroupContainer, CaseContainerGroupImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::CaseContainerGroup>>& GlobalContext::GetContainer<QuestCore::CaseContainerGroup>()
{
    static std::shared_ptr<ContainerBase<QuestCore::CaseContainerGroup>>
        instancePtr = std::make_shared<CaseContainerGroupContainer>("containers");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::CaseContainerGroup>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::CaseContainerGroup>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::CaseContainerGroup>>>(container);
}
