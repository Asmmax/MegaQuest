#pragma once
#include "CaseContainers/CaseContainerStateMachine.hpp"

#include "Containers/ContainerInitializer.hpp"
#include "Containers/ContainerImpl.hpp"

#include "Containers/Container.hpp"
#include "Containers/ContainerBinder.hpp"

#include "Containers/Utils.hpp"

using CaseContainerStateMachineInitializer = ContainerInitializer<QuestCore::CaseContainerStateMachine,
    std::shared_ptr<QuestCore::ICaseContainer>
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

using CaseContainerStateMachineContainer = Container<QuestCore::CaseContainerStateMachine, CaseContainerStateMachineImpl>;

template<>
template<>
void ContainerBinder<QuestCore::CaseContainerStateMachine>::BindImpl(const std::string& implName, const std::shared_ptr<CaseContainerStateMachineImpl>& impl);

template<>
const std::shared_ptr<ContainerBase<QuestCore::CaseContainerStateMachine>>& GlobalContext::GetContainer<QuestCore::CaseContainerStateMachine>();

template <>
std::shared_ptr<IReaderStrategy<std::shared_ptr<QuestCore::CaseContainerStateMachine>>> GetReader();
