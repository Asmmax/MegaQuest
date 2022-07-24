#include "Game/Replay/ReplayAction.hpp"
#include "Game/IButtonList.hpp"

using namespace Game;

void ReplayAction::operator()()
{
	buttonList->Do(answer);
}
