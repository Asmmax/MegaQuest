#include "Game/Dialogs/SimpleDialog.hpp"
#include "Game/IButtonList.hpp"
#include "Game/IOutput.hpp"
#include "IParagraph.hpp"
#include "Quests/Slots/ParagraphSlot.hpp"

using namespace Game;


SimpleDialog::SimpleDialog(const QuestCore::TextString& intro,
	const ParagraphSlotPtr& paragraphSlot,
	const std::vector<ButtonListPtr> buttonGroups) :

	DialogBase(intro, buttonGroups),
	_paragraphSlot(paragraphSlot)
{
}

void SimpleDialog::AppendText(const QuestCore::TextString& text)
{
	_text += text;
}

void SimpleDialog::Draw(IOutput& output)
{
	_text = QuestCore::TextString();

	auto paragraph = _paragraphSlot->GetParagraph();
	if (!paragraph) {
		return;
	}

	paragraph->Print(*this);
	output.WriteLn(_text);
	DialogBase::Draw(output);
}
