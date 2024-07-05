#include "Game/Commands/AliasCommand.hpp"
#include "Game/CommandManager.hpp"

using namespace Game;

AliasCommand::AliasCommand(const std::string& alias,
	CommandManager* commandManager):

	_orig(alias),
	_parent(commandManager)
{
}

void AliasCommand::Run(const std::vector<std::string>& args)
{
	if (_parent) {
		_parent->Run(_orig, args);
	}
}
