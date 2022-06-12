#pragma once
#include "Game/IButtonList.hpp"
#include "TextString.hpp"
#include <vector>

namespace Game
{
	class IOutput;
	class SwitchButtonList;

	class ButtonListBase : public IButtonList
	{
		using OutputPtr = std::shared_ptr<IOutput>;
		using SwitchButtonListPtr = std::shared_ptr<SwitchButtonList>;

	public:
		struct Button
		{
			QuestCore::TextString name;
			Callback callback;
		};

		using Ptr = std::shared_ptr<ButtonListBase>;

		ButtonListBase(const OutputPtr& output,
			const QuestCore::TextString& error);

		virtual void Do(int answer = 0) override;
		virtual void Update() override;
		virtual void SetButtonDoneCallback(const Callback& callback) override;
		void AddButton(const Button& button);
		void Clear();
		void Print();
		void SetSwitchButtonList(const SwitchButtonListPtr& switchList);

	private:
		std::vector<QuestCore::TextString> GetNames() const;

	private:
		std::vector<Button> _buttons;
		OutputPtr _output;
		QuestCore::TextString _error;
		Callback _buttonDone;
		SwitchButtonListPtr _switchList;
	};
}
