#include "Game/ButtonLists/SwitchButtonList.hpp"

using namespace Game;

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
	buttonList->AddPreUpdateCallback([rawPtr = buttonList.get(), this]() {
		Switch(rawPtr);
		});
	_buttonLists.push_back(buttonList);
}

void SwitchButtonList::UpdateImpl()
{
	_currentButtonList = nullptr;
}

void SwitchButtonList::DoImpl(int answer)
{
	if (_currentButtonList) {
		_currentButtonList->Do(answer);
	}
}
