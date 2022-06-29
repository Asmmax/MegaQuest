#include "Generated/Actions/CaseContainerSwitching_gen.hpp"
#include "Generated/IAction_gen.hpp"

CaseContainerSwitchingImpl_Binder CaseContainerSwitchingImpl_Binder::instance;

CaseContainerSwitchingImpl_Binder::CaseContainerSwitchingImpl_Binder()
{
    auto iCaseContainerContainer = GlobalContext::GetContainer<QuestCore::ICaseContainer>();

    ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>, std::shared_ptr<QuestCore::CaseContainerStateMachine>> 
    containerStateMachineReader(iCaseContainerContainer);

    ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>> 
    containerReader(iCaseContainerContainer);

    MethodInitializer<QuestCore::CaseContainerSwitching, 
    std::shared_ptr<QuestCore::CaseContainerStateMachine>, 
    ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>, std::shared_ptr<QuestCore::CaseContainerStateMachine>>
    >
        caseContainerStateMachineInitializer("stateMachine", containerStateMachineReader, nullptr,
            [](const std::shared_ptr<QuestCore::CaseContainerSwitching>& element, const std::shared_ptr<QuestCore::CaseContainerStateMachine>& arg) {
                element->SetStateMachine(arg);
            });

    MethodInitializer<QuestCore::CaseContainerSwitching, 
    std::shared_ptr<QuestCore::ICaseContainer>, 
    ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>
    >
        caseContainerInitializer("nextContainer", containerReader, nullptr,
            [](const std::shared_ptr<QuestCore::CaseContainerSwitching>& element, const std::shared_ptr<QuestCore::ICaseContainer>& arg) {
                element->SetNextContainer(arg);
            });

    ContainerSwitchingInitializer containerSwitchingInitializer(caseContainerStateMachineInitializer, caseContainerInitializer);
    auto caseContainerSwitchingImpl = std::make_shared<CaseContainerSwitchingImpl>(containerSwitchingInitializer);

    if (auto actionContainer = std::dynamic_pointer_cast<IActionContainer>(GlobalContext::GetContainer<QuestCore::IAction>())) {
        actionContainer->SetInheritor<CaseContainerSwitchingImpl>(
            ReaderImplRecord<CaseContainerSwitchingImpl>{ "CaseContainerSwitching", caseContainerSwitchingImpl });
    }
}
