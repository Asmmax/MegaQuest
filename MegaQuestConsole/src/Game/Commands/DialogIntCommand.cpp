#include "Game/Commands/DialogIntCommand.hpp"
#include "Game/IDialog.hpp"
#include "Game/ButtonList.hpp"

using namespace Game;

DialogIntCommand::DialogIntCommand(const DialogPtr& dialog, const QuestCore::TextString& error) :
	IntCommand(error),
	_dialog(dialog)
{
}

void DialogIntCommand::Run(int arg)
{
	if (auto defaultButtons = _dialog->GetButtonList()) {
		defaultButtons->Do(arg - 1);
	}
}