#include "Game/Commands/SwitchCommand.hpp"
#include "Game/Dialogs/SwitchDialog.hpp"

using namespace Game;

SwitchCommand::SwitchCommand(const SwitchDialogPtr& dialog) :
	_dialog(dialog)
{
}

void SwitchCommand::Run()
{
	_dialog->Next();
}
