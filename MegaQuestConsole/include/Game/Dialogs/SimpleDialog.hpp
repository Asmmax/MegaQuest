#pragma once
#include "ITextView.hpp"
#include "Game/Dialogs/DialogBase.hpp"

namespace QuestCore
{
	class IParagraphFactory;
	class IParagraph;
}

namespace Game
{
	class SimpleDialog : public DialogBase, public QuestCore::ITextView
	{
	public:
		SimpleDialog(const QuestCore::TextString& intro,
			QuestCore::IParagraphFactory* paragraphFactory,
			const std::vector<IButtonList*> buttonGroups = std::vector<IButtonList*>());

		virtual void AppendText(const QuestCore::TextString& text) override;
		virtual void Draw(IOutput& output) override;

	private:
		QuestCore::IParagraphFactory* _paragraphFactory;
		QuestCore::TextString _text;
	};
}
