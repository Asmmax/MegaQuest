#include "Game/Commands/LevelUpCommand.hpp"
#include "Game/Model.hpp"
#include "Quests/QuestList.hpp"

using namespace Game;

LevelUpCommand::LevelUpCommand(const ModelPtr& model, const QuestListPtr& questList) :
	_model(model),
	_questList(questList)
{
}

void LevelUpCommand::Run()
{
	_questList->Up();
	_model->Reset();
}
