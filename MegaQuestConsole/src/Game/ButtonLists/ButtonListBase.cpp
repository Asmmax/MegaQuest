#include "Game/ButtonLists/ButtonListBase.hpp"
#include "Game/ButtonLists/SwitchButtonList.hpp"
#include "Game/IOutput.hpp"
#include "Game/IDialog.hpp"
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

void ButtonListBase::Do(int answer)
{
	if (answer < 0 || answer >= _buttons.size()) {
		IO::Logger::Instance().Log(_error);
		return;
	}

	_buttons[answer].callback();

	if (auto ptr = _parentDialog.lock()) {
		ptr->Update();
		ptr->Draw();
	}
}

void ButtonListBase::Update()
{
	if (auto ptr = _switchList.lock()) {
		ptr->Switch(this);
	}
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

void ButtonListBase::SetParentDialog(const DialogWeakPtr& dialog)
{
	_parentDialog = dialog;
}

void ButtonListBase::SetSwitchButtonList(const SwitchButtonListPtr& switchList)
{
	_switchList = switchList;
}
