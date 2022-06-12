#include "Game/ButtonLists/ButtonListBase.hpp"
#include "Game/ButtonLists/SwitchButtonList.hpp"
#include "Game/IOutput.hpp"
#include "IO/Logger.hpp"

using namespace Game;

ButtonListBase::ButtonListBase(const IOutput::Ptr& output,
	const QuestCore::TextString& error) :

	_output(output),
	_error(error)
{
}

void ButtonListBase::AddButton(const Button& button)
{
	Button copyButton(button);
	copyButton.callback = [callback = copyButton.callback, afterCallback = _buttonDone]() {
		callback();
		if (afterCallback) {
			afterCallback();
		}
	};
	_buttons.push_back(copyButton);
}

void ButtonListBase::Do(int answer)
{
	if (answer < 0 || answer >= _buttons.size()) {
		IO::Logger::Instance().Log(_error);
		return;
	}

	_buttons[answer].callback();
}

void ButtonListBase::Update()
{
	_switchList->Switch(shared_from_this());
}

std::vector<QuestCore::TextString> ButtonListBase::GetNames() const
{
	std::vector<QuestCore::TextString> _names;
	for (auto& button : _buttons) {
		_names.push_back(button.name);
	}
	return _names;
}

void ButtonListBase::SetButtonDoneCallback(const Callback& callback)
{
	_buttonDone = callback;
}

void ButtonListBase::Clear()
{
	_buttons.clear();
}

void ButtonListBase::Print()
{
	auto names = GetNames();
	int num = 1;
	for (auto& name : names) {
		_output->WriteLn(QuestCore::TextString(num++) + QuestCore::TextString::FromUtf8(u8". ") + name);
	}
}

void ButtonListBase::SetSwitchButtonList(const SwitchButtonListPtr& switchList)
{
	_switchList = switchList;
}
