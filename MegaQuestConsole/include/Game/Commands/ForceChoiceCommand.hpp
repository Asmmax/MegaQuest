#pragma once
#include "Game/Commands/VoidCommand.hpp"
#include <string>

namespace Game
{
	class IDialog;

	class ForceChoiceCommand : public VoidCommand
	{
		using DialogPtr = std::shared_ptr<IDialog>;
	public:
		ForceChoiceCommand(const DialogPtr& dialog, const std::string& actionKey, int choiceId = 0);
		virtual void Run() override;
	private:
		DialogPtr _dialog;
		std::string _actionKey;
		int _choiceId;
	};
}
