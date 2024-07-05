#pragma once
#include "Game/Commands/VoidCommand.hpp"
#include <string>

namespace Game
{
	class IButtonList;

	class ForceChoiceCommand : public VoidCommand
	{
	public:
		ForceChoiceCommand(IButtonList* buttonGroup, int choice = 0);
		virtual void Run() override;
	private:
		IButtonList* _buttonList;
		int _choiceId;
	};
}
