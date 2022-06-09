#pragma once
#include "Game/Commands/IntCommand.hpp"

namespace Game
{
	class IDialog;

	class ChoiceCommand : public IntCommand
	{
		using DialogPtr = std::shared_ptr<IDialog>;
	public:
		ChoiceCommand(const DialogPtr& dialog, 
			const std::string& actionKey, 
			const QuestCore::TextString& error);
		
		virtual void Run(int arg) override;
	private:
		DialogPtr _dialog;
		std::string _actionKey;
	};
}
