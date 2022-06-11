#pragma once
#include "Game/IButtonList.hpp"
#include "TextString.hpp"
#include <vector>

namespace Game
{
	class IOutput;
	class IDialog;

	class ButtonListBase : public IButtonList
	{
		struct Button
		{
			QuestCore::TextString name;
			Callback callback;
		};

		using DialogWeakPtr = std::weak_ptr<IDialog>;
		using OutputPtr = std::shared_ptr<IOutput>;

	public:
		using Ptr = std::shared_ptr<ButtonListBase>;

		ButtonListBase(const DialogWeakPtr& parent,
			const OutputPtr& output,
			const QuestCore::TextString& error);

		virtual void Do(int answer = 0) override;
		virtual void AddButton(const QuestCore::TextString& text, const Callback& callback) override;
		void Clear();
		void Print();

	private:
		std::vector<QuestCore::TextString> GetNames() const;

	private:
		std::vector<Button> _buttons;
		DialogWeakPtr _parent;
		OutputPtr _output;
		QuestCore::TextString _error;
	};
}
