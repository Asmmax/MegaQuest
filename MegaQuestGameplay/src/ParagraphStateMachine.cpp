#include "ParagraphStateMachine.hpp"

#include <assert.h>

using namespace QuestCore;

TextString ParagraphStateMachine::GetQuest() const
{
	assert(_state);
	return _state->GetQuest();
}

ActionContainer& ParagraphStateMachine::GetActionContainer()
{
	assert(_state);
	return _state->GetActionContainer();
}
