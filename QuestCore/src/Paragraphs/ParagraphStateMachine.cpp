#include "Paragraphs/ParagraphStateMachine.hpp"
#include "TextString.hpp"
#include <assert.h>

using namespace QuestCore;

void ParagraphStateMachine::SetState(const std::weak_ptr<IParagraph>& state)
{
	_state = state;
}

void ParagraphStateMachine::Print(ITextView& view)
{
	auto statePtr = _state.lock();
	assert(statePtr);
	if (statePtr) {
		statePtr->Print(view);
	}
}
