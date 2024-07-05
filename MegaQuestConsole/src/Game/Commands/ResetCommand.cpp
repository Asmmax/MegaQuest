#include "Game/Commands/ResetCommand.hpp"
#include "Game/Model.hpp"

using namespace Game;

ResetCommand::ResetCommand(Model* model):
	_model(model)
{
}

void ResetCommand::Run()
{
	_model->Reset();
}
