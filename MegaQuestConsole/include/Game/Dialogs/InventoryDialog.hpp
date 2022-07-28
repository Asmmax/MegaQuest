#pragma once
#include "Game/Dialogs/DialogBase.hpp"

namespace QuestCore
{
	class InventorySlot;
	class Inventory;
}

namespace Game
{
	/// @serializable
	class InventoryDialog : public DialogBase
	{
		using InventorySlotPtr = std::shared_ptr<QuestCore::InventorySlot>;
		using InventoryPtr = std::shared_ptr<QuestCore::Inventory>;

	public:
		InventoryDialog(const QuestCore::TextString& intro, const InventorySlotPtr& inventorySlot,
			const std::vector<ButtonListPtr> buttonGroups = std::vector<ButtonListPtr>());
		virtual void Draw(IOutput& output) override;
		
	private:
		InventorySlotPtr _inventorySlot;
	};
}
