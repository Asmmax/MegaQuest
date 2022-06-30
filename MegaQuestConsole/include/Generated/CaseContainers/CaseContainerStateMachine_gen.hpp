#pragma once
#include "CaseContainers/CaseContainerStateMachine.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/GlobalContext.hpp"

using CaseContainerStateMachineInitializer = ContainerInitializer<QuestCore::CaseContainerStateMachine,
    MethodInitializer<QuestCore::CaseContainerStateMachine, std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader>
>;

using CaseContainerStateMachineImpl = ContainerImpl<QuestCore::CaseContainerStateMachine,
    CaseContainerStateMachineInitializer
>;

class CaseContainerStateMachineImpl_Binder
{
public:
    CaseContainerStateMachineImpl_Binder();

private:
    static CaseContainerStateMachineImpl_Binder instance;
};

using CaseContainerStateMachineContainer = Container<QuestCore::CaseContainerStateMachine, CaseContainerStateMachineImpl>;

template<>
const std::shared_ptr<ContainerBase<QuestCore::CaseContainerStateMachine>>& GlobalContext::GetContainer<QuestCore::CaseContainerStateMachine>();
