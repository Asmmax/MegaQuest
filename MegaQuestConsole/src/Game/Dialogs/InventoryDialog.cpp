#include "Game/Dialogs/InventoryDialog.hpp"
#include "Game/IOutput.hpp"
#include "Game/IButtonList.hpp"
#include "Inventory.hpp"
#include "Item.hpp"

using namespace Game;

InventoryDialog::InventoryDialog(const OutputPtr& output, 
	const QuestCore::TextString& intro,
	const InventoryPtr& inventory):

	IntroDialog(output, intro),
	_inventory(inventory)
{
}

void InventoryDialog::AddButtonList(const std::string& key, const IButtonList::Ptr& buttonList)
{
	_buttonGroups[key] = buttonList;
}

IButtonList::Ptr InventoryDialog::GetButtonList(const std::string& key)
{
	auto foundIt = _buttonGroups.find(key);
	if (foundIt == _buttonGroups.end()) {
		return nullptr;
	}
	return foundIt->second;
}

void InventoryDialog::Update()
{
	auto&& output = GetOutput();
	auto& items = _inventory->GetItems();

	for (auto& item : items) {
		output->WriteLn(item.first->GetContains(item.second));
	}

	if (auto defaultButtons = GetButtonList()) {
		defaultButtons->Update();
	}
}
