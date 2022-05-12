#include "CaseContainers/CaseContainerStateMachine.hpp"
#include <assert.h>

using namespace QuestCore;

void CaseContainerStateMachine::Print(IButtonPanel& buttonPanel)
{
	assert(_state);
	_state->Print(buttonPanel);
}
