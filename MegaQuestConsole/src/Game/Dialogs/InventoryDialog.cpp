#include "Game/Dialogs/InventoryDialog.hpp"
#include "Game/IOutput.hpp"
#include "Game/IButtonList.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

using namespace Game;

InventoryDialog::InventoryDialog(const QuestCore::TextString& intro,
	const InventoryPtr& inventory,
	const std::vector<ButtonListPtr> buttonGroups):

	DialogBase(intro, buttonGroups),
	_inventory(inventory)
{
}

void InventoryDialog::Draw(IOutput& output)
{
	auto& items = _inventory->GetItems();

	for (auto& item : items) {
		output.WriteLn(item.first->GetContains(item.second));
	}

	DialogBase::Draw(output);
}

