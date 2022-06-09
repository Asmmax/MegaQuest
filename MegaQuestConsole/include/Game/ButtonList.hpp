#pragma once
#include "IButtonPanel.hpp"
#include "TextString.hpp"
#include <vector>

namespace Game
{
	class IOutput;
	class IDialog;

	class ButtonList : public QuestCore::IButtonGroup
	{
		struct Button
		{
			QuestCore::TextString name;
			Callback callback;
		};

		using DialogWeakPtr = std::weak_ptr<IDialog>;

	public:
		using Ptr = std::shared_ptr<ButtonList>;

		ButtonList(const DialogWeakPtr& parent);
		ButtonList(const DialogWeakPtr& parent, const QuestCore::TextString& error);
		void Clear();
		virtual void AddButton(const QuestCore::TextString& text, const Callback& callback) override;
		void Do();
		void Do(int answer);
		std::vector<QuestCore::TextString> GetNames() const;
		size_t GetButtonCount() const;
		void Update(IOutput& output);

	private:
		std::vector<Button> _buttons;
		DialogWeakPtr _parent;
		QuestCore::TextString _error;
	};
}
