#pragma once
#include "ICaseContainer.hpp"

#include "Generated/CaseContainers/CaseContainerGroup_gen.hpp"
#include "Generated/CaseContainers/CaseContainerStateMachine_gen.hpp"
#include "Generated/CaseContainers/ConditionalCaseContainer_gen.hpp"
#include "Generated/CaseContainers/SimpleCaseContainer_gen.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using ICaseContainerContainer = Container<QuestCore::ICaseContainer, CaseContainerGroupImpl, CaseContainerStateMachineImpl, ConditionalCaseContainerImpl, SimpleCaseContainerImpl>;

template<>
template<>
void ContainerBinder<QuestCore::ICaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerGroupImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::ICaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerStateMachineImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::ICaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<ConditionalCaseContainerImpl>& impl);

template<>
template<>
void ContainerBinder<QuestCore::ICaseContainer>::BindImpl(const std::string& implName, const std::shared_ptr<SimpleCaseContainerImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::ICaseContainer>>& GlobalContext::GetContainer<QuestCore::ICaseContainer>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::ICaseContainer>>> GetReader();
