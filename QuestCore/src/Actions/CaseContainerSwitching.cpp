#include "Actions/CaseContainerSwitching.hpp"
#include "CaseContainers/CaseContainerStateMachine.hpp"

using namespace QuestCore;

void CaseContainerSwitching::SetStateMachine(CaseContainerStateMachine* stateMachine)
{
	_stateMachine = stateMachine;
}

void CaseContainerSwitching::SetNextContainer(ICaseContainer* nextContainer)
{
	_nextContainer = nextContainer;
}

void CaseContainerSwitching::Do()
{
	if (_stateMachine) {
		_stateMachine->SetState(_nextContainer);
	}
}
