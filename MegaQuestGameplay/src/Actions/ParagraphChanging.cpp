#include "Actions/ParagraphChanging.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"

using namespace QuestCore;

ParagraphChanging::ParagraphChanging(const std::shared_ptr<ParagraphStateMachine>& stateMachine, const std::shared_ptr<IParagraph>& nextParagraph):
	_stateMachine(stateMachine),
	_nextParagraph(nextParagraph)
{
}

void ParagraphChanging::Do()
{
	_stateMachine->SetState(_nextParagraph);
}
