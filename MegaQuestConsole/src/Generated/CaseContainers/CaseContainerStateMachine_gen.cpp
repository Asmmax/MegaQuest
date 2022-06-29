#include "Generated/CaseContainers/CaseContainerStateMachine_gen.hpp"
#include "Generated/ICaseContainer_gen.hpp"

CaseContainerStateMachineImpl_Binder CaseContainerStateMachineImpl_Binder::instance;

CaseContainerStateMachineImpl_Binder::CaseContainerStateMachineImpl_Binder()
{
    auto iCaseContainerContainer = GlobalContext::GetContainer<QuestCore::ICaseContainer>();

    ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>
        caseContainerReader(iCaseContainerContainer);

    MethodInitializer<QuestCore::CaseContainerStateMachine, 
        std::shared_ptr<QuestCore::ICaseContainer>, 
        ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>
    >
        stateInitializer("state", caseContainerReader, nullptr,
            [](const std::shared_ptr<QuestCore::CaseContainerStateMachine>& element, const std::shared_ptr<QuestCore::ICaseContainer>& arg) {
                element->SetState(arg);
            });

    CaseContainerStateMachineInitializer caseContainerStateMachineInitializer(stateInitializer);
    auto caseContainerStateMachineImpl = std::make_shared<CaseContainerStateMachineImpl>(
        caseContainerStateMachineInitializer);

    if (auto containerContainer = std::dynamic_pointer_cast<ICaseContainerContainer>(GlobalContext::GetContainer<QuestCore::ICaseContainer>())) {
        containerContainer->SetInheritor<CaseContainerStateMachineImpl>(
            ReaderImplRecord<CaseContainerStateMachineImpl>{ "CaseContainerStateMachine", caseContainerStateMachineImpl });
    }
}
