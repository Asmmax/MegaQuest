#pragma once
#include "Game/Dialogs/DialogBase.hpp"

namespace QuestCore
{
	class IInventoryFactory;
	class Inventory;
}

namespace Game
{
	/// @serializable
	class InventoryDialog : public DialogBase
	{
		using InventoryFactoryPtr = std::shared_ptr<QuestCore::IInventoryFactory>;
		using InventoryPtr = std::shared_ptr<QuestCore::Inventory>;

	public:
		InventoryDialog(const QuestCore::TextString& intro, const InventoryFactoryPtr& inventoryFactory,
			const std::vector<ButtonListPtr> buttonGroups = std::vector<ButtonListPtr>());
		virtual void Draw(IOutput& output) override;
		
	private:
		InventoryFactoryPtr _inventoryFactory;
	};
}
