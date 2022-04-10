#include "ParagraphStateMachine.hpp"

#include <assert.h>

using namespace QuestCore;

std::string ParagraphStateMachine::GetQuest() const
{
	assert(_state);
	return _state->GetQuest();
}

std::string ParagraphStateMachine::GetCases() const
{
	assert(_state);
	return _state->GetCases();
}

int ParagraphStateMachine::GetCaseCount() const
{
	assert(_state);
	return _state->GetCaseCount();
}

void ParagraphStateMachine::Answer(int caseID)
{
	assert(_state);
	_state->Answer(caseID);
}
