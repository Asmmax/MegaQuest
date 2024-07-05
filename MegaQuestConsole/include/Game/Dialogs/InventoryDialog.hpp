#pragma once
#include "Game/Dialogs/DialogBase.hpp"

namespace QuestCore
{
	class IInventoryFactory;
	class Inventory;
}

namespace Game
{
	class InventoryDialog : public DialogBase
	{
	public:
		InventoryDialog(const QuestCore::TextString& intro, QuestCore::IInventoryFactory* inventoryFactory,
			const std::vector<IButtonList*> buttonGroups = std::vector<IButtonList*>());
		virtual void Draw(IOutput& output) override;
		
	private:
		QuestCore::IInventoryFactory* _inventoryFactory;
	};
}
