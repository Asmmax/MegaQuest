#include "Actions/ParagraphSwitching.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"

using namespace QuestCore;

ParagraphSwitching::ParagraphSwitching(const std::shared_ptr<ParagraphStateMachine>& stateMachine, const std::shared_ptr<IParagraph>& nextParagraph):
	_stateMachine(stateMachine),
	_nextParagraph(nextParagraph)
{
}

void ParagraphSwitching::Do()
{
	_stateMachine->SetState(_nextParagraph);
}
