#include "Quests/Slots/ParagraphSlot.hpp"
#include "Quests/Slots/ParagraphInput.hpp"

using namespace QuestCore;

ParagraphSlot::ParagraphSlot(const QuestHeaderPtr& quest):
	QuestInitable(quest)
{
}

void ParagraphSlot::Init()
{
	_input = nullptr;
}

void ParagraphSlot::SetInput(ParagraphInput* input)
{
	_input = input;
}

ParagraphSlot::ParagraphPtr ParagraphSlot::GetParagraph() const
{
	if (!_input) {
		return nullptr;
	}
	return _input->GetParagraph();
}
