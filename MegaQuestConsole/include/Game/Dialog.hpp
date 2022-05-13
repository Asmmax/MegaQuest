#pragma once
#include "ITextView.hpp"
#include "IButtonPanel.hpp"
#include "TextString.hpp"
#include <map>

namespace QuestCore
{
	class QuestBase;
}

namespace Game
{
	class IOutput;
	class ButtonList;

	class Dialog : public QuestCore::ITextView, public QuestCore::IButtonPanel
	{
		using OutputPtr = std::shared_ptr<IOutput>;
		using QuestPtr = std::shared_ptr<QuestCore::QuestBase>;
		using ButtonListPtr = std::shared_ptr<ButtonList>;

	public:
		using Ptr = std::shared_ptr<Dialog>;

		Dialog(const OutputPtr& output);
		virtual void Clear() override;
		virtual void RemoveAllButtons() override;
		virtual void AppendText(const QuestCore::TextString& text) override;
		virtual QuestCore::IButtonGroup& GetButtonGroup(const std::string& actionKey) override;
		ButtonListPtr GetDefaultButtonList();
		ButtonListPtr GetInventoryButtonList();
		void SetQuest(const QuestPtr& quest);
		void Update();
		bool Answer(int answer);
		void OpenInventory();

	private:
		OutputPtr _output;
		QuestPtr _quest;
		QuestCore::TextString _text;
		std::map<std::string, ButtonListPtr> _buttonGroups;
	};
}
