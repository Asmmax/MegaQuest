#include "Game/Commands/ForceChoiceCommand.hpp"
#include "Game/IButtonList.hpp"

using namespace Game;

ForceChoiceCommand::ForceChoiceCommand(const ButtonListPtr& buttonList, int choiceId) :
	_buttonList(buttonList),
	_choiceId(choiceId)
{
}

void ForceChoiceCommand::Run()
{
	_buttonList->Do(_choiceId);
}
