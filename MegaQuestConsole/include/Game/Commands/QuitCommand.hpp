#pragma once
#include "Game/Commands/VoidCommand.hpp"

namespace Game
{
	/// @serializable
	class QuitCommand : public VoidCommand
	{
	public:
		virtual void Run() override;
	};
}
