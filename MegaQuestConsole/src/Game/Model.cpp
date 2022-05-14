#include "Game/Model.hpp"
#include "Game/Dialog.hpp"

using namespace Game;

Model::Model(const std::vector<DialogPtr>& dialogs):
	_dialogs(dialogs)
{
	_currentDialog = dialogs[0];
}

void Model::OpenInventory()
{
	_currentDialog->OpenInventory();
}

bool Model::Handle(int answer)
{
	return _currentDialog->Answer(answer);
}

void Model::Update()
{
	_currentDialog->Update();
}
