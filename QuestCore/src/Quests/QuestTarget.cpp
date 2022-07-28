#include "Quests/QuestTarget.hpp"

using namespace QuestCore;

QuestTarget::QuestTarget(const std::vector<SlotPtr>& slots) :
	QuestHeader(slots)
{
}

void QuestTarget::Reset(const IQuest::Ptr& current)
{
	_current = current;
	UpdateSlots();
}

void QuestTarget::UpdateSlots()
{
	QuestHeader::UpdateSlots();
	_current->UpdateSlots();
}
