#include "Game/Model.hpp"
#include "Game/Dialog.hpp"
#include "Game/ButtonList.hpp"

using namespace Game;

Model::Model(const std::vector<DialogPtr>& dialogs):
	_dialogs(dialogs)
{
	_currentDialog = dialogs[0];
}

void Model::OpenInventory()
{
	if (auto inventoryButtons = _currentDialog->GetButtonList("inventory")) {
		inventoryButtons->Do();
	}
}

void Model::Handle(int answer)
{
	if (auto defaultButtons = _currentDialog->GetButtonList()) {
		defaultButtons->Do(answer);
	}
}

void Model::Update()
{
	_currentDialog->Update();
}
