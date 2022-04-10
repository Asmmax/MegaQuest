#include "ParagraphChanging.hpp"
#include "ParagraphStateMachine.hpp"

using namespace QuestCore;

ParagraphChanging::ParagraphChanging(const std::string& name, const std::shared_ptr<ParagraphStateMachine>& stateMachine, const std::shared_ptr<IParagraph>& nextParagraph):
	_name(name),
	_stateMachine(stateMachine),
	_nextParagraph(nextParagraph)
{
}

std::string ParagraphChanging::GetName() const
{
	return _name;
}

void ParagraphChanging::Do()
{
	_stateMachine->SetState(_nextParagraph);
}
