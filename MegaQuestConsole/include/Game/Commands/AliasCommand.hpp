#pragma once
#include "Game/ICommand.hpp"

namespace Game
{
	class CommandManager;

	class AliasCommand :public ICommand
	{
		using CommandManagerWeakPtr = std::weak_ptr<CommandManager>;

	public:
		AliasCommand(const CommandManagerWeakPtr& parent, const std::string& orig);
		virtual void Run(const std::vector<std::string>& args) override;
	private:
		CommandManagerWeakPtr _parent;
		std::string _orig;
	};
}
