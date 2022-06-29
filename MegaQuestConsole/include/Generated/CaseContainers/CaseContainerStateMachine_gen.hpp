#pragma once
#include "CaseContainers/CaseContainerStateMachine.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"

using CaseContainerStateMachineInitializer = ContainerInitializer<QuestCore::CaseContainerStateMachine,
    MethodInitializer<QuestCore::CaseContainerStateMachine, std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>>
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
