#pragma once
#include "Game/ICommand.hpp"

namespace Game
{
	class CommandManager;

	/// @serializable
	class AliasCommand :public ICommand
	{
		using CommandManagerWeakPtr = std::weak_ptr<CommandManager>;

	public:
		AliasCommand(const std::string& alias,
			const CommandManagerWeakPtr& commandManager);

		virtual void Run(const std::vector<std::string>& args) override;
	private:
		CommandManagerWeakPtr _parent;
		std::string _orig;
	};
}
