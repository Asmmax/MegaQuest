#include "Game/Commands/ChoiceCommand.hpp"
#include "Game/IDialog.hpp"
#include "Game/IButtonList.hpp"

using namespace Game;

ChoiceCommand::ChoiceCommand(const DialogPtr& dialog,
	const std::string& actionKey,
	const QuestCore::TextString& error) :

	IntCommand(error),
	_dialog(dialog),
	_actionKey(actionKey)
{
}

void ChoiceCommand::Run(int arg)
{
	if (auto defaultButtons = _dialog->GetButtonList(_actionKey)) {
		defaultButtons->Do(arg - 1);
	}
}
