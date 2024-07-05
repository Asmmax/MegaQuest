#include "Game/Dialogs/SwitchDialog.hpp"
#include "Game/IDialog.hpp"
#include "Game/IButtonList.hpp"
#include "Game/IOutput.hpp"
#include "Game/Model.hpp"
#include <assert.h>

using namespace Game;

SwitchDialog::SwitchDialog(const QuestCore::TextString& intro, 
	const std::vector<IButtonList*> buttonGroups,
	const std::vector<IDialog*>& dialogs):

	DialogBase(intro, buttonGroups),
	_isIntroShowed(false)
{
	for (auto& dialog : dialogs) {
		AddDialog(dialog);
	}
}

void SwitchDialog::AddDialog(IDialog* dialog)
{
	if (_dialogs.empty()) {
		_currentDialog = dialog;
	}

	_dialogs.push_back(dialog);
}

void SwitchDialog::Init(IOutput& output)
{
	if (!_isIntroShowed) {
		DialogBase::Init(output);
		_isIntroShowed = true;
	}
	_currentDialog->Init(output);
}

void SwitchDialog::Update()
{
	DialogBase::Update();
	_currentDialog->Update();
}

void SwitchDialog::Draw(IOutput& output)
{
	_currentDialog->Draw(output);
	DialogBase::Draw(output);
}

void SwitchDialog::Next()
{
	if (_dialogs.size() < 2) {
		return;
	}

	auto foundIt = std::find(_dialogs.begin(), _dialogs.end(), _currentDialog);

	assert(foundIt != _dialogs.end());
	if (foundIt == _dialogs.end()) {
		return;
	}

	size_t count = _dialogs.size();
	size_t currId = std::distance(_dialogs.begin(), foundIt);
	size_t nextId = (currId + 1) % count;

	_currentDialog = _dialogs[nextId];
	
	if (auto model = GetModel()) {
		model->Init();
		model->Update();
	}
}
