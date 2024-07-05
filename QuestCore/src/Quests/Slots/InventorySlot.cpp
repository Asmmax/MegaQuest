#include "Quests/Slots/InventorySlot.hpp"
#include "Quests/Input.hpp"

using namespace QuestCore;

InventorySlot::InventorySlot(Quest* quest):
	Base(quest)
{
}

Inventory* InventorySlot::GetInventory() const
{
	return Get();
}
