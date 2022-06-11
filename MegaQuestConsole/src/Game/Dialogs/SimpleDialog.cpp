#include "Game/Dialogs/SimpleDialog.hpp"
#include "Game/IButtonList.hpp"
#include "Game/IOutput.hpp"
#include "IParagraph.hpp"
#include "ICaseContainer.hpp"

using namespace Game;


SimpleDialog::SimpleDialog(const OutputPtr& output,
	const QuestCore::TextString& intro,
	const ParagraphPtr& paragraph, 
	const CaseContainerPtr& container) :

	IntroDialog(output, intro),
	_paragraph(paragraph),
	_container(container)
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

void SimpleDialog::AddButtonList(const std::string& key, const IButtonList::Ptr& buttonList)
{
	_buttonGroups[key] = buttonList;
}

IButtonList::Ptr SimpleDialog::GetButtonList(const std::string& key)
{
	auto foundIt = _buttonGroups.find(key);
	if (foundIt == _buttonGroups.end()) {
		return nullptr;
	}
	return foundIt->second;
}

void SimpleDialog::Update()
{
	auto&& output = GetOutput();

	_text = QuestCore::TextString();
	_paragraph->Print(*this);
	output->WriteLn(_text);

	for (auto buttonGroup : _buttonGroups) {
		buttonGroup.second->Clear();
	}
	_container->Print(*this);

	if (auto defaultButtons = GetButtonList()) {
		defaultButtons->Update(*output);
	}
}
