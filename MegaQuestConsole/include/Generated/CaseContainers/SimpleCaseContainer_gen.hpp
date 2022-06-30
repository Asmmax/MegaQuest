#pragma once
#include "CaseContainers/SimpleCaseContainer.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/ReaderStrategy/FactoryReader.hpp"
#include "Containers/PropertyReader.hpp"

using SimpleCaseContainerImpl = ContainerImpl<QuestCore::SimpleCaseContainer,
    ContainerInitializer<QuestCore::SimpleCaseContainer>,
    PropertyReader<std::vector<QuestCore::Case>, FactoryReader>
>;

class SimpleCaseContainerImpl_Binder
{
public:
    SimpleCaseContainerImpl_Binder();

private:
    static SimpleCaseContainerImpl_Binder instance;
};
