#pragma once
#include "Game/Commands/IntCommand.hpp"

namespace Game
{
	class IDialog;

	class DialogIntCommand : public IntCommand
	{
		using DialogPtr = std::shared_ptr<IDialog>;
	public:
		DialogIntCommand(const DialogPtr& dialog, const QuestCore::TextString& error);
		virtual void Run(int arg) override;
	private:
		DialogPtr _dialog;
	};
}
