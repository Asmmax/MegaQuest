#include "Game/Commands/AliasCommand.hpp"
#include "Game/CommandManager.hpp"

using namespace Game;

AliasCommand::AliasCommand(const std::string& orig):
	_orig(orig)
{
}

void AliasCommand::Run(const std::vector<std::string>& args)
{
	CommandManager::Instance().Run(_orig, args);
}
