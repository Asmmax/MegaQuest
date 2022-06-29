#pragma once
#include "CaseContainers/CaseContainerGroup.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ReaderStrategy/ContainerReader.hpp"
#include "Containers/ContainerImpl.hpp"
#include "Containers/PropertyReader.hpp"

using CaseContainerGroupImpl = ContainerImpl<QuestCore::CaseContainerGroup,
    ContainerInitializer<QuestCore::CaseContainerGroup>,
    PropertyReader<std::vector<std::shared_ptr<QuestCore::ICaseContainer>>, ContainerReader<std::shared_ptr<QuestCore::ICaseContainer>>>
>;

class CaseContainerGroupImpl_Binder
{
public:
    CaseContainerGroupImpl_Binder();

private:
    static CaseContainerGroupImpl_Binder instance;
};
