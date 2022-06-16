#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class IAction;

	/// @serializable
	struct Case
	{
		TextString name;
		std::vector<std::shared_ptr<IAction>> actions;

		void Do();
	};
}
