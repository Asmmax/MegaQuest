#include "Quests/Inputs/ParagraphInput.hpp"
#include "Quests/Slots/ParagraphSlot.hpp"

using namespace QuestCore;

ParagraphInput::ParagraphInput(const ParagraphPtr& paragraph, 
	const ParagraphSlotPtr& slot,
	const QuestHeaderPtr& quest):
	
	Base(paragraph, slot, quest)
{
}
