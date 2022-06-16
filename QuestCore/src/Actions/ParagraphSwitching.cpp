#include "Actions/ParagraphSwitching.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"

using namespace QuestCore;

void ParagraphSwitching::SetStateMachine(const std::weak_ptr<ParagraphStateMachine>& stateMachine)
{
	_stateMachine = stateMachine;
}

void ParagraphSwitching::SetNextParagraph(const std::weak_ptr<IParagraph>& nextParagraph)
{
	_nextParagraph = nextParagraph;
}

void ParagraphSwitching::Do()
{
	if (auto stateMachinePtr = _stateMachine.lock()) {
		stateMachinePtr->SetState(_nextParagraph);
	}
}
