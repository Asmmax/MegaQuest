#pragma once
#include "Game/Commands/VoidCommand.hpp"
#include <string>

namespace Game
{
	class SwitchDialog;

	/// @serializable
	class SwitchCommand : public VoidCommand
	{
		using SwitchDialogPtr = std::shared_ptr<SwitchDialog>;
	public:
		SwitchCommand(const SwitchDialogPtr& switchDialog);
		virtual void Run() override;
	private:
		SwitchDialogPtr _dialog;
	};
}
