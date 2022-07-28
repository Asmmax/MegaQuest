#include "Paragraphs/ParagraphStateMachine.hpp"
#include "TextString.hpp"
#include <assert.h>

using namespace QuestCore;

ParagraphStateMachine::ParagraphStateMachine(const QuestHeaderPtr& quest):
	QuestInitable(quest)
{
}

void ParagraphStateMachine::InitState(const std::weak_ptr<IParagraph>& state)
{
	_initState = state;
}

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

void ParagraphStateMachine::Init()
{
	SetState(_initState);
}
