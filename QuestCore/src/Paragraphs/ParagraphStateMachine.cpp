#include "Paragraphs/ParagraphStateMachine.hpp"
#include "TextString.hpp"
#include <assert.h>

using namespace QuestCore;

TextString ParagraphStateMachine::GetText() const
{
	assert(_state);
	return _state->GetText();
}
