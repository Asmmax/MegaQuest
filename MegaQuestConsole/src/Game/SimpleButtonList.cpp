#include "Game/SimpleButtonList.hpp"
#include "Game/IOutput.hpp"
#include "Game/IDialog.hpp"
#include "IO/Logger.hpp"

using namespace Game;

SimpleButtonList::SimpleButtonList(const DialogWeakPtr& parent, const QuestCore::TextString& error):
	_parent(parent),
	_error(error)
{
}

void SimpleButtonList::Clear()
{
	_buttons.clear();
}

void SimpleButtonList::AddButton(const QuestCore::TextString& text, const std::function<void()>& callback)
{
	Button button{ text, [callback]() {
		callback();
	} };
	_buttons.push_back(button);
}

void SimpleButtonList::Do(int answer)
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

std::vector<QuestCore::TextString> SimpleButtonList::GetNames() const
{
	std::vector<QuestCore::TextString> _names;
	for (auto& button : _buttons) {
		_names.push_back(button.name);
	}
	return _names;
}

void SimpleButtonList::Update(IOutput& output)
{
	auto names = GetNames();
	int num = 1;
	for (auto& name : names) {
		output.WriteLn(QuestCore::TextString(num++) + QuestCore::TextString::FromUtf8(u8". ") + name);
	}
}
