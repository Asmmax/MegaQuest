#include "Game/Dialogs/SwitchDialog.hpp"
#include "Game/IDialog.hpp"
#include "Game/IButtonList.hpp"
#include "Game/IOutput.hpp"
#include <assert.h>

using namespace Game;

SwitchDialog::SwitchDialog(const OutputPtr& output, const QuestCore::TextString& intro):
	IntroDialog(output, intro)
{
}

void SwitchDialog::AddDialog(const DialogPtr& dialog)
{
	if (_dialogs.empty()) {
		_currentDialog = dialog;
	}

	_dialogs.push_back(dialog);
}

void SwitchDialog::AddButtonList(const IButtonList::Ptr& buttonList)
{
	_buttonGroups.push_back(buttonList);
	buttonList->SetButtonDoneCallback([this]() {
		Update();
		});
}

void SwitchDialog::Init()
{
	IntroDialog::Init();
	_currentDialog->Init();
}

void SwitchDialog::Update()
{
	for (auto& buttonGroup : _buttonGroups) {
		buttonGroup->Update();
	}

	_currentDialog->Update();
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
	_currentDialog->Init();
	Update();
}
