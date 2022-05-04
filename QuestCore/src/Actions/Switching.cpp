#include "Actions/Switching.hpp"
#include "Paragraphs/ParagraphStateMachine.hpp"

using namespace QuestCore;

Switching::Switching(const std::shared_ptr<ParagraphStateMachine>& stateMachine, const std::shared_ptr<IParagraph>& nextParagraph):
	_stateMachine(stateMachine),
	_nextParagraph(nextParagraph)
{
}

void Switching::Do()
{
	_stateMachine->SetState(_nextParagraph);
}
