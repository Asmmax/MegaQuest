#include "Quests/Slots/ParagraphSlot.hpp"
#include "Quests/Input.hpp"

using namespace QuestCore;

ParagraphSlot::ParagraphSlot(const QuestHeaderPtr& quest):
	Base(quest)
{
}

ParagraphSlot::ParagraphPtr ParagraphSlot::GetParagraph() const
{
	return Get();
}
