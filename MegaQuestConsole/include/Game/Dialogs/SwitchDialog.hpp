#pragma once
#include "Game/Dialogs/DialogBase.hpp"
#include <vector>

namespace Game
{
	/// @serializable
	class SwitchDialog : public DialogBase
	{
		using DialogPtr = std::shared_ptr<IDialog>;

	public:
		using Ptr = std::shared_ptr<SwitchDialog>;

		SwitchDialog(const QuestCore::TextString& intro, 
			const std::vector<ButtonListPtr> buttonGroups = std::vector<ButtonListPtr>(),
			const std::vector<DialogPtr>& dialogs = std::vector<DialogPtr>());
		void AddDialog(const DialogPtr& dialog);
		virtual void Init(IOutput& output) override;
		virtual void Update() override;
		virtual void Draw(IOutput& output) override;
		void Next();

	private:
		std::vector<DialogPtr> _dialogs;
		DialogPtr _currentDialog;
		bool _isIntroShowed;
	};
}
