#pragma once
#include "Utils/EventBus.hpp"

namespace Game
{
	struct Events
	{
		static EventBus<> Quit;
	};
}
