#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class IAction;

	struct Case
	{
		TextString name;
		std::vector<IAction*> actions;

		void Do();
	};
}
