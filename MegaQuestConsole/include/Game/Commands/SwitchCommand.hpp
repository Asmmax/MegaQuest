#pragma once
#include "Game/Commands/VoidCommand.hpp"
#include <string>

namespace Game
{
	class SwitchDialog;

	class SwitchCommand : public VoidCommand
	{
	public:
		SwitchCommand(SwitchDialog* switchDialog);
		virtual void Run() override;
	private:
		SwitchDialog* _dialog;
	};
}
