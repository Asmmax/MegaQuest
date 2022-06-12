#pragma once
#include "Game/Dialogs/IntroDialog.hpp"
#include <memory>
#include <vector>
#include <string>

namespace Game
{
	class IOutput;

	class SwitchDialog : public IntroDialog
	{
		using DialogPtr = std::shared_ptr<IDialog>;
		using ButtonListPtr = std::shared_ptr<IButtonList>;
		using OutputPtr = std::shared_ptr<IOutput>;

	public:
		using Ptr = std::shared_ptr<SwitchDialog>;

		SwitchDialog(const OutputPtr& output, const QuestCore::TextString& intro);
		void AddDialog(const DialogPtr& dialog);
		void AddButtonList(const ButtonListPtr& buttonList);
		virtual void Init() override;
		virtual void Update() override;
		void Next();

	private:
		std::vector<DialogPtr> _dialogs;
		DialogPtr _currentDialog;
		std::vector<ButtonListPtr> _buttonGroups;
	};
}
