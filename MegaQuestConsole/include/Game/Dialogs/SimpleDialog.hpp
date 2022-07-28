#pragma once
#include "ITextView.hpp"
#include "Game/Dialogs/DialogBase.hpp"

namespace QuestCore
{
	class ParagraphSlot;
	class IParagraph;
}

namespace Game
{
	/// @serializable
	class SimpleDialog : public DialogBase, public QuestCore::ITextView
	{
		using ParagraphSlotPtr = std::shared_ptr<QuestCore::ParagraphSlot>;
		using ParagraphPtr = std::shared_ptr<QuestCore::IParagraph>;

	public:
		using Ptr = std::shared_ptr<SimpleDialog>;

		SimpleDialog(const QuestCore::TextString& intro,
			const ParagraphSlotPtr& paragraphSlot,
			const std::vector<ButtonListPtr> buttonGroups = std::vector<ButtonListPtr>());

		virtual void AppendText(const QuestCore::TextString& text) override;
		virtual void Draw(IOutput& output) override;

	private:
		ParagraphSlotPtr _paragraphSlot;
		QuestCore::TextString _text;
	};
}
