#pragma once
#include "Game/Commands/IntCommand.hpp"

namespace Game
{
	class IButtonList;

	class ChoiceCommand : public IntCommand
	{
	public:
		ChoiceCommand(IButtonList* buttonGroup,
			const QuestCore::TextString& error);
		
		virtual void Run(int arg) override;
	private:
		IButtonList* _buttonList;
	};
}
