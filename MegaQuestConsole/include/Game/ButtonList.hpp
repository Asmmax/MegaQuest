#pragma once
#include "IButtonPanel.hpp"
#include "TextString.hpp"
#include <vector>

namespace Game
{
	class ButtonList : public QuestCore::IButtonGroup
	{
		struct Button
		{
			QuestCore::TextString name;
			Callback callback;
		};

	public:
		using Ptr = std::shared_ptr<ButtonList>;

		ButtonList(const Callback& finishCallback);
		virtual void AddButton(const QuestCore::TextString& text, const Callback& callback) override;
		void Do();
		void Do(int answer);
		std::vector<QuestCore::TextString> GetNames() const;
		size_t GetButtonCount() const;

	private:
		Callback _finishCallback;
		std::vector<Button> _buttons;
	};
}
