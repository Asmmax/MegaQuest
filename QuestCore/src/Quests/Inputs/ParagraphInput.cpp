#include "Quests/Inputs/ParagraphInput.hpp"
#include "Quests/Slots/ParagraphSlot.hpp"

using namespace QuestCore;

ParagraphInput::ParagraphInput(IParagraph* paragraph, 
	ParagraphSlot* slot,
	Quest* quest):
	
	Base(paragraph, slot, quest)
{
}
