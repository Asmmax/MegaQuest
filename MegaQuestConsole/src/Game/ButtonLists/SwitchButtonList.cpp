#include "Game/ButtonLists/SwitchButtonList.hpp"

using namespace Game;

void SwitchButtonList::Do(int answer)
{
	if (_currentButtonList) {
		_currentButtonList->Do(answer);
	}
}

void SwitchButtonList::SetButtonDoneCallback(const Callback& callback)
{
	_buttonDone = callback;
}

void SwitchButtonList::Switch(const IButtonList::Ptr& buttonList)
{
	_currentButtonList = buttonList;
}
