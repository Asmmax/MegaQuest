#include "Game/SimpleDialog.hpp"
#include "Game/ButtonList.hpp"
#include "Game/IOutput.hpp"
#include "IParagraph.hpp"
#include "ICaseContainer.hpp"

using namespace Game;


SimpleDialog::SimpleDialog(const OutputPtr& output, 
	const ParagraphPtr& paragraph, 
	const CaseContainerPtr& container,
	const QuestCore::TextString& intro) :

	_output(output),
	_paragraph(paragraph),
	_container(container),
	_intro(intro)
{
}

void SimpleDialog::AppendText(const QuestCore::TextString& text)
{
	_text += text;
}

QuestCore::IButtonGroup::Ptr SimpleDialog::GetButtonGroup(const std::string& actionKey)
{
	return GetButtonList(actionKey);
}

void SimpleDialog::AddButtonList(const std::string& key, const ButtonList::Ptr& buttonList)
{
	_buttonGroups[key] = buttonList;
}

ButtonList::Ptr SimpleDialog::GetButtonList(const std::string& key)
{
	auto foundIt = _buttonGroups.find(key);
	if (foundIt == _buttonGroups.end()) {
		return nullptr;
	}
	return foundIt->second;
}

void SimpleDialog::Init()
{
	_output->WriteLn(_intro);
	Update();
}

void SimpleDialog::Update()
{
	_text = QuestCore::TextString();
	_paragraph->Print(*this);
	_output->WriteLn(_text);

	for (auto buttonGroup : _buttonGroups) {
		buttonGroup.second->Clear();
	}
	_container->Print(*this);

	if (auto defaultButtons = GetButtonList()) {
		defaultButtons->Update(*_output);
	}
}
