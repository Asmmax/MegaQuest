#include "Game/Dialogs/SimpleDialog.hpp"
#include "Game/IButtonList.hpp"
#include "Game/IOutput.hpp"
#include "IParagraph.hpp"
#include "Quests/Slots/ParagraphSlot.hpp"

using namespace Game;


SimpleDialog::SimpleDialog(const QuestCore::TextString& intro,
	QuestCore::IParagraphFactory* paragraphFactory,
	const std::vector<IButtonList*> buttonGroups) :

	DialogBase(intro, buttonGroups),
	_paragraphFactory(paragraphFactory)
{
}

void SimpleDialog::AppendText(const QuestCore::TextString& text)
{
	_text += text;
}

void SimpleDialog::Draw(IOutput& output)
{
	_text = QuestCore::TextString();

	auto paragraph = _paragraphFactory->GetParagraph();
	if (!paragraph) {
		return;
	}

	paragraph->Print(*this);
	output.WriteLn(_text);
	DialogBase::Draw(output);
}
