#include "Game/ButtonList.hpp"
#include "Game/IOutput.hpp"
#include "Game/IDialog.hpp"
#include "IO/Logger.hpp"

using namespace Game;

ButtonList::ButtonList(const DialogWeakPtr& parent):
	_parent(parent)
{
}

ButtonList::ButtonList(const DialogWeakPtr& parent, const QuestCore::TextString& error):
	_parent(parent),
	_error(error)
{
}

void ButtonList::Clear()
{
	_buttons.clear();
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

	if (auto ptr = _parent.lock()) {
		ptr->Update();
	}
}

void ButtonList::Do(int answer)
{
	if (answer < 0 || answer >= _buttons.size()) {
		IO::Logger::Instance().Log(_error);
		return;
	}

	_buttons[answer].callback();

	if (auto ptr = _parent.lock()) {
		ptr->Update();
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
