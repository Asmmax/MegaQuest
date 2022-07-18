#include "Game/Model.hpp"
#include "Game/IDialog.hpp"

using namespace Game;

Model::Model(const DialogPtr& rootDialog):
	_rootDialog(rootDialog)
{
}

void Model::SetOutput(const OutputPtr& output)
{
	_output = output;
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
