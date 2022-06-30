#pragma once
#include "CaseContainers/ConditionalCaseContainer.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/PropertyReader.hpp"

using ConditionalCaseContainerImpl = ContainerImpl<QuestCore::ConditionalCaseContainer,
    ContainerInitializer<QuestCore::ConditionalCaseContainer>,
    PropertyReader<std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader>,
    PropertyReader<std::shared_ptr<QuestCore::ICaseContainer>, ContainerReader>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICondition>>, FactoryReader>
>;

class ConditionalCaseContainerImpl_Binder
{
public:
    ConditionalCaseContainerImpl_Binder();

private:
    static ConditionalCaseContainerImpl_Binder instance;
};
