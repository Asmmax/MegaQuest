#pragma once
#include "CaseContainers/CaseContainerGroup.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using CaseContainerGroupInitializer = ContainerInitializer<QuestCore::CaseContainerGroup>;

using CaseContainerGroupImpl = ContainerImpl<QuestCore::CaseContainerGroup,
    CaseContainerGroupInitializer,
    std::vector<std::shared_ptr<QuestCore::ICaseContainer>>
>;

class CaseContainerGroupImpl_Binder
{
public:
    CaseContainerGroupImpl_Binder();

private:
    static CaseContainerGroupImpl_Binder instance;
};

using CaseContainerGroupContainer = Container<QuestCore::CaseContainerGroup, CaseContainerGroupImpl>;

template<>
template<>
void ContainerBinder<QuestCore::CaseContainerGroup>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerGroupImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::CaseContainerGroup>>& GlobalContext::GetContainer<QuestCore::CaseContainerGroup>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::CaseContainerGroup>>> GetReader();
