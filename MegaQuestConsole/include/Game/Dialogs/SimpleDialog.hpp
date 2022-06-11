#pragma once
#include "ITextView.hpp"
#include "Game/Dialogs/IntroDialog.hpp"

#include <map>

namespace QuestCore
{
	class IParagraph;
}

namespace Game
{
	class IOutput;

	class SimpleDialog : public IntroDialog, public QuestCore::ITextView
	{
		using OutputPtr = std::shared_ptr<IOutput>;
		using ButtonListPtr = std::shared_ptr<IButtonList>;
		using ParagraphPtr = std::shared_ptr<QuestCore::IParagraph>;

	public:
		using Ptr = std::shared_ptr<SimpleDialog>;

		SimpleDialog(const OutputPtr& output,
			const QuestCore::TextString& intro,
			const ParagraphPtr& paragraph);

		virtual void AppendText(const QuestCore::TextString& text) override;
		void AddButtonList(const std::string& key, const ButtonListPtr& buttonList);
		virtual ButtonListPtr GetButtonList(const std::string& key = std::string()) override;
		virtual void Update() override;

	private:
		ParagraphPtr _paragraph;
		QuestCore::TextString _text;
		std::map<std::string, ButtonListPtr> _buttonGroups;
	};
}
