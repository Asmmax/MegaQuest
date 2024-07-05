#include "Paragraphs/ParagraphStateMachine.hpp"
#include "TextString.hpp"
#include <assert.h>

using namespace QuestCore;

ParagraphStateMachine::ParagraphStateMachine(Quest* quest):
	QuestInitable(quest),
	_initState(nullptr),
	_state(nullptr)
{
}

void ParagraphStateMachine::InitState(IParagraph* state)
{
	_initState = state;
}

void ParagraphStateMachine::SetState(IParagraph* state)
{
	_state = state;
}

void ParagraphStateMachine::Print(ITextView& view)
{
	assert(_state);
	if (_state) {
		_state->Print(view);
	}
}

void ParagraphStateMachine::Init()
{
	SetState(_initState);
}
