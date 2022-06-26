#pragma once
#include "CaseContainers/CaseContainerGroup.hpp"
#include "CaseContainers/CaseContainerStateMachine.hpp"
#include "CaseContainers/ConditionalCaseContainer.hpp"
#include "CaseContainers/SimpleCaseContainer.hpp"
#include "ICaseContainer.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/MethodInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/Container.hpp"

namespace QuestCore
{
    class ICondition;
    struct Case;
}

// CaseContainerGroup

using CaseContainerGroupImpl = ContainerImpl<QuestCore::CaseContainerGroup,
    ContainerInitializer<QuestCore::CaseContainerGroup>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICaseContainer>>, ContainerReader>
>;

// CaseContainerStateMachine

using CaseContainerStateMachineInitializer = ContainerInitializer<QuestCore::CaseContainerStateMachine,
    MethodInitializer<QuestCore::CaseContainerStateMachine, std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader>
>;

using CaseContainerStateMachineImpl = ContainerImpl<QuestCore::CaseContainerStateMachine,
    CaseContainerStateMachineInitializer
>;

//ConditionalCaseContainer

using ConditionalCaseContainerImpl = ContainerImpl<QuestCore::ConditionalCaseContainer,
    ContainerInitializer<QuestCore::ConditionalCaseContainer>,
    PropertyReader<std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader>,
    PropertyReader<std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICondition>>, FactoryReader>
>;

// SimpleCaseContainer

using SimpleCaseContainerImpl = ContainerImpl<QuestCore::SimpleCaseContainer,
    ContainerInitializer<QuestCore::SimpleCaseContainer>,
    PropertyReader<std::vector<QuestCore::Case>, FactoryReader>
>;

//Containers

using ICaseContainerContainer = Container<QuestCore::ICaseContainer, CaseContainerGroupImpl, CaseContainerStateMachineImpl, ConditionalCaseContainerImpl, SimpleCaseContainerImpl>;
using CaseContainerStateMachineContainer = Container<QuestCore::CaseContainerStateMachine, CaseContainerStateMachineImpl>;
