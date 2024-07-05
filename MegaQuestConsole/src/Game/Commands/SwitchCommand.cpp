#include "Game/Commands/SwitchCommand.hpp"
#include "Game/Dialogs/SwitchDialog.hpp"

using namespace Game;

SwitchCommand::SwitchCommand(SwitchDialog* dialog) :
	_dialog(dialog)
{
}

void SwitchCommand::Run()
{
	_dialog->Next();
}
