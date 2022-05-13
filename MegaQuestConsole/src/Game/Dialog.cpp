#include "Game/Dialog.hpp"
#include "Game/ButtonList.hpp"
#include "Game/IOutput.hpp"
#include "QuestBase.hpp"

using namespace Game;


Dialog::Dialog(const IOutput::Ptr& output) :
	_output(output)
{
}

void Dialog::Clear()
{
	_text = QuestCore::TextString();
}

void Dialog::RemoveAllButtons()
{
	_buttonGroups.clear();
}

void Dialog::AppendText(const QuestCore::TextString& text)
{
	_text += text;
}

QuestCore::IButtonGroup& Dialog::GetButtonGroup(const std::string& actionKey)
{
	auto foundIt = _buttonGroups.find(actionKey);
	if (foundIt == _buttonGroups.end()) {
		auto buttonGroup = std::make_shared<ButtonList>([this]() {
			if (_quest) {
				_quest->Update();
			}
			});
		auto res = _buttonGroups.emplace(actionKey, buttonGroup);
		foundIt = res.first;
	}
	return *foundIt->second;
}

ButtonList::Ptr Dialog::GetDefaultButtonList()
{
	auto foundIt = _buttonGroups.find("");
	if (foundIt == _buttonGroups.end()) {
		return nullptr;
	}
	return foundIt->second;
}

ButtonList::Ptr Dialog::GetInventoryButtonList()
{
	auto foundIt = _buttonGroups.find("inventory");
	if (foundIt == _buttonGroups.end()) {
		return nullptr;
	}
	return foundIt->second;
}

void Dialog::SetQuest(const QuestCore::QuestBase::Ptr& quest)
{
	_quest = quest;
}

void Dialog::Update()
{
	_output->WriteLn(_text);
	auto defaultButtons = GetDefaultButtonList();
	if (!defaultButtons) {
		return;
	}

	auto names = defaultButtons->GetNames();
	int num = 1;
	for (auto& name : names) {
		_output->WriteLn(QuestCore::TextString(num++) + QuestCore::TextString::FromUtf8(u8". ") + name);
	}
}

bool Dialog::Answer(int answer)
{
	if (answer < 0) {
		return false;
	}

	auto defaultButtons = GetDefaultButtonList();
	if (!defaultButtons) {
		return false;
	}

	auto buttonCount = defaultButtons->GetButtonCount();
	if (answer >= buttonCount) {
		return false;
	}

	defaultButtons->Do(answer);
	return true;
}

void Dialog::OpenInventory()
{
	auto inventoryButtons = GetInventoryButtonList();
	if (!inventoryButtons) {
		return;
	}

	inventoryButtons->Do();
}
