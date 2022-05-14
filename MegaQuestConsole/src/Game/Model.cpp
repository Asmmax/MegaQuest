#include "Game/Model.hpp"
#include "Game/Dialog.hpp"
#include "QuestBase.hpp"

using namespace Game;

Model::Model(const std::vector<DialogPtr>& dialogs, const QuestPtr& quest):
	_dialogs(dialogs),
	_quest(quest)
{
	_currentDialog = dialogs[0];
	_currentDialog->SetQuest(_quest);
}

void Model::OpenInventory()
{
	_currentDialog->OpenInventory();
	_currentDialog->Update();
}

bool Model::Handle(int answer)
{
	if (_currentDialog->Answer(answer)) {
		_currentDialog->Update();
		return true;
	}

	return false;
}

void Model::Init()
{
	_quest->Update();
	_currentDialog->Update();
}
