#include "Actions/CaseContainerSwitching.hpp"
#include "CaseContainers/CaseContainerStateMachine.hpp"

using namespace QuestCore;

void CaseContainerSwitching::SetStateMachine(const std::weak_ptr<CaseContainerStateMachine>& stateMachine)
{
	_stateMachine = stateMachine;
}

void CaseContainerSwitching::SetNextContainer(const std::weak_ptr<ICaseContainer>& nextContainer)
{
	_nextContainer = nextContainer;
}

void CaseContainerSwitching::Do()
{
	if (auto stateMachinePtr = _stateMachine.lock()) {
		stateMachinePtr->SetState(_nextContainer);
	}
}
