#include "Generated/CaseContainers/CaseContainerStateMachine_gen.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"

CaseContainerStateMachineImpl_Binder CaseContainerStateMachineImpl_Binder::instance;

CaseContainerStateMachineImpl_Binder::CaseContainerStateMachineImpl_Binder()
{
    auto impl = std::make_shared<CaseContainerStateMachineImpl>(
        CaseContainerStateMachineInitializer(
            CreateMethod<QuestCore::CaseContainerStateMachine,std::shared_ptr<QuestCore::ICaseContainer>>("state", nullptr, 
                [](const std::shared_ptr<QuestCore::CaseContainerStateMachine>& element, const std::shared_ptr<QuestCore::ICaseContainer>& arg) {
                    element->SetState(arg);
                })
        )
        );

    ContainerBinder<QuestCore::CaseContainerStateMachine>().BindImpl("CaseContainerStateMachine", impl);
    ContainerBinder<QuestCore::ICaseContainer>().BindImpl("CaseContainerStateMachine", impl);
}

template<>
template<>
void ContainerBinder<QuestCore::CaseContainerStateMachine>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerStateMachineImpl>& impl)
{
    BindImplWithCast<CaseContainerStateMachineContainer, CaseContainerStateMachineImpl>(implName, impl);
}

template<>
const std::shared_ptr<ContainerBase<QuestCore::CaseContainerStateMachine>>& GlobalContext::GetContainer<QuestCore::CaseContainerStateMachine>()
{
    static std::shared_ptr<ContainerBase<QuestCore::CaseContainerStateMachine>>
        instancePtr = std::make_shared<CaseContainerStateMachineContainer>("containers");
    return instancePtr;
}

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::CaseContainerStateMachine>>> GetReader()
{
    auto container = GlobalContext::GetContainer<QuestCore::CaseContainerStateMachine>();
    return std::make_shared<ContainerReader<std::shared_ptr<QuestCore::CaseContainerStateMachine>>>(container);
}
