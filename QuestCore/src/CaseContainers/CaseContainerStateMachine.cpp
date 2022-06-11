#include "CaseContainers/CaseContainerStateMachine.hpp"
#include <assert.h>

using namespace QuestCore;

void CaseContainerStateMachine::Print(IButtonGroup& buttons)
{
	assert(_state);
	_state->Print(buttons);
}
