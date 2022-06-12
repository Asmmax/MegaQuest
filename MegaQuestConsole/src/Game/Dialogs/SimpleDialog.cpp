#include "Game/Dialogs/SimpleDialog.hpp"
#include "Game/IButtonList.hpp"
#include "Game/IOutput.hpp"
#include "IParagraph.hpp"

using namespace Game;


SimpleDialog::SimpleDialog(const OutputPtr& output,
	const QuestCore::TextString& intro,
	const ParagraphPtr& paragraph) :

	DialogBase(output, intro),
	_paragraph(paragraph)
{
}

void SimpleDialog::AppendText(const QuestCore::TextString& text)
{
	_text += text;
}

void SimpleDialog::Draw()
{
	auto&& output = GetOutput();

	_text = QuestCore::TextString();
	_paragraph->Print(*this);
	output->WriteLn(_text);

	DialogBase::Draw();
}
