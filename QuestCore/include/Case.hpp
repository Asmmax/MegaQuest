#pragma once
#include "TextString.hpp"
#include <memory>
#include <vector>

namespace QuestCore
{
	class IAction;

	struct Case
	{
	private:
		using ActionPtr = std::shared_ptr<IAction>;

	public:
		TextString name;
		std::vector<ActionPtr> actions;

		void Do();
	};
}
