#include "Game/Commands/ForceChoiceCommand.hpp"
#include "Game/IDialog.hpp"
#include "Game/IButtonList.hpp"

using namespace Game;

ForceChoiceCommand::ForceChoiceCommand(const DialogPtr& dialog, const std::string& actionKey, int choiceId) :
	_dialog(dialog),
	_actionKey(actionKey),
	_choiceId(choiceId)
{
}

void ForceChoiceCommand::Run()
{
	if (auto inventoryButtons = _dialog->GetButtonList(_actionKey)) {
		inventoryButtons->Do(_choiceId);
	}
}
