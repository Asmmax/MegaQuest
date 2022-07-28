#include "Quests/QuestHeader.hpp"
#include "Quests/ISlot.hpp"

using namespace QuestCore;

QuestHeader::QuestHeader(const std::vector<SlotPtr>& slots) :
	_slots(slots)
{
}

void QuestHeader::Init()
{
	UpdateSlots();
	Reset();
}

void QuestHeader::UpdateSlots()
{
	for (auto& slot : _slots) {
		slot->Update();
	}
}

void QuestHeader::Reset()
{

}
