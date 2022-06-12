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

void SimpleDialog::AddButtonList(const IButtonList::Ptr& buttonList)
{
	_buttonGroups.push_back(buttonList);
	buttonList->SetButtonDoneCallback([this]() {
		Update();
		});
}

void SimpleDialog::Update()
{
	auto&& output = GetOutput();

	_text = QuestCore::TextString();
	_paragraph->Print(*this);
	output->WriteLn(_text);
	
	for (auto& buttonGroup : _buttonGroups) {
		buttonGroup->Update();
	}
}
