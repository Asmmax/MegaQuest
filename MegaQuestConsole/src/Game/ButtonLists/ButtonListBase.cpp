#include "Game/ButtonLists/ButtonListBase.hpp"
#include "Game/IOutput.hpp"
#include "IO/Logger.hpp"

using namespace Game;

ButtonListBase::ButtonListBase(const IOutput::Ptr& output,
	const QuestCore::TextString& error,
	bool show) :

	_output(output),
	_error(error),
	_show(show)
{
}

void ButtonListBase::AddButton(const Button& button)
{
	_buttons.push_back(button);
}

void ButtonListBase::Draw() 
{
	if (!_show) {
		return;
	}

	auto names = GetNames();
	int num = 1;
	for (auto& name : names) {
		_output->WriteLn(QuestCore::TextString(num++) + QuestCore::TextString::FromUtf8(u8". ") + name);
	}
}

void ButtonListBase::DoImpl(int answer)
{
	if (answer < 0 || answer >= _buttons.size()) {
		IO::Logger::Instance().Log(_error);
		return;
	}

	_buttons[answer].callback();
}

std::vector<QuestCore::TextString> ButtonListBase::GetNames() const
{
	std::vector<QuestCore::TextString> _names;
	for (auto& button : _buttons) {
		_names.push_back(button.name);
	}
	return _names;
}

void ButtonListBase::Clear()
{
	_buttons.clear();
}
