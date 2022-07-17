#pragma once
#include "Game/Dialogs/DialogBase.hpp"
#include <vector>

namespace Game
{
	class IOutput;

	/// @serializable
	class SwitchDialog : public DialogBase
	{
		using DialogPtr = std::shared_ptr<IDialog>;
		using OutputPtr = std::shared_ptr<IOutput>;

	public:
		using Ptr = std::shared_ptr<SwitchDialog>;

		SwitchDialog(const OutputPtr& output, const QuestCore::TextString& intro);
		void AddDialog(const DialogPtr& dialog);
		virtual void Init() override;
		virtual void Update() override;
		virtual void Draw() override;
		void Next();

	private:
		std::vector<DialogPtr> _dialogs;
		DialogPtr _currentDialog;
	};
}
