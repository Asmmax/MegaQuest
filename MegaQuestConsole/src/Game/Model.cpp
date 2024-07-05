#include "Game/Model.hpp"
#include "Game/IDialog.hpp"
#include "IQuest.hpp"

using namespace Game;

Model::Model(IDialog* rootDialog, QuestCore::IQuest* quest):
	_rootDialog(rootDialog),
	_quest(quest),
	_output(nullptr)
{
}

void Model::SetOutput(IOutput* output)
{
	_output = output;
}

void Model::Reset()
{
	_quest->Init();
	Init();
	Update();
}

void Model::Init()
{
	_rootDialog->Init(*_output);
}

void Model::Update()
{
	_rootDialog->Update();
	_rootDialog->Draw(*_output);
}
