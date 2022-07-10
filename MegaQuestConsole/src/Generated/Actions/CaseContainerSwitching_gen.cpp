#include "Generated/Actions/CaseContainerSwitching_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

CaseContainerSwitchingImpl_Binder CaseContainerSwitchingImpl_Binder::instance;

CaseContainerSwitchingImpl_Binder::CaseContainerSwitchingImpl_Binder()
{
    auto impl = std::make_shared<CaseContainerSwitchingImpl>(
        ContainerSwitchingInitializer(
            CreateMethod<QuestCore::CaseContainerSwitching, std::shared_ptr<QuestCore::CaseContainerStateMachine>>("stateMachine", nullptr,
                [](const std::shared_ptr<QuestCore::CaseContainerSwitching>& element, const std::shared_ptr<QuestCore::CaseContainerStateMachine>& arg) {
                    element->SetStateMachine(arg);
                }),
            CreateMethod<QuestCore::CaseContainerSwitching, std::shared_ptr<QuestCore::ICaseContainer>>("nextContainer", nullptr,
                [](const std::shared_ptr<QuestCore::CaseContainerSwitching>& element, const std::shared_ptr<QuestCore::ICaseContainer>& arg) {
                    element->SetNextContainer(arg);
                })
        )
        );

    ContainerBinder<QuestCore::CaseContainerSwitching>().BindImpl("CaseContainerSwitching", impl);
    ContainerBinder<QuestCore::IAction>().BindImpl("CaseContainerSwitching", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::CaseContainerSwitching>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerSwitchingImpl>& impl)
{
    BindImplWithCast<CaseContainerSwitchingContainer, CaseContainerSwitchingImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::CaseContainerSwitching>>& GlobalContext::GetContainer<QuestCore::CaseContainerSwitching>()
{
    static std::shared_ptr<ContainerBase<QuestCore::CaseContainerSwitching>>
        instancePtr = std::make_shared<CaseContainerSwitchingContainer>("actions");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::CaseContainerSwitching>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::CaseContainerSwitching>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::CaseContainerSwitching>>>(container);
}
