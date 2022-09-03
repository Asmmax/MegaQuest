#pragma once
#include "Quests/Input.hpp"

namespace QuestCore
{
	class InventorySlot;
	class Inventory;

	/// @serializable @shared inputs
	class InventoryInput : public Input<Inventory>
	{
		using Base = Input<Inventory>;
		using InventorySlotPtr = std::shared_ptr<InventorySlot>;
		using InventoryPtr = std::shared_ptr<Inventory>;
	public:
		InventoryInput(const InventoryPtr& inventory, 
			const InventorySlotPtr& slot,
			const QuestPtr& quest);
	};
}
