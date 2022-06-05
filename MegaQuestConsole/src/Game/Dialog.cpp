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
		auto buttonGroup = std::make_shared<ButtonList>(this);
		auto res = _buttonGroups.emplace(actionKey, buttonGroup);
		foundIt = res.first;
	}
	return *foundIt->second;
}

ButtonList::Ptr Dialog::GetButtonList(const std::string& key)
{
	auto foundIt = _buttonGroups.find(key);
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

	if (auto defaultButtons = GetButtonList()) {
		defaultButtons->Update(*_output);
	}
}
