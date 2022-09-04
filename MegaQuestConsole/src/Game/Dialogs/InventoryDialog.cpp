#include "Game/Dialogs/InventoryDialog.hpp"
#include "Game/IOutput.hpp"
#include "Game/IButtonList.hpp"
#include "Inventory.hpp"
#include "Item.hpp"
#include "Quests/Slots/InventorySlot.hpp"

using namespace Game;

InventoryDialog::InventoryDialog(const QuestCore::TextString& intro,
	const InventoryFactoryPtr& inventoryFactory,
	const std::vector<ButtonListPtr> buttonGroups):

	DialogBase(intro, buttonGroups),
	_inventoryFactory(inventoryFactory)
{
}

void InventoryDialog::Draw(IOutput& output)
{
	auto inventory = _inventoryFactory->GetInventory();
	if (!inventory) {
		return;
	}

	auto& items = inventory->GetItems();

	for (auto& item : items) {
		output.WriteLn(item.first->GetContains(item.second));
	}

	DialogBase::Draw(output);
}

