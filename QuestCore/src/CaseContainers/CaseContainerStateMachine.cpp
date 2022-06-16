#include "CaseContainers/CaseContainerStateMachine.hpp"
#include <assert.h>

using namespace QuestCore;

void CaseContainerStateMachine::SetState(const ICaseContainer::WeakPtr& newState)
{
	_state = newState;
}

void CaseContainerStateMachine::Print(IButtonGroup& buttons)
{
	auto statePtr = _state.lock();
	assert(statePtr);
	if (statePtr) {
		statePtr->Print(buttons);
	}
}
