#pragma once
#include "Actions/CaseContainerSwitching.hpp"

#include "ICaseContainer.hpp"
#include "CaseContainers/CaseContainerStateMachine.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"

using ContainerSwitchingInitializer = ContainerInitializer<QuestCore::CaseContainerSwitching,
    MethodInitializer<QuestCore::CaseContainerSwitching, std::shared_ptr<QuestCore::CaseContainerStateMachine>, ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>, std::shared_ptr<QuestCore::CaseContainerStateMachine>>>,
    MethodInitializer<QuestCore::CaseContainerSwitching, std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>>
>;

using CaseContainerSwitchingImpl = ContainerImpl<QuestCore::CaseContainerSwitching,
    ContainerSwitchingInitializer
>;

class CaseContainerSwitchingImpl_Binder
{
public:
    CaseContainerSwitchingImpl_Binder();

private:
    static CaseContainerSwitchingImpl_Binder instance;
};
