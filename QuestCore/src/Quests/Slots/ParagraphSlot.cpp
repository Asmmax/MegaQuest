#include "Quests/Slots/ParagraphSlot.hpp"
#include "Quests/Input.hpp"

using namespace QuestCore;

ParagraphSlot::ParagraphSlot(Quest* quest):
	Base(quest)
{
}

IParagraph* ParagraphSlot::GetParagraph() const
{
	return Get();
}
