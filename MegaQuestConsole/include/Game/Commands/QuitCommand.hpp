#pragma once
#include "Game/Commands/VoidCommand.hpp"

namespace Game
{
	class QuitCommand : public VoidCommand
	{
	public:
		virtual void Run() override;
	};
}