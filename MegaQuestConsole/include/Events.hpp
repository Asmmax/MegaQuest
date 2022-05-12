#pragma once
#include "EventBus.hpp"

struct GameEvents
{
	static EventBus<> Quit;
};
