#pragma once
#include "Game/Commands/IntCommand.hpp"

namespace Game
{
	class IButtonList;

	/// @serializable
	class ChoiceCommand : public IntCommand
	{
		using ButtonListPtr = std::shared_ptr<IButtonList>;
	public:
		ChoiceCommand(const ButtonListPtr& buttonGroup,
			const QuestCore::TextString& error);
		
		virtual void Run(int arg) override;
	private:
		ButtonListPtr _buttonList;
	};
}
