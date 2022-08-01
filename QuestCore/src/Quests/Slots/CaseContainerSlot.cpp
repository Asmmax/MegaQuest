#include "Quests/Slots/CaseContainerSlot.hpp"
#include "Quests/Input.hpp"

using namespace QuestCore;

CaseContainerSlot::CaseContainerSlot(const QuestHeaderPtr& quest):
	Base(quest)
{
}

CaseContainerSlot::CaseContainerPtr CaseContainerSlot::GetCaseContainer() const
{
	return Get();
}
