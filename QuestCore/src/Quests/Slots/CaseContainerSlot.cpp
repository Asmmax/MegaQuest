#include "Quests/Slots/CaseContainerSlot.hpp"
#include "Quests/Input.hpp"

using namespace QuestCore;

CaseContainerSlot::CaseContainerSlot(Quest* quest):
	Base(quest)
{
}

ICaseContainer* CaseContainerSlot::GetCaseContainer() const
{
	return Get();
}
