#include "Game/Commands/ResetCommand.hpp"
#include "Game/Model.hpp"

using namespace Game;

ResetCommand::ResetCommand(const ModelPtr& model):
	_model(model)
{
}

void ResetCommand::Run()
{
	_model->Reset();
}
