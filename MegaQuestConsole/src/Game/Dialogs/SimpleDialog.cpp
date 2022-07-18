#include "Game/Dialogs/SimpleDialog.hpp"
#include "Game/IButtonList.hpp"
#include "Game/IOutput.hpp"
#include "IParagraph.hpp"

using namespace Game;


SimpleDialog::SimpleDialog(const QuestCore::TextString& intro,
	const ParagraphPtr& paragraph,
	const std::vector<ButtonListPtr> buttonGroups) :

	DialogBase(intro, buttonGroups),
	_paragraph(paragraph)
{
}

void SimpleDialog::AppendText(const QuestCore::TextString& text)
{
	_text += text;
}

void SimpleDialog::Draw(IOutput& output)
{
	_text = QuestCore::TextString();
	_paragraph->Print(*this);
	output.WriteLn(_text);

	DialogBase::Draw(output);
}
