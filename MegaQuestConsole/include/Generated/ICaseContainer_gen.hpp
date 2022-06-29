#pragma once
#include "ICaseContainer.hpp"

#include "Generated/CaseContainers/CaseContainerGroup_gen.hpp"
#include "Generated/CaseContainers/CaseContainerStateMachine_gen.hpp"
#include "Generated/CaseContainers/ConditionalCaseContainer_gen.hpp"
#include "Generated/CaseContainers/SimpleCaseContainer_gen.hpp"

#include "Containers/Container.hpp"
#include "Containers/GlobalContext.hpp"

using ICaseContainerContainer = Container<QuestCore::ICaseContainer, CaseContainerGroupImpl, CaseContainerStateMachineImpl, ConditionalCaseContainerImpl, SimpleCaseContainerImpl>;

template<>
const std::shared_ptr<ContainerBase<QuestCore::ICaseContainer>>& GlobalContext::GetContainer<QuestCore::ICaseContainer>();
