#pragma once
#include "IButtonPanel.hpp"

namespace Game
{
	class IOutput;

	class IButtonList : public QuestCore::IButtonGroup
	{
	public:
		using Ptr = std::shared_ptr<IButtonList>;

		virtual void Clear() = 0;
		virtual void Do(int answer = 0) = 0;
		virtual void Update(IOutput& output) = 0;
	};
}
