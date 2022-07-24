#include "Game/ButtonLists/ReplayButtonList.hpp"
#include "Game/Replay/ReplayAction.hpp"
#include "Game/Replay/ReplayManager.hpp"

using namespace Game;

ReplayButtonList::ReplayButtonList(const IButtonList::Ptr& buttonList, const ReplayManagerPtr& manager):
	_buttonList(buttonList),
	_manager(manager)
{
}

void ReplayButtonList::Draw(IOutput& output)
{
}

void ReplayButtonList::UpdateImpl()
{
}

void ReplayButtonList::DoImpl(int answer)
{
	_manager->PushAction(ReplayAction{ _buttonList, answer });
}
