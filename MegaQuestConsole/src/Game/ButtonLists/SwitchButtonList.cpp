#include "Game/ButtonLists/SwitchButtonList.hpp"

using namespace Game;

SwitchButtonList::SwitchButtonList(const std::vector<IButtonList*>& targets)
{
	for (auto target : targets) {
		AddButtonList(target);
	}
}

void SwitchButtonList::Draw(IOutput& /*output*/)
{
}

void SwitchButtonList::Switch(const IButtonList* buttonList)
{
	auto foundIt = std::find_if(_buttonLists.begin(), _buttonLists.end(), [buttonList](IButtonList* buttonListPtr) -> bool {
		return buttonListPtr == buttonList;
		});
	_currentButtonList = *foundIt;
}

void SwitchButtonList::AddButtonList(IButtonList* buttonList)
{
	buttonList->AddPreUpdateCallback([rawPtr = buttonList, this]() {
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
