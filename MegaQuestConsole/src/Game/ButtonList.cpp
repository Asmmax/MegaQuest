#include "Game/ButtonList.hpp"
#include "Game/IOutput.hpp"
#include "Game/Dialog.hpp"
#include "IO/Logger.hpp"

using namespace Game;

ButtonList::ButtonList(Dialog* parent):
	_parent(parent)
{
}

void ButtonList::AddButton(const QuestCore::TextString& text, const std::function<void()>& callback)
{
	Button button{ text, [callback]() {
		callback();
	} };
	_buttons.push_back(button);
}

void ButtonList::Do()
{
	if (_buttons.empty()) {
		return;
	}

	_buttons[0].callback();

	if (_parent) {
		_parent->Update();
	}
}

void ButtonList::Do(int answer)
{
	if (answer < 0 || answer >= _buttons.size()) {
		return;
	}

	_buttons[answer].callback();
	if (_parent) {
		_parent->Update();
	}
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

void ButtonList::Update(IOutput& output)
{
	auto names = GetNames();
	int num = 1;
	for (auto& name : names) {
		output.WriteLn(QuestCore::TextString(num++) + QuestCore::TextString::FromUtf8(u8". ") + name);
	}
}
