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
	/// @serializable
	class SimpleDialog : public DialogBase, public QuestCore::ITextView
	{
		using ParagraphFactoryPtr = std::shared_ptr<QuestCore::IParagraphFactory>;
		using ParagraphPtr = std::shared_ptr<QuestCore::IParagraph>;

	public:
		using Ptr = std::shared_ptr<SimpleDialog>;

		SimpleDialog(const QuestCore::TextString& intro,
			const ParagraphFactoryPtr& paragraphFactory,
			const std::vector<ButtonListPtr> buttonGroups = std::vector<ButtonListPtr>());

		virtual void AppendText(const QuestCore::TextString& text) override;
		virtual void Draw(IOutput& output) override;

	private:
		ParagraphFactoryPtr _paragraphFactory;
		QuestCore::TextString _text;
	};
}
