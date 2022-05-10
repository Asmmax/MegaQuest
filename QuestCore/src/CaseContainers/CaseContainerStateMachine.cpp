#include "CaseContainers/CaseContainerStateMachine.hpp"
#include <assert.h>

using namespace QuestCore;

const std::vector<Case>& CaseContainerStateMachine::GetCases(const std::string& key) const
{
	assert(_state);
	return _state->GetCases(key);
}

size_t CaseContainerStateMachine::GetCaseCount() const
{
	assert(_state);
	return _state->GetCaseCount();
}
