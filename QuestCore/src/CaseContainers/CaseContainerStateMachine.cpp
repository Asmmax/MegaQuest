#include "CaseContainers/CaseContainerStateMachine.hpp"
#include <assert.h>

using namespace QuestCore;

CaseContainerStateMachine::CaseContainerStateMachine(const QuestHeaderPtr& quest):
	QuestInitable(quest)
{
}

void CaseContainerStateMachine::InitState(const ICaseContainer::WeakPtr& state)
{
	_initState = state;
}

void CaseContainerStateMachine::SetState(const ICaseContainer::WeakPtr& state)
{
	_state = state;
}

void CaseContainerStateMachine::Print(IButtonGroup& buttons)
{
	auto statePtr = _state.lock();
	assert(statePtr);
	if (statePtr) {
		statePtr->Print(buttons);
	}
}

void CaseContainerStateMachine::Init()
{
	SetState(_initState);
}
