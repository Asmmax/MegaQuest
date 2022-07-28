#include "Quests/ParagraphSlot.hpp"
#include "Quests/ParagraphInput.hpp"

using namespace QuestCore;

void ParagraphSlot::Update()
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
