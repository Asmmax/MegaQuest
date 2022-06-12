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

void InventoryDialog::AddButtonList(const IButtonList::Ptr& buttonList)
{
	_buttonGroups.push_back(buttonList);
	buttonList->SetButtonDoneCallback([this]() {
		Update();
		});
}

void InventoryDialog::Update()
{
	auto&& output = GetOutput();
	auto& items = _inventory->GetItems();

	for (auto& item : items) {
		output->WriteLn(item.first->GetContains(item.second));
	}

	for (auto& buttonGroup : _buttonGroups) {
		buttonGroup->Update();
	}
}
