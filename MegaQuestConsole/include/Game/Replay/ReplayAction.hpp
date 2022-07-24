#pragma once
#include <memory>

namespace Game
{
	class IButtonList;

	struct ReplayAction
	{
		std::shared_ptr<IButtonList> buttonList;
		int answer = -1;

		void operator()();
	};
}