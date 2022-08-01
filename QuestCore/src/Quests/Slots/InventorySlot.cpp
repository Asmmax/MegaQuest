#include "Quests/Slots/InventorySlot.hpp"
#include "Quests/Input.hpp"

using namespace QuestCore;

InventorySlot::InventorySlot(const QuestHeaderPtr& quest):
	Base(quest)
{
}

InventorySlot::InventoryPtr InventorySlot::GetInventory() const
{
	return Get();
}
