#include "Game/ButtonLists/SwitchButtonList.hpp"

using namespace Game;

void SwitchButtonList::Do(int answer)
{
	if (_currentButtonList) {
		_currentButtonList->Do(answer);
	}
}

void SwitchButtonList::Update()
{
	_currentButtonList = nullptr;
}

void SwitchButtonList::Draw()
{
}

void SwitchButtonList::Switch(const IButtonList* buttonList)
{
	auto foundIt = std::find_if(_buttonLists.begin(), _buttonLists.end(), [buttonList](const IButtonList::Ptr& buttonListPtr) -> bool {
		return buttonListPtr.get() == buttonList;
		});
	_currentButtonList = *foundIt;
}

void SwitchButtonList::AddButtonList(const IButtonList::Ptr& buttonList)
{
	_buttonLists.push_back(buttonList);
}
