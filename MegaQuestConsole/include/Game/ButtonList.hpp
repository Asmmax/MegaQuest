#pragma once
#include "IButtonPanel.hpp"
#include "TextString.hpp"
#include <vector>

namespace Game
{
	class IOutput;
	class Dialog;

	class ButtonList : public QuestCore::IButtonGroup
	{
		struct Button
		{
			QuestCore::TextString name;
			Callback callback;
		};

	public:
		using Ptr = std::shared_ptr<ButtonList>;

		ButtonList(Dialog* parent);
		virtual void AddButton(const QuestCore::TextString& text, const Callback& callback) override;
		void Do();
		void Do(int answer);
		std::vector<QuestCore::TextString> GetNames() const;
		size_t GetButtonCount() const;
		void Update(IOutput& output);

	private:
		std::vector<Button> _buttons;
		Dialog* _parent;
	};
}
