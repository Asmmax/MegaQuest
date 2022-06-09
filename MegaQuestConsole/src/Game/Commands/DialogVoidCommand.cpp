#include "Game/Commands/DialogVoidCommand.hpp"
#include "Game/IDialog.hpp"
#include "Game/ButtonList.hpp"

using namespace Game;

DialogVoidCommand::DialogVoidCommand(const DialogPtr& dialog, const std::string& key) :
	_dialog(dialog),
	_key(key)
{
}

void DialogVoidCommand::Run()
{
	if (auto inventoryButtons = _dialog->GetButtonList(_key)) {
		inventoryButtons->Do();
	}
}