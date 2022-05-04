#include "Paragraphs/ParagraphStateMachine.hpp"

#include <assert.h>

using namespace QuestCore;

TextString ParagraphStateMachine::GetQuest() const
{
	assert(_state);
	return _state->GetQuest();
}

CaseContainer& ParagraphStateMachine::GetCaseContainer()
{
	assert(_state);
	return _state->GetCaseContainer();
}
