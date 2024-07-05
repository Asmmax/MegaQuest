#include "CaseContainers/CaseContainerStateMachine.hpp"
#include <assert.h>

using namespace QuestCore;

CaseContainerStateMachine::CaseContainerStateMachine(Quest* quest):
	QuestInitable(quest),
	_initState(nullptr),
	_state(nullptr)
{
}

void CaseContainerStateMachine::InitState(ICaseContainer* state)
{
	_initState = state;
}

void CaseContainerStateMachine::SetState(ICaseContainer* state)
{
	_state = state;
}

void CaseContainerStateMachine::Print(IButtonGroup& buttons)
{
	assert(_state);
	if (_state) {
		_state->Print(buttons);
	}
}

void CaseContainerStateMachine::Init()
{
	SetState(_initState);
}
