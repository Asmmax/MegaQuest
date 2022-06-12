#pragma once
#include "Game/IButtonList.hpp"
#include "TextString.hpp"
#include <vector>

namespace Game
{
	class IDialog;
	class IOutput;
	class SwitchButtonList;

	class ButtonListBase : public IButtonList
	{
		using DialogWeakPtr = std::weak_ptr<IDialog>;
		using SwitchButtonListPtr = std::weak_ptr<SwitchButtonList>;
		using OutputPtr = std::shared_ptr<IOutput>;

	public:
		struct Button
		{
			QuestCore::TextString name;
			Callback callback;
		};

		using Ptr = std::shared_ptr<ButtonListBase>;

		ButtonListBase(const OutputPtr& output,
			const QuestCore::TextString& error,
			bool show = true);

		virtual void Do(int answer = 0) override;
		virtual void Update() override;
		virtual void Draw() override;

		void SetParentDialog(const DialogWeakPtr& dialog);
		void SetSwitchButtonList(const SwitchButtonListPtr& switchList);
		void AddButton(const Button& button);
		void Clear();

	private:
		std::vector<QuestCore::TextString> GetNames() const;

	private:
		DialogWeakPtr _parentDialog;
		SwitchButtonListPtr _switchList;
		std::vector<Button> _buttons;
		OutputPtr _output;
		QuestCore::TextString _error;
		bool _show;
	};
}
