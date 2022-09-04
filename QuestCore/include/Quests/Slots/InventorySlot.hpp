#pragma once
#include "Quests/Slot.hpp"
#include "IInventoryFactory.hpp"

namespace QuestCore
{
	/// @serializable @shared slots
	class InventorySlot : public IInventoryFactory, public Slot<Inventory>
	{
		using Base = Slot<Inventory>;
	public:
		InventorySlot(const QuestPtr& quest);
		InventoryPtr GetInventory() const;
	};
}
