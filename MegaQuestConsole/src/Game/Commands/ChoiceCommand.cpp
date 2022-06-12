#include "Game/Commands/ChoiceCommand.hpp"
#include "Game/IButtonList.hpp"

using namespace Game;

ChoiceCommand::ChoiceCommand(const ButtonListPtr& buttonList,
	const QuestCore::TextString& error) :

	IntCommand(error),
	_buttonList(buttonList)
{
}

void ChoiceCommand::Run(int arg)
{
	_buttonList->Do(arg - 1);
}
