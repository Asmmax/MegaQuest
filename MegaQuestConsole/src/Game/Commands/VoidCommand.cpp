#include "Game/Commands/VoidCommand.hpp"

using namespace Game;

void VoidCommand::Run(const std::vector<std::string>& /*args*/)
{
	Run();
}
