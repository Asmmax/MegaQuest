#pragma once
#include "Game/Commands/VoidCommand.hpp"
#include <string>

namespace Game
{
	class IDialog;

	class DialogVoidCommand : public VoidCommand
	{
		using DialogPtr = std::shared_ptr<IDialog>;
	public:
		DialogVoidCommand(const DialogPtr& dialog, const std::string& key);
		virtual void Run() override;
	private:
		DialogPtr _dialog;
		std::string _key;
	};
}
