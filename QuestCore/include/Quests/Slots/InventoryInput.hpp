#pragma once
#include "Quests/ISlot.hpp"
#include <memory>

namespace QuestCore
{
	class InventorySlot;
	class Inventory;

	/// @serializable
	class InventoryInput : public ISlot
	{
		using InventorySlotPtr = std::shared_ptr<InventorySlot>;
		using InventoryPtr = std::shared_ptr<Inventory>;

	public:
		InventoryInput(const InventoryPtr& inventory, const InventorySlotPtr& slot);
		virtual void Update() override;
		InventoryPtr GetInventory() const;

	private:
		InventorySlotPtr _slot;
		InventoryPtr _inventory;
	};
}
