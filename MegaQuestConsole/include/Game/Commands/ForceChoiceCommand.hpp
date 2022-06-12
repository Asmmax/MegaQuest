#pragma once
#include "Game/Commands/VoidCommand.hpp"
#include <string>

namespace Game
{
	class IButtonList;

	class ForceChoiceCommand : public VoidCommand
	{
		using ButtonListPtr = std::shared_ptr<IButtonList>;
	public:
		ForceChoiceCommand(const ButtonListPtr& buttonList, int choiceId = 0);
		virtual void Run() override;
	private:
		ButtonListPtr _buttonList;
		int _choiceId;
	};
}
