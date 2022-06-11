#pragma once
#include "IButtonGroup.hpp"

namespace Game
{
	class IButtonList : public QuestCore::IButtonGroup
	{
	public:
		using Ptr = std::shared_ptr<IButtonList>;

		virtual void Do(int answer = 0) = 0;
		virtual void Update() = 0;
	};
}
