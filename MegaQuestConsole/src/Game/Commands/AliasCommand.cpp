#include "Game/Commands/AliasCommand.hpp"
#include "Game/CommandManager.hpp"

using namespace Game;

AliasCommand::AliasCommand(const std::string& alias,
	const CommandManagerWeakPtr& commandManager):

	_orig(alias),
	_parent(commandManager)
{
}

void AliasCommand::Run(const std::vector<std::string>& args)
{
	if (auto ptr = _parent.lock()) {
		ptr->Run(_orig, args);
	}
}
