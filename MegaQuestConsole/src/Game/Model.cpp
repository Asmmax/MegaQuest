#include "Game/Model.hpp"
#include "Game/IDialog.hpp"
#include "IQuest.hpp"

using namespace Game;

Model::Model(const DialogPtr& rootDialog, const QuestPtr& quest):
	_rootDialog(rootDialog),
	_quest(quest)
{
}

void Model::SetOutput(const OutputPtr& output)
{
	_output = output;
}

void Model::Init()
{
	_quest->Init();
	_rootDialog->Init(*_output);
}

void Model::Update()
{
	_rootDialog->Update();
	_rootDialog->Draw(*_output);
}
