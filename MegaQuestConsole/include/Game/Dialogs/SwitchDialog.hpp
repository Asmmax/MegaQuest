#pragma once
#include "Game/Dialogs/DialogBase.hpp"
#include <vector>

namespace Game
{
	class SwitchDialog : public DialogBase
	{
	public:
		using Ptr = std::shared_ptr<SwitchDialog>;

		SwitchDialog(const QuestCore::TextString& intro, 
			const std::vector<IButtonList*> buttonGroups = std::vector<IButtonList*>(),
			const std::vector<IDialog*>& dialogs = std::vector<IDialog*>());
		void AddDialog(IDialog* dialog);
		virtual void Init(IOutput& output) override;
		virtual void Update() override;
		virtual void Draw(IOutput& output) override;
		void Next();

	private:
		std::vector<IDialog*> _dialogs;
		IDialog* _currentDialog;
		bool _isIntroShowed;
	};
}
