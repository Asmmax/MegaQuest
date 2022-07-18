#pragma once
#include "ITextView.hpp"
#include "Game/Dialogs/DialogBase.hpp"

namespace QuestCore
{
	class IParagraph;
}

namespace Game
{
	/// @serializable
	class SimpleDialog : public DialogBase, public QuestCore::ITextView
	{
		using ParagraphPtr = std::shared_ptr<QuestCore::IParagraph>;

	public:
		using Ptr = std::shared_ptr<SimpleDialog>;

		SimpleDialog(const QuestCore::TextString& intro,
			const ParagraphPtr& paragraph,
			const std::vector<ButtonListPtr> buttonGroups = std::vector<ButtonListPtr>());

		virtual void AppendText(const QuestCore::TextString& text) override;
		virtual void Draw(IOutput& output) override;

	private:
		ParagraphPtr _paragraph;
		QuestCore::TextString _text;
	};
}
