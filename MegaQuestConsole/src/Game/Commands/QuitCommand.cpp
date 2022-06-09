#include "Game/Commands/QuitCommand.hpp"
#include "Game/Events.hpp"

using namespace Game;

void QuitCommand::Run()
{
	Events::Quit.Send();
}
