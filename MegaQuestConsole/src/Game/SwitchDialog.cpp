#include "Game/SwitchDialog.hpp"
#include "Game/IDialog.hpp"
#include "Game/IButtonList.hpp"

using namespace Game;

void SwitchDialog::AddDialog(const DialogPtr& dialog)
{
	if (_dialogs.empty()) {
		_currentDialog = dialog;
	}

	_dialogs.push_back(dialog);
}

IButtonList::Ptr SwitchDialog::GetButtonList(const std::string& key)
{
	return _currentDialog->GetButtonList(key);
}

void SwitchDialog::Init()
{
	_currentDialog->Init();
}

void SwitchDialog::Update()
{
	_currentDialog->Update();
}
