#pragma once
#include "Quests/Slot.hpp"

namespace QuestCore
{
	class Inventory;

	/// @serializable @shared slots
	class InventorySlot : public Slot<Inventory>
	{
		using Base = Slot<Inventory>;
		using InventoryPtr = std::shared_ptr<Inventory>;
	public:
		InventorySlot(const QuestHeaderPtr& quest);
		InventoryPtr GetInventory() const;
	};
}
