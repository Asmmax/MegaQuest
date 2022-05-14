#include "Game/Dialog.hpp"
#include "Game/ButtonList.hpp"
#include "Game/IOutput.hpp"
#include "IParagraph.hpp"
#include "ICaseContainer.hpp"

using namespace Game;


Dialog::Dialog(const OutputPtr& output, const ParagraphPtr& paragraph, const CaseContainerPtr& container) :
	_output(output),
	_paragraph(paragraph),
	_container(container)
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
		auto buttonGroup = std::make_shared<ButtonList>();
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

void Dialog::Update()
{
	_text = QuestCore::TextString();
	_paragraph->Print(*this);
	_output->WriteLn(_text);

	_buttonGroups.clear();
	_container->Print(*this);

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
