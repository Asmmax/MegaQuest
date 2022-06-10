#include "Game/Commands/AliasCommand.hpp"
#include "Game/CommandManager.hpp"

using namespace Game;

AliasCommand::AliasCommand(const CommandManagerWeakPtr& parent, const std::string& orig):
	_parent(parent),
	_orig(orig)
{
}

void AliasCommand::Run(const std::vector<std::string>& args)
{
	if (auto ptr = _parent.lock()) {
		ptr->Run(_orig, args);
	}
}
