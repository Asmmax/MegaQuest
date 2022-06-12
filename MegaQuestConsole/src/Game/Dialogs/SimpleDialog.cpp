#include "Game/Dialogs/SimpleDialog.hpp"
#include "Game/IButtonList.hpp"
#include "Game/IOutput.hpp"
#include "IParagraph.hpp"

using namespace Game;


SimpleDialog::SimpleDialog(const OutputPtr& output,
	const QuestCore::TextString& intro,
	const ParagraphPtr& paragraph) :

	IntroDialog(output, intro),
	_paragraph(paragraph)
{
}

void SimpleDialog::AppendText(const QuestCore::TextString& text)
{
	_text += text;
}

void SimpleDialog::AddButtonList(const std::string& key, const IButtonList::Ptr& buttonList)
{
	_buttonGroups[key] = buttonList;
	buttonList->SetButtonDoneCallback([this]() {
		Update();
		});
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
	
	for (auto& buttonGroup : _buttonGroups) {
		buttonGroup.second->Update();
	}
}
