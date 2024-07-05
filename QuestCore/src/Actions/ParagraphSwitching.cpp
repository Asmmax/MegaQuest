#include "Actions/ParagraphSwitching.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"

using namespace QuestCore;

void ParagraphSwitching::SetStateMachine(ParagraphStateMachine* stateMachine)
{
	_stateMachine = stateMachine;
}

void ParagraphSwitching::SetNextParagraph(IParagraph* nextParagraph)
{
	_nextParagraph = nextParagraph;
}

void ParagraphSwitching::Do()
{
	if (_stateMachine) {
		_stateMachine->SetState(_nextParagraph);
	}
}
