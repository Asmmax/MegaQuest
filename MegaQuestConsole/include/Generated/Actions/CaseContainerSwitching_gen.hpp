#pragma once
#include "Actions/CaseContainerSwitching.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using ContainerSwitchingInitializer = ContainerInitializer<QuestCore::CaseContainerSwitching,
    std::shared_ptr<QuestCore::CaseContainerStateMachine>,
    std::shared_ptr<QuestCore::ICaseContainer>
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

using CaseContainerSwitchingContainer = Container<QuestCore::CaseContainerSwitching, CaseContainerSwitchingImpl>;

template<>
template<>
void ContainerBinder<QuestCore::CaseContainerSwitching>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerSwitchingImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::CaseContainerSwitching>>& GlobalContext::GetContainer<QuestCore::CaseContainerSwitching>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::CaseContainerSwitching>>> GetReader();
