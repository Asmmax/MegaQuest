#pragma once
#include "Game/ICommand.hpp"

namespace Game
{
	class CommandManager;

	class AliasCommand :public ICommand
	{
	public:
		AliasCommand(const std::string& alias, CommandManager* commandManager);

		virtual void Run(const std::vector<std::string>& args) override;
	private:
		CommandManager* _parent;
		std::string _orig;
	};
}
