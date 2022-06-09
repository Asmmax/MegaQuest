#include "Game/SwitchDialog.hpp"
#include "Game/IDialog.hpp"
#include "Game/ButtonList.hpp"

using namespace Game;

SwitchDialog::SwitchDialog(const std::vector<IDialog::Ptr>& dialogs):
	_dialogs(dialogs)
{
	_currentDialog = dialogs[0];
}

ButtonList::Ptr SwitchDialog::GetButtonList(const std::string& key)
{
	return _currentDialog->GetButtonList(key);
}

void SwitchDialog::Update()
{
	_currentDialog->Update();
}
