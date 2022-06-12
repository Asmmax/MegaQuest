#include "Game/Dialogs/InventoryDialog.hpp"
#include "Game/IOutput.hpp"
#include "Game/IButtonList.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

using namespace Game;

InventoryDialog::InventoryDialog(const OutputPtr& output, 
	const QuestCore::TextString& intro,
	const InventoryPtr& inventory):

	DialogBase(output, intro),
	_inventory(inventory)
{
}

void InventoryDialog::Draw()
{
	auto&& output = GetOutput();
	auto& items = _inventory->GetItems();

	for (auto& item : items) {
		output->WriteLn(item.first->GetContains(item.second));
	}

	DialogBase::Draw();
}

