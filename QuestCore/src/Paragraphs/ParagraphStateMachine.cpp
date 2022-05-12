#include "Paragraphs/ParagraphStateMachine.hpp"
#include "TextString.hpp"
#include <assert.h>

using namespace QuestCore;

void ParagraphStateMachine::Print(ITextView& view)
{
	assert(_state);
	_state->Print(view);
}
