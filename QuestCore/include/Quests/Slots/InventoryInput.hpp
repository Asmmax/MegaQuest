#pragma once
#include "Quests/QuestInitable.hpp"
#include <memory>

namespace QuestCore
{
	class InventorySlot;
	class Inventory;

	/// @serializable @shared inputs
	class InventoryInput : public QuestInitable
	{
		using InventorySlotPtr = std::shared_ptr<InventorySlot>;
		using InventoryPtr = std::shared_ptr<Inventory>;

	public:
		InventoryInput(const InventoryPtr& inventory, 
			const InventorySlotPtr& slot,
			const QuestHeaderPtr& quest);
		virtual void Init() override;
		InventoryPtr GetInventory() const;

	private:
		InventorySlotPtr _slot;
		InventoryPtr _inventory;
	};
}
