#pragma once
#include "Quests/Slot.hpp"
#include "IInventoryFactory.hpp"

namespace QuestCore
{
	class InventorySlot : public IInventoryFactory, public Slot<Inventory>
	{
		using Base = Slot<Inventory>;
	public:
		InventorySlot(Quest* quest);
		Inventory* GetInventory() const;
	};
}
