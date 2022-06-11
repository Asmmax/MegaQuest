#include "Game/ButtonListBase.hpp"
#include "Game/IOutput.hpp"
#include "Game/IDialog.hpp"

using namespace Game;

ButtonListBase::ButtonListBase(const DialogWeakPtr& parent,
	const IOutput::Ptr& output,
	const QuestCore::TextString& error) :

	_parent(parent),
	_output(output),
	_error(error)
{
}

void ButtonListBase::AddButton(const QuestCore::TextString& text, const std::function<void()>& callback)
{
	Button button{ text, callback};
	_buttons.push_back(button);
}

void ButtonListBase::Do(int answer)
{
	if (answer < 0 || answer >= _buttons.size()) {
		_output->WriteLn(_error);
		return;
	}

	_buttons[answer].callback();

	if (auto ptr = _parent.lock()) {
		ptr->Update();
	}
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

void ButtonListBase::Print()
{
	auto names = GetNames();
	int num = 1;
	for (auto& name : names) {
		_output->WriteLn(QuestCore::TextString(num++) + QuestCore::TextString::FromUtf8(u8". ") + name);
	}
}
