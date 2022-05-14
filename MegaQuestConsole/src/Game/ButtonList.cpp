#include "Game/ButtonList.hpp"

using namespace Game;

void ButtonList::AddButton(const QuestCore::TextString& text, const std::function<void()>& callback)
{
	Button button{ text, [callback]() {
		callback();
	} };
	_buttons.push_back(button);
}

void ButtonList::Do()
{
	_buttons[0].callback();
}

void ButtonList::Do(int answer)
{
	_buttons[answer].callback();
}

std::vector<QuestCore::TextString> ButtonList::GetNames() const
{
	std::vector<QuestCore::TextString> _names;
	for (auto& button : _buttons) {
		_names.push_back(button.name);
	}
	return _names;
}

size_t ButtonList::GetButtonCount() const
{
	return _buttons.size();
}
