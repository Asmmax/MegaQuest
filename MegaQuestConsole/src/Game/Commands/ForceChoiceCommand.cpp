#include "Game/Commands/ForceChoiceCommand.hpp"
#include "Game/IButtonList.hpp"

using namespace Game;

ForceChoiceCommand::ForceChoiceCommand(IButtonList* buttonList, int choiceId) :
	_buttonList(buttonList),
	_choiceId(choiceId)
{
}

void ForceChoiceCommand::Run()
{
	_buttonList->Do(_choiceId);
}
