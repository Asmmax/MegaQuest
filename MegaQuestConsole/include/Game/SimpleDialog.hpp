#pragma once
#include "ITextView.hpp"
#include "IButtonPanel.hpp"
#include "TextString.hpp"
#include "Game/IDialog.hpp"

#include <map>

namespace QuestCore
{
	class IParagraph;
	class ICaseContainer;
}

namespace Game
{
	class IOutput;
	class ButtonList;

	class SimpleDialog : public IDialog, public QuestCore::ITextView, public QuestCore::IButtonPanel
	{
		using OutputPtr = std::shared_ptr<IOutput>;
		using ButtonListPtr = std::shared_ptr<ButtonList>;
		using ParagraphPtr = std::shared_ptr<QuestCore::IParagraph>;
		using CaseContainerPtr = std::shared_ptr<QuestCore::ICaseContainer>;

	public:
		using Ptr = std::shared_ptr<SimpleDialog>;

		SimpleDialog(const OutputPtr& output, 
			const ParagraphPtr& paragraph, 
			const CaseContainerPtr& container,
			const QuestCore::TextString& intro);

		virtual void AppendText(const QuestCore::TextString& text) override;
		virtual QuestCore::IButtonGroup::Ptr GetButtonGroup(const std::string& actionKey) override;
		void AddButtonList(const std::string& key, const ButtonListPtr& buttonList);
		virtual ButtonListPtr GetButtonList(const std::string& key = std::string()) override;
		virtual void Init() override;
		virtual void Update() override;

	private:
		OutputPtr _output;
		ParagraphPtr _paragraph;
		CaseContainerPtr _container;
		QuestCore::TextString _text;
		QuestCore::TextString _intro;
		std::map<std::string, ButtonListPtr> _buttonGroups;
	};
}
