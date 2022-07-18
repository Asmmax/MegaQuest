#pragma once
#include "Game/Dialogs/DialogBase.hpp"

namespace QuestCore
{
	class Inventory;
}

namespace Game
{
	/// @serializable
	class InventoryDialog : public DialogBase
	{
		using InventoryPtr = std::shared_ptr<QuestCore::Inventory>;

	public:
		InventoryDialog(const QuestCore::TextString& intro, const InventoryPtr& inventory, 
			const std::vector<ButtonListPtr> buttonGroups = std::vector<ButtonListPtr>());
		virtual void Draw(IOutput& output) override;
		
	private:
		InventoryPtr _inventory;
	};
}
