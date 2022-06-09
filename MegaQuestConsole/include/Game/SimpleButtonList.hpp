#pragma once
#include "Game/IButtonList.hpp"
#include "TextString.hpp"
#include <vector>

namespace Game
{
	class IDialog;

	class SimpleButtonList : public IButtonList
	{
		struct Button
		{
			QuestCore::TextString name;
			Callback callback;
		};

		using DialogWeakPtr = std::weak_ptr<IDialog>;

	public:
		using Ptr = std::shared_ptr<SimpleButtonList>;

		SimpleButtonList(const DialogWeakPtr& parent);
		SimpleButtonList(const DialogWeakPtr& parent, const QuestCore::TextString& error);
		virtual void Clear() override;
		virtual void Do(int answer = 0) override;
		virtual void Update(IOutput& output) override;
		virtual void AddButton(const QuestCore::TextString& text, const Callback& callback) override;

	private:
		std::vector<QuestCore::TextString> GetNames() const;

	private:
		std::vector<Button> _buttons;
		DialogWeakPtr _parent;
		QuestCore::TextString _error;
	};
}
