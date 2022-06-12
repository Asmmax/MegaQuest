#pragma once
#include "ITextView.hpp"
#include "Game/Dialogs/DialogBase.hpp"

namespace QuestCore
{
	class IParagraph;
}

namespace Game
{
	class IOutput;

	class SimpleDialog : public DialogBase, public QuestCore::ITextView
	{
		using OutputPtr = std::shared_ptr<IOutput>;
		using ParagraphPtr = std::shared_ptr<QuestCore::IParagraph>;

	public:
		using Ptr = std::shared_ptr<SimpleDialog>;

		SimpleDialog(const OutputPtr& output,
			const QuestCore::TextString& intro,
			const ParagraphPtr& paragraph);

		virtual void AppendText(const QuestCore::TextString& text) override;
		virtual void Draw() override;

	private:
		ParagraphPtr _paragraph;
		QuestCore::TextString _text;
	};
}
